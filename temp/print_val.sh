#!/bin/bash
#print 0x5F


#print ASCII
printf '\x5f'


#print 0x5F in binary
dc -e '16i2o5Fp'

printf '\x5F' | xxd -b | cut -d' ' -f2


echo "ibase=16;obase=2;5F" | bc


#NUM_DEC2BIN=({0..1}{0..1}{0..1}{0..1}{0..1}{0..1}{0..1}{0..1})
NUM_DEC2BIN=({0,1}{0,1}{0,1}{0,1}{0,1}{0,1}{0,1}{0,1})
#echo "$NUM_DEC2BIN[@]"

echo ${NUM_DEC2BIN[21]}

#To remove leading zeros, e.g. from ${NUM_DEC2BIN[7]}
echo $((10#${NUM_DEC2BIN[7]}))


bc <<< "obase=16;1024"



echo 65 66 67 68 | xxd -r -p
echo \x36 \x37 | xxd -r -p


test_a=39
echo $((0x$test_a))
printf "%x"   $((0x$test_a))



#print ASCII
echo -e '\x5a'





