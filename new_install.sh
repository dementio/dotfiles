apt-get install vim axel git gpm command-not-found elinks build-essential ctags python-pip python-dev colorgcc colormake colordiff colortail ccze flex byacc libncurses5-dev libncursesw5-dev irssi irssi-dev irssi-scripts
pip install glances
sh ~/.vim_runtime/install_awesome_vimrc.sh
update-command-not-found
cd unnethack
./configure --enable-curses-graphics
make
cd
