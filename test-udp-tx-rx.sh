#!/bin/bash


echo whois > ufifo
sleep 1
echo quit > ufifo
sleep 1
echo good-bye
