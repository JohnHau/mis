#!/bin/bash

for e in `ls *.txt *.log`
do


mv $e sub_$e
echo $e




done


echo "done"
