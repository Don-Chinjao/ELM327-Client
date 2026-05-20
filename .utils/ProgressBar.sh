#!/bin/bash

green='\e[38;5;46;1m'
red='\e[31;1m'
white='\e[38;5;15;1m'
reset='\e[0m'

ProgressBar() {
	name=$1 ; nb_files=$2 ; count=$3 ; lastfile=$4 ;			
	if [ $name = $lastfile ] ; then name="[DONE]" ; fi ;
	progress=`echo "($count*100)/$nb_files" | bc`;
	done=`echo "($progress*30)/100" | bc` ;
	left=`echo "30-$done" | bc` ;
	fill=`printf "%*s" $done | sed 's/ /█/g'` ;
	empty=`printf "%*s" $left | sed 's/ /█/g'` ;
	if [ $count = 1 ] ; then line="$white Compiling source files		: \n\n" ; fi ;
	line+="\r\e[0K $green$fill$red$empty$reset $white$progress%% $green$name$reset" ;
	printf "$line" ;
}

ProgressBar $1 $2 $3 $4
