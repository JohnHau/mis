#!/bin/bash
#like 0x31c1
if [ $# -lt 1 ];then
echo "less parameters"
exit
fi


let a=$1
res=`echo "scale=4;($a*2100)/(65535-$a)"|bc`
echo "R is $res hom"
