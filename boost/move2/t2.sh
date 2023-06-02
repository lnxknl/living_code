#!/bin/bash
counter=0
#counter=59
while read line
do
	((counter++))
	if [ $counter -gt 60 ]
	then
		echo "enter sleep"
		counter=0
		sleep 1200
#		sleep 4
		echo "outter sleep"
	fi
	echo $line  >>kernel_out.txt
	echo "=====" >>kernel_out.txt
    	python client2.py "$line" >>kernel_out.txt
	echo $line
	echo "=====" >>kernel_out.txt
#    sleep 1800
done
