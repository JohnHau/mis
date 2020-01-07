#!/bin/bash

if [ $# -lt 1 ]; then
echo "error: need at least 1 parameter"
else
   
   cat $1 |while read line
   do
	echo $line
	for e in "$line"
	do
	echo $e
	done

   done
fi


