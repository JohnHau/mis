#!/bin/bash
IP=192.168.0.108
PORT=47808
echo "whois"
echo "whois" > /dev/udp/${IP}/${PORT}

sleep 5



echo "whois"
#echo "whois" > /dev/udp/192.168.0.105/47808
echo "whois" > /dev/udp/${IP}/${PORT}


sleep 5
echo "quit"
#echo "quit" > /dev/udp/192.168.0.105/47808
echo "quit" > /dev/udp/${IP}/${PORT}
