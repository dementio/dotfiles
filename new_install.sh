#!/bin/bash
if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root"
   exit 1
fi

# Setup environment
ln -fs ~/dotfiles/.bashrc ~/.bashrc
ln -fs ~/dotfiles/.profile ~/.profile
source ~/.profile
ln -s ~/dotfiles/.irssi ~/.irssi
ln -s ~/dotfiles/bin ~/bin
ln -s ~/dotfiles/.fonts ~/.fonts
fc-cache -fv

# Install common utils
sudo ln -s /etc/apt/sources.list.d/non-free.list ~/dotfiles/non-free.list
sudo apt-get update
sudo apt-get -y dist-upgrade
sudo apt-get -y install vim axel gpm command-not-found elinks build-essential ctags python-pip python-dev colorgcc colormake \
colordiff colortail ccze flex byacc libncurses5-dev libncursesw5-dev irssi irssi-dev irssi-scripts lshw pastebinit deborphan \
p7zip-full ntpdate beep firmware-linux-nonfree screen setserial

# Configure tty11 & tty12
sudo echo 'C:12345:wait:/usr/bin/tail -n30 -f /var/log/messages | /usr/bin/ccze > /dev/tty12' >> /etc/inittab
sudo echo 'C:12345:wait:/usr/local/bin/glances > /dev/tty11' >> /etc/inittab

#Install Glances
sudo pip install glances

# Install vimrc
ln -s ~/dotfiles/.vim_runtime ~/.vim_runtime
sh ~/.vim_runtime/install_awesome_vimrc.sh

# Build & install UnNetHack
cd ~/dotfiles/unnethack
./configure --enable-curses-graphics
make
sudo make install
sudo ln -fs ~/dotfiles/.nethackrc /usr/local/share/unnethack/unnethackrc.default

# Install YouTube-DL
sudo curl https://yt-dl.org/latest/youtube-dl -o /usr/local/bin/youtube-dl
sudo chmod a+x /usr/local/bin/youtube-dl

sudo update-command-not-found
beep
