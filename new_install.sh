mv non-free.list /etc/apt/sources.list.d/
apt-get update
apt-get -y dist-upgrade
apt-get -y install vim axel git gpm command-not-found elinks build-essential ctags python-pip python-dev colorgcc colormake \
colordiff colortail ccze flex byacc libncurses5-dev libncursesw5-dev irssi irssi-dev irssi-scripts lshw pastebinit deborphan \
p7zip-full ntpdate beep firmware-linux-nonfree screen setserial
echo 'C:12345:wait:/usr/bin/tail -n30 -f /var/log/messages | /usr/bin/ccze > /dev/tty12' >> /etc/inittab
echo 'C:12345:wait:/usr/local/bin/glances > /dev/tty11' >> /etc/inittab
pip install glances
#git clone https://github.com/amix/vimrc.git .vim_runtime
sh ~/.vim_runtime/install_awesome_vimrc.sh
update-command-not-found
#git clone http://git.code.sf.net/p/unnethack/git unnethack
cd unnethack
./configure --enable-curses-graphics
make
make install
cd
mv .nethackrc /usr/local/share/unnethack/unnethackrc.default
beep
