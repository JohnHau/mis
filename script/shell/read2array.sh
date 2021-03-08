#!/bin/bash

str="hello,world bash"

read -ra rv <<< "$str"
#readarray -d= -t rv <<< "$str"

for word in "${rv[@]}";do

echo $word
done
