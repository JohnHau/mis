#!/bin/bash


while read line
do
echo $line
#awk '{print $1}'  $line
for w in $line
do

echo "it is $w"
done

done < a.log
