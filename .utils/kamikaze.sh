#!/bin/bash
msg1=(	' █████  ██    ██ ████████  ██████  ██████  ███████ ███████ ████████ ██████  ██    ██  ██████ ████████ ██  ██████  ███    ██     ██ ███    ██         '
		'██   ██ ██    ██    ██    ██    ██ ██   ██ ██      ██         ██    ██   ██ ██    ██ ██         ██    ██ ██    ██ ████   ██     ██ ████   ██         '
		'███████ ██    ██    ██    ██    ██ ██   ██ █████   ███████    ██    ██████  ██    ██ ██         ██    ██ ██    ██ ██ ██  ██     ██ ██ ██  ██         '
		'██   ██ ██    ██    ██    ██    ██ ██   ██ ██           ██    ██    ██   ██ ██    ██ ██         ██    ██ ██    ██ ██  ██ ██     ██ ██  ██ ██         '
		'██   ██  ██████     ██     ██████  ██████  ███████ ███████    ██    ██   ██  ██████   ██████    ██    ██  ██████  ██   ████     ██ ██   ████ ██ ██ ██')

msg2=(	'██████         ██████          ██'
		'   ░░██           ░░██        ███'
		' █████          █████          ██'
		'   ░░██        ██░░            ██'
		'█████          ███████         ██')

red='\e[38;5;196;1m';
reset='\e[0m';
clrline='\r\e[0K\e[4A'

PrintArt() {
	i=$2;
	local -n array=$4
	while [ $i -le $1 ] ;
	do
		printf $red ;
		for str in "${array[@]}" ;
		do
			printf "%.*s" "$i" "$str" ;
			if [ "$str" != "${array[-1]}" ] ; then printf "\n" ; fi
		done
		printf $reset ;
		sleep $3 ;
		if [ $(($i + $2)) -le $1 ] ; then printf $clrline ; fi ;
		((i+=$2)) ;
	done
	printf "\n" ;
	printf "\n" ;
}

clear ;
pactl set-sink-volume @DEFAULT_SINK@ 35%
if  command -v aplay &> /dev/null
then
	(aplay --quiet ./coffindance.wav &> /dev/null &)
elif command -v paplay &> /dev/null
then
	(paplay --volume=65536 ./coffindance.wav &> /dev/null &) #volume max == 65536
fi

#trap '' 2 #ignore
PrintArt 346 16 0.092 msg1
PrintArt 70 23 0.97 msg2
(cat /dev/urandom &)
