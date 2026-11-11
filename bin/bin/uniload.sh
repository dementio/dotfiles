#! /bin/sh

STATS_FILE=/var/tmp/${USER}_stats_top
DELAY=1

# FreeBSD uses jot(1) while Linux uses seq(1)
which jot 1> /dev/null 2> /dev/null || alias jot=seq

__freebsd() {
    top -s ${DELAY} -d 2 0  \
        | grep -m 1 CPU \
        | sed 's/,//g' \
        | awk '{ print %2": "$3" | "$4": "$5" | "$6": "$7" | "$8": "$9" | "$10": "$11 }'
    }

__linux() {
    top -d ${DELAY} -n 2 -b \
        | grep -m 2 Cpu \
        | tail -1 \
        | sed 's/%/ /g' \
        | awk '{ print "user: " $2 " | system: " $4 " | nice: " $6 " | idle: " $8 }'
    }

__exit() {
    rm -rf ${STATS_FILE}
    exit 0
    }

trap '__exit' 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
OS=$( uname )
while true
do
    for I in $( jot 128 ); do
        case ${OS} in
            (FreeBSD) __freebsd >> ${STATS_FILE} 2>&1 ;;
            (Linux)   __linux   >> ${STATS_FILE} 2>&1 ;;
            (*)       echo "supported systems: FreeBSD Linux"; exit 1 ;;
        esac
    done
    sleep 1
    :> ${STATS_FILE}
done
