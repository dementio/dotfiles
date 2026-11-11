#!/bin/bash
set -euo pipefail # Added -e for fail-fast and pipefail for safer pipelines

_error() {
  echo >&2 ":: $*"
}

if [[ $EUID -eq 0 ]]; then
   _error "Run this script as your standard user, it will call sudo when needed."
   exit 1
fi

echo ":: Updating system and installing common utils..."
sudo apt-get update
sudo apt-get -y dist-upgrade

# Removed python-dev, ntpdate. Added python3-dev, pipx, stow, yt-dlp
sudo apt-get -y install vim axel gpm elinks build-essential exuberant-ctags python3-pip \
python3-dev pipx colormake bash-completion colordiff ccze expect flex byacc libncurses-dev \
irssi irssi-dev lshw pastebinit deborphan p7zip-full beep screen setserial autoconf \
libsqlite3-dev tmux exfat-fuse yara curl surfraw rbenv fontconfig stow yt-dlp

echo ":: Setting up dotfiles using GNU Stow..."
# GNU Stow automatically symlinks mirroring your repo structure. 
# e.g., if you have dotfiles/bash/.bashrc, running 'stow bash' links it to ~/.bashrc
cd ~/dotfiles
# stow . # Uncomment after structuring your dotfiles repo for stow

echo ":: Installing Python CLI tools via pipx..."
# pipx isolates dependencies but symlinks the binary to your PATH
pipx ensurepath
pipx install glances
pipx install speedtest-cli

echo ":: Adding sr elvi to path..."
surfraw-update-path -add

echo ":: Building & installing UnNetHack..."
cd ~/dotfiles/unnethack
make clean
./configure --enable-curses-graphics --enable-score-on-botl
make
sudo make install
sudo ln -fs ~/dotfiles/.nethackrc /usr/local/share/unnethack/unnethackrc.default

echo ":: Updating command-not-found..."
sudo update-command-not-found

echo "Change .irssi/config:19"
beep