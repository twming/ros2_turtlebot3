#!/usr/bin/env python3
import serial
from time import sleep

ser=serial.Serial(port="/dev/ttyAMA0",baudrate=9600)
received_data=""

while True:
    received_data=ser.read()
    sleep(0.03)
    data_left=ser.inWaiting()
    received_data+=ser.read(data_left)
    print(received_data)
    if (received_data.decode('utf-8')=="04#"):
        print("yes")
    else:
        print("no")
    
