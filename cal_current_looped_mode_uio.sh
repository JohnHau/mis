#!/bin/bash
#like 0x31c1
if [ $# -lt 1 ];then
echo "less parameters"
exit
fi


let a=$1
#res=`echo "scale=4;(($a*1000*2.5)/65535)/100"|bc`
res=`echo "scale=2;(($a*25)/65535)"|bc`
echo "Current is $res mA"
