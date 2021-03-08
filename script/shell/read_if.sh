#!/bin/bash

#echo "Enter username"
#read username
#echo "Enter password"
#read password 
#


#if [[ ($username == "admin" && $password == "secret") ]] 
#then
#echo "valid user"
#else
#echo "invalid user"
#fi
#

#if [[ ($username == "admin" && $password == "secret") ]];then 
#echo "valid user"
#else
#echo "invalid user"
#fi







#################################################
#next block
#################################################

echo "Enter any number"
read n

if [[ $n -eq 15 || $n -eq 45 ]]
then
echo "you won the game"
else
echo "you lost the game"
fi



