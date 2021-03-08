#!/bin/bash

echo "Enter your lucky number"
read n

case $n in
101)
echo "you got 1st prize";;

510)
echo "you got 2nd prize";;

999)
echo "you got 3rd prize";;

*)
echo "sorry, try for the next time";;

esac
