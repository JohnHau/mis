#!/bin/bash
#like 0x31c1
if [ $# -lt 1 ];then
echo "less parameters"
exit
fi


let a=$1
cur=`echo "scale=4;($a/65535)*2.5*10"|bc`
echo "cur is $cur ma"
