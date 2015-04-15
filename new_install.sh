apt-get install vim axel git gpm command-not-found elinks build-essential ctags python-pip python-dev colorgcc colormake colordiff colortail ccze flex byacc libncurses5-dev libncursesw5-dev
pip install glances
git clone https://github.com/amix/vimrc.git ~/.vim_runtime
sh ~/.vim_runtime/install_awesome_vimrc.sh
git clone http://git.code.sf.net/p/unnethack/git unnethack
update-command-not-found
cd unnethack
./configure --enable-curses-graphics
make
cd
