#!/usr/bin/env python3
import RPi.GPIO as GPIO
import time
import serial
GPIO.setwarnings(False)

M1 = 7
M2 = 8
M3 = 9
M4 = 10
LED = 5
BUT = 6
GPIO.setmode(GPIO.BCM)
GPIO.setup(M1, GPIO.OUT)
GPIO.setup(M2, GPIO.OUT)
GPIO.setup(M3, GPIO.OUT)
GPIO.setup(M4, GPIO.OUT)
GPIO.setup(LED,GPIO.OUT)
GPIO.setup(BUT,GPIO.IN)
cmd='N'
state=0


def setMotor(S1,S2,S3,S4,timeInSec):
    GPIO.output(M1,S1)
    GPIO.output(M2,S2)
    GPIO.output(M3,S3)
    GPIO.output(M4,S4)
    time.sleep(timeInSec)

setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)

try:
    while True:
        button_state=GPIO.input(BUT)
        if (GPIO.input(BUT)):
            if state:
                state=0
            else:
                state=1
            time.sleep(1)

        if (state==1):
            GPIO.output(LED,GPIO.HIGH)

            match cmd:
                case 'N':
                    setMotor(GPIO.HIGH,GPIO.LOW,GPIO.HIGH,GPIO.LOW,0.025)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.025)

                case 'S':
                    setMotor(GPIO.LOW,GPIO.HIGH,GPIO.LOW,GPIO.HIGH,0.025)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.025)

                case 'W':
                    setMotor(GPIO.HIGH,GPIO.LOW,GPIO.LOW,GPIO.HIGH,0.025)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.025)
                    
                case 'E':
                    setMotor(GPIO.LOW,GPIO.HIGH,GPIO.HIGH,GPIO.LOW,0.025)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.025)

                case 'A':
                    setMotor(GPIO.HIGH,GPIO.LOW,GPIO.HIGH,GPIO.LOW,0.010)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.HIGH,GPIO.LOW,0.030)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)
                    
                case 'D':
                    setMotor(GPIO.HIGH,GPIO.LOW,GPIO.HIGH,GPIO.LOW,0.010)
                    setMotor(GPIO.HIGH,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.030)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)

                case 'B':
                    setMotor(GPIO.LOW,GPIO.HIGH,GPIO.LOW,GPIO.HIGH,0.010)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.HIGH,0.030)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)

                case 'C':
                    setMotor(GPIO.LOW,GPIO.HIGH,GPIO.LOW,GPIO.HIGH,0.010)
                    setMotor(GPIO.LOW,GPIO.HIGH,GPIO.LOW,GPIO.LOW,0.030)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)

                case '0':
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)

            #print(cmd)
        else:
            GPIO.output(LED,GPIO.LOW)
            setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)

except KeyboardInterrupt:
    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)


