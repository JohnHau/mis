#!/bin/bash
#echo $#
#if [ $# -lt 1 ];then
#	echo "parameters error"
#	exit
#fi
rv=`echo "scale=2;$1*2100/(65535-$1)"| bc`
echo "The result is $rv"
#echo "hello world"
