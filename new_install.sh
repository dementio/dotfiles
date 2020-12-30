#!/bin/bash
#if [[ $EUID -ne 0 ]]; then
#   echo "This script must be run as root"
#   exit 1
#fi

# Add command switches for 'all' 'environment' etc

set -u      # exit if there is any unbound variable

_POPT=""    # primary   operation
_SOPT=""    # secondary operation
_TOPT=""    # options for operations
_PKG=""     # packages and extra parameters for apt-get
_VERBOSE="" # verbose mode
_FORCE=""   # force yes
_OSTYPE=""  # type of package manager (Arch pacman, Debian apt, ...)

_error() {
  echo >&2 ":: $*"
}

###
### Helpers
###

_os_is() {
  [[ "$_OSTYPE" = "$*" ]]
}

_exec_() {
  local _type="$1"
  shift
  if _os_is $_type; then
    [[ -z "$_VERBOSE" ]] || _error "Going to execute: $* $_VERBOSE $_FORCE"
    eval "$* $_VERBOSE $_FORCE"
  fi
}

# Detect OS & package type from /etc/issue
_found_arch() {
  local _ostype="$1"
  shift
  grep -qis "$*" /etc/issue && _OSTYPE="$_ostype"
}

# Detect package type
_OSTYPE_detect() {
  _found_arch PACMAN "Arch Linux" && return
  _found_arch DPKG   "Debian GNU/Linux" && return
  _found_arch DPKG   "Ubuntu" && return
  _found_arch YUM    "CentOS" && return
  _found_arch YUM    "Red Hat" && return
  _found_arch YUM    "Fedora" && return
  _found_arch ZYPPER "SUSE" && return

  [[ -z "$_OSTYPE" ]] || return

  # See also https://github.com/icy/pacapt/pull/22
  # Please not that $OSTYPE (which is `linux-gnu` on Linux system)
  # is not our $_OSTYPE. The choice is not very good because
  # a typo can just break the logic of the program.
  if [[ "$OSTYPE" != "darwin"* ]]; then
    _error "Can't detect OS type from /etc/issue. Running fallback method."
  fi
  if [[ -x "/usr/bin/pacman" ]]; then
    # This is to prevent a loop when this script is installed on
    # non-standard system
    grep -q "$FUNCNAME" '/usr/bin/pacman' >/dev/null 2>&1
    [[ $? -ge 1 ]] && _OSTYPE="PACMAN" && return
  fi
  [[ -x "/usr/bin/apt-get" ]]          && _OSTYPE="DPKG" && return
  [[ -x "/usr/bin/yum" ]]              && _OSTYPE="YUM" && return
  [[ -x "/opt/local/bin/port" ]]       && _OSTYPE="MACPORTS" && return
  command -v brew >/dev/null           && _OSTYPE="HOMEBREW" && return
  [[ -x "/usr/bin/emerge" ]]           && _OSTYPE="PORTAGE" && return
  [[ -x "/usr/bin/zypper" ]]           && _OSTYPE="ZYPPER" && return
  if [[ -z "$_OSTYPE" ]]; then
    _error "No supported package manager installed on system"
    _error "(supported: apt, homebrew, pacman, portage, yum)"
    exit 1
  fi
}

# Setup environment
ln -fs ~/dotfiles/.bashrc ~/.bashrc
ln -fs ~/dotfiles/.tmux.conf ~/.tmux.conf
ln -fs ~/dotfiles/.profile ~/.profile
ln -fs ~/dotfiles/.screen ~/.screen
ln -fs ~/dotfiles/.screenrc ~/.screenrc
ln -fs ~/dotfiles/.bash_logout ~/.bash_logout
ln -fs ~/dotfiles/.irssi ~/.irssi
ln -fs ~/dotfiles/bin ~/bin
ln -fs ~/dotfiles/.fonts ~/.fonts
mkdir -p ~/.config/surfraw
ln -fs ~/dotfiles/surfraw.conf ~/.config/surfraw/conf
source ~/.profile
fc-cache -fv

# Add nonfree if needed
#if $os = "Debian"; then
#  if ! grep -q non-free /etc/apt/sources.list; then
    sudo ln -fs ~/dotfiles/non-free.list /etc/apt/sources.list.d/non-free.list
#  fi
#fi

# Install common utils
sudo apt-get update
sudo apt-get -y dist-upgrade
sudo apt-get -y install vim axel gpm command-not-found elinks build-essential ctags python-pip python-dev colorgcc colormake \
colordiff colortail ccze expect flex byacc libncurses5-dev libncursesw5-dev irssi irssi-dev irssi-scripts lshw pastebinit deborphan \
p7zip-full ntpdate beep firmware-linux-nonfree screen setserial autoconf libsqlite3-dev tmux exfat-fuse yara curl surfraw rbenv
# Uncomment for Kali
#dict-devil dict-vera dict-foldoc dict-gcide dict-wn dict-moby-thesaurus

# Add sr elvi to path
surfraw-update-path -add

# Configure tty11 & tty12
#sudo echo 'C:12345:wait:/usr/bin/tail -n30 -f /var/log/messages | /usr/bin/ccze > /dev/tty12' >> /etc/inittab
#sudo echo "C:12345:wait:/usr/bin/setsid sh -c 'exec /usr/local/bin/glances <> /dev/tty11 >&0 2>&1'" >> /etc/inittab

# Pip installs
sudo pip install glances
sudo pip install speedtest-cli

# Install vimrc
ln -s ~/dotfiles/.vim_runtime ~/.vim_runtime
sh ~/.vim_runtime/install_awesome_vimrc.sh

# Build & install UnNetHack
cd ~/dotfiles/unnethack
make clean
./configure --enable-curses-graphics --enable-score-on-botl
make
sudo make install
sudo ln -fs ~/dotfiles/.nethackrc /usr/local/share/unnethack/unnethackrc.default

# Install YouTube-DL
sudo curl https://yt-dl.org/latest/youtube-dl -o /usr/local/bin/youtube-dl
sudo chmod a+x /usr/local/bin/youtube-dl

sudo update-command-not-found
echo "Change .irssi/config:19"
beep
