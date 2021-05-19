#!/bin/bash


foo=/usr/local/bin/bar
echo "${foo##*/}"  #bar
echo "${foo%/*}"   #/usr/local/bin



 
path=`dirname $foo`
file=`basename $foo`


echo $path
echo $file


