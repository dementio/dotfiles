# ~/.profile: executed by the command interpreter for login shells.
# This file is not read by bash(1), if ~/.bash_profile or ~/.bash_login
# exists.
# see /usr/share/doc/bash/examples/startup-files for examples.
# the files are located in the bash-doc package.

# the default umask is set in /etc/profile; for setting the umask
# for ssh logins, install and configure the libpam-umask package.
#umask 022

# if running bash
if [ -n "$BASH_VERSION" ]; then
    # include .bashrc if it exists
    if [ -f "$HOME/.bashrc" ]; then
	. "$HOME/.bashrc"
    fi
fi

# set PATH so it includes user's private bin if it exists
if [ -d "$HOME/bin" ] ; then
    PATH="$HOME/bin:$PATH"
fi

[[ $TERM == "screen" ]] && export -p TERM="screen-256color"

update_display() {
    good_display=$(netstat -an | /bin/grep 0\ [0-9,:,.]*:60..\ | awk '{print $4}' | tail -n 1)
    good_display=${good_display: -2}
    export DISPLAY=${HOSTNAME}:${good_display}.0
}

#look_for_cmd=0
#print_cmd() {
#    if [ ${look_for_cmd} = 1 ] ;then
#        if [ "${BASH_COMMAND}" != 'print_host' ] ;then
#            cmdline=$(history 1 | xargs | cut -d\  -f3-)
#            if [[ "${cmdline}" =~ ^(sudo|ssh|vi|man|more|less)\  ]] ;then
#                first=$(echo "${cmdline}" | awk '{print (}')
#                for i in ${cmdline} ;do
#                    if ! [[ "${i}" =~ ^-.*$ ]] && ! [[ "${i}" =~ ^${first}$ ]] ;then
#                        cmd="${first}[${i}]"
#                        break
#                    fi
#                done
#            elif [[ "${cmdline}" =~ ^[A-Z]*=.*$ ]] ;then
#                cmd=$(echo ${cmdline} | awk '{print [}')
#            else
#                cmd=$(echo ${cmdline} | awk '{print (}')
#            fi
#            echo -ne "\033k${cmd}\033\\" 1>&2
#            look_for_cmd=0
#        else
#            return
#        fi
#    fi
#}
#
#print_host() {
#    echo -ne "\033k${HOSTNAME}\033\\" 1>&2
#    look_for_cmd=1
#}
#
#PROMPT_COMMAND="print_host"
#
#trap "print_cmd" DEBUG)])
