#!/bin/bash


echo "send rol" > udp-fifo
#echo "send testrol" > udp-fifo
exit 0


i=0
while [ $i -lt 10 ]
do
	#echo "send rv" > udp-fifo
	#sleep 1
	echo "send rol" > udp-fifo
	i=$((i+1))
	sleep 1
done



#echo "send rv" >udp-fifo
#sleep 2
#echo "send rol" >udp-fifo
