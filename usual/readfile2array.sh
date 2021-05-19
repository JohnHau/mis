#!/bin/bash

while read -a line
do
echo ${line[0]}
echo ${line[1]}
done < $1
