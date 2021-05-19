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



for((fcnt=0;fcnt<5;fcnt++))
do
echo "fcnt is $fcnt"
done



