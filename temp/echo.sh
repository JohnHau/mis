#!/bin/bash
valid=0
count=1


while [ $valid ]
do
echo $count

if [ $count -eq 5 ]
then
#break
valid=
fi

((count++))

done

