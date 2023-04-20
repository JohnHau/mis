#!/bin/bash

./uwrite.exe /dev/ttyS3 conf.json
sleep 8

./uwrite.exe /dev/ttyS3 false.json
sleep 8
./uwrite.exe /dev/ttyS3 false.json

echo done
