#!/bin/bash


#like 0x31c1
if [ $# -lt 1 ];then
echo "less parameters"
exit
fi

while read val
do
val="0x"$val


let tval=$val 

echo $tval
res=`echo "scale=4;($tval*2100)/(65535-$tval)"|bc`
echo "R is $res hom"
done < $1

#let a=$1
#
#res=`echo "scale=4;($a*2100)/(65535-$a)"|bc`
#
#echo "R is $res hom"
#
