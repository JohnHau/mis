#!/bin/bash

file='test.log'



if [ -f $ifle ]
then
touch $file
echo "a b c line" >> $file
echo "gogogle good" >> $file
echo "last last cool" >> $file
else
echo "existed"
fi

while read line
do
echo $line
done <$file
