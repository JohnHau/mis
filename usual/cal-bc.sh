#!/bin/bash

a=19
b=3

c=$(echo "scale=4;$a/$b" | bc)
echo $c
