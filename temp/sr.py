#!/usr/bin/python

import serial
import time 

ser=serial.Serial("/dev/ttyS0",9600,timeout=0.5) 

#ser.open()

#ser.write("hello\r\n".encode("gbk"))
while 1:
    data=ser.readline()
    time.sleep(1)
    print(data)
ser.close()

