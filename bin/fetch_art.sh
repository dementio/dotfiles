#!/bin/bash

# --- WORKER MODE (Internal use for parallel execution) ---
if [[ "$1" == "--worker" ]]; then
  shift
  dir="$1"
  MUSIC_DIR="$2"
  TARGET_SIZE="$3"
  MIN_SIZE="$4"
  FAILED_LOG="$5"
  RETRY_FILE="$6"
  RUN_LOG="$7"

  raw_album=$(basename "$dir")
  album=$(echo "$raw_album" | sed -E 's/^[0-9]{4} - //')
  artist=$(basename "$(dirname "$dir")")
  output_file="$MUSIC_DIR/$dir/folder.jpg"
  output_file_png="$MUSIC_DIR/$dir/folder.png"

  log_msg() {
    flock -x 201
    echo "$1" >> "$RUN_LOG"
  } 201>lock.run

  # Safety check: Skip if artwork already exists
  if [ -f "$output_file" ] || [ -f "$output_file_png" ]; then
    log_msg "[Skipped] Already exists: $artist - $album"
    echo "." # Output for pv to count
    exit 0
  fi

  log_msg "[Search] $artist - $album"

  sacad "$artist" "$album" "$TARGET_SIZE" "$output_file" >/dev/null 2>&1
  
  validate_img() {
    local img="$1"
    [ ! -f "$img" ] && return 1
    local dims
    dims=$(identify -format "%w %h" "$img" 2>/dev/null)
    [ $? -ne 0 ] && { rm -f "$img"; return 1; }
    local w h
    read -r w h <<< "$dims"
    if [ "$w" -lt "$MIN_SIZE" ] || [ "$h" -lt "$MIN_SIZE" ]; then
      rm -f "$img"
      return 1
    fi
    return 0
  }

  if ! validate_img "$output_file"; then
    glyrc cover --artist "$artist" --album "$album" --write "$output_file" >/dev/null 2>&1
    
    if ! validate_img "$output_file"; then
      {
        flock -x 200
        echo "$dir - Failed both sacad and glyrc attempts" >> "$FAILED_LOG"
        echo "$dir" >> "$RETRY_FILE"
      } 200>lock.ex
      log_msg "[Failed] $artist - $album"
      echo "." # Output for pv to count
      exit 1
    fi
  fi

  mogrify -resize "${TARGET_SIZE}x${TARGET_SIZE}>" "$output_file" 2>/dev/null
  
  mime_type=$(file -b --mime-type "$output_file")
  if [[ "$mime_type" == "image/jpeg" ]]; then
    jpegoptim --strip-all --quiet "$output_file"
  elif [[ "$mime_type" == "image/png" ]]; then
    optipng -quiet "$output_file"
  fi
  
  log_msg "[Success] $artist - $album"
  echo "." # Output for pv to count
  exit 0
fi

# --- MAIN SCRIPT MODE ---

show_help() {
  echo "Usage: $(basename "$0") [OPTIONS] [MUSIC_DIR] [REPORT_FILE] [TARGET_SIZE] [MIN_SIZE] [MAX_JOBS]"
  echo ""
  echo "Concurrently downloads missing album art with a live progress bar."
  echo ""
  echo "Options:"
  echo "  -h, --help     Display this help message and exit."
  echo "  --dry-run      Preview folders to process without downloading or modifying files."
}

DRY_RUN=0
POSITIONAL_ARGS=()

while [[ $# -gt 0 ]]; do
  case $1 in
    -h|--help)
      show_help
      exit 0
      ;;
    --dry-run)
      DRY_RUN=1
      shift
      ;;
    *)
      POSITIONAL_ARGS+=("$1")
      shift
      ;;
  esac
done

set -- "${POSITIONAL_ARGS[@]}"

MUSIC_DIR="${1:-/mnt/user/Storage/Music}"
REPORT_FILE="${2:-missing_artwork_report.txt}"
TARGET_SIZE="${3:-1000}"
MIN_SIZE="${4:-500}"
MAX_JOBS="${5:-4}"
FAILED_LOG="failed_downloads.log"
RETRY_FILE="retry_downloads.txt"
RUN_LOG="fetch_run.log"

echo "Checking system requirements..."
MISSING_DEPS=0
for cmd in sacad glyrc mogrify identify jpegoptim optipng flock xargs pv tr; do
  if ! command -v "$cmd" &> /dev/null; then
    echo "Error: Required tool '$cmd' is not installed or not in PATH."
    MISSING_DEPS=1
  fi
done

if [ $MISSING_DEPS -ne 0 ]; then
  echo ""
  echo "Please install missing tools: sudo apt install imagemagick jpegoptim optipng glyr util-linux findutils pv"
  echo "pip3 install sacad"
  exit 1
fi

if [ ! -d "$MUSIC_DIR" ]; then
  echo "Error: Directory '$MUSIC_DIR' does not exist."
  exit 1
fi

if [ ! -f "$REPORT_FILE" ]; then
  echo "Error: Report file '$REPORT_FILE' not found."
  exit 1
fi

if [ $DRY_RUN -eq 1 ]; then
  echo "-------------------------------------------------------------"
  echo " DRY RUN MODE: No files will be downloaded, modified or logged"
  echo "-------------------------------------------------------------"
  while IFS= read -r dir; do
    [ -z "$dir" ] && continue
    echo "[DRY RUN] Would process: $dir"
  done < "$REPORT_FILE"
  exit 0
fi

echo "Failed Artwork Downloads - $(date)" > "$FAILED_LOG"
echo "----------------------------------------" >> "$FAILED_LOG"
> "$RETRY_FILE"
> "$RUN_LOG"

TOTAL_ALBUMS=$(grep -c -v '^$' "$REPORT_FILE")

echo "Starting parallel batch processing with $MAX_JOBS concurrent jobs..."
echo "Detailed output is being logged to $RUN_LOG"
echo "-------------------------------------------------------------"

export SCRIPT_PATH="$(realpath "$0")"

# We feed the report into xargs, and pipe the background workers' output into pv so it ticks up upon completion
grep -v '^$' "$REPORT_FILE" | tr '\n' '\0' | xargs -0 -I {} -P "$MAX_JOBS" bash -c '
  "$SCRIPT_PATH" --worker "$0" "$1" "$2" "$3" "$4" "$5" "$6"
' {} "$MUSIC_DIR" "$TARGET_SIZE" "$MIN_SIZE" "$FAILED_LOG" "$RETRY_FILE" "$RUN_LOG" | pv -l -s "$TOTAL_ALBUMS" -N "Albums Processed" > /dev/null

echo ""
echo "-------------------------------------------------------------"
echo "Finished!"
echo " - Detailed run log saved to: $RUN_LOG"
if [ -s "$RETRY_FILE" ]; then
  echo " - A clean list of failed directories has been saved to: $RETRY_FILE"
  echo " - View error details in: $FAILED_LOG"
else
  rm -f "$RETRY_FILE" "$FAILED_LOG"
fi