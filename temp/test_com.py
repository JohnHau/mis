#!/usr/bin/python
import time
import serial

print ("------------------------------------------------------------------------------------------------")
print ("sdram enable, sdram disable, ecc608 enable, ecc608 disable")
print ("led 1 100, wifi disable, ble disable, ethernet enable, ethernet disable")
print ("uio ch01 vo 10, uio ch01 co 20, uio ch01 rtd, uio ch01 vi, uio ch01 ci, uio ch01 di ")
print ("bi ch01, bi ch02, relay1 1, relay1 0, spectrum enable, spectrum disable, sdram_clk 7")
print ("lpspi4 enable, lpspi4 disable, lpi2c3 enable, lpi2c3 disable")
print ("------------------------------------------------------------------------------------------------")
time.sleep(3)
 
# 连接
ser = serial.Serial()
print ("CQ test start")



cmd= [

  "ecc608 enable\r\n",
  "sdram enable\r\n",
 
  
  "uio ch01 vo 10\r\n",
  "uio ch02 vo 10\r\n",
  "uio ch03 vo 10\r\n",
  "uio ch04 vo 10\r\n",

  "wifi disable\r\n",
  "ble disable\r\n",
  "ethernet disable\r\n",
  "sdram disable\r\n",
  "ecc608 disable\r\n",

  "bi ch01\r\n",
  "spectrum enable\r\n",
  "sdram_clk 7\r\n",
  "lpspi4 enable\r\n",
  "lpi2c3 enable\r\n",
  
  ];

i=0
cnt=0
#ser.port = 'COM14'
ser.port = '/dev/ttyS13'
ser.baudrate = 115200
ser.timeout = 3
ser.open()
 
testStr="hello"
# 接收返回的信息
while True:
    tc=cmd[i]

    for c in cmd[i]:
        #ser.write(c)
        ser.write(c.encode("gbk"))
        time.sleep(0.02)

    #result=ser.write(cmd[i].encode("gbk"))
    i =i+1
    #time.sleep(3)
    recv = ser.readlines()
    print(recv)
  
    #recv = ser.readline()
    #print(recv)
    time.sleep(2)

    #if str(recv) == "q":
    #break
    if(i >15):
        break


   
ser.close()


time.sleep(2)
