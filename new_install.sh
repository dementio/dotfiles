#!/bin/bash
#if [[ $EUID -ne 0 ]]; then
#   echo "This script must be run as root"
#   exit 1
#fi

# Detect distro and set to $os
fn_distro(){
arch=$(uname -m)
kernel=$(uname -r)
if [ -f /etc/lsb-release ]; then
        os=$(lsb_release -s -d)
elif [ -f /etc/debian_version ]; then
        os="Debian $(cat /etc/debian_version)"
elif [ -f /etc/redhat-release ]; then
        os=`cat /etc/redhat-release`
else
        os="$(uname -s) $(uname -r)"
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
source ~/.profile
fc-cache -fv

# Add nonfree if needed
#if $os = "Debian"; then
#  if ! grep -q non-free /etc/apt/sources.list; then
    sudo ln -s /etc/apt/sources.list.d/non-free.list ~/dotfiles/non-free.list
#  fi
#fi

# Install common utils
sudo apt-get update
sudo apt-get -y dist-upgrade
sudo apt-get -y install vim axel gpm command-not-found elinks build-essential ctags python-pip python-dev colorgcc colormake \
colordiff colortail ccze flex byacc libncurses5-dev libncursesw5-dev irssi irssi-dev irssi-scripts lshw pastebinit deborphan \
p7zip-full ntpdate beep firmware-linux-nonfree screen setserial autoconf libsqlite3-dev tmux

# Configure tty11 & tty12
sudo echo 'C:12345:wait:/usr/bin/tail -n30 -f /var/log/messages | /usr/bin/ccze > /dev/tty12' >> /etc/inittab
sudo echo "C:12345:wait:/usr/bin/setsid sh -c 'exec /usr/local/bin/glances <> /dev/tty11 >&0 2>&1'" >> /etc/inittab

#Install Glances
sudo pip install glances

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
