import math
import sys
import numpy as np
import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

global solPin
solPin=15#BCM 22
global floPin
floPin=11#BCM 17
global tickVol
tickvol=2.06#1000mL/485 pulses 2.06 mL/pulse

GPIO.setup(solPin, GPIO.OUT)
GPIO.setup(floPin, GPIO.IN)

class flo():

    def __init__(self):
        self.clicks=0
        self.last=time.time()
        self.now=time.time()
        self.start=time.time()
        GPIO.add_event_detect(floPin, GPIO.RISING, callback=self.update)

    def update(self, channel):  
        self.clicks=self.clicks+1
        self.last=self.now
        self.now=time.time()
        print(str(self.vol()) +" mL in "+ str(self.delta()) + " seconds " + str(self.clicks) + " on channel " + str(channel))

    def clear(self):
        self.clicks=0
        self.last=time.time()
        self.now=time.time()
        self.start=time.time()

    def vol(self):
        return tickvol*self.clicks

    def delta(self):
        return self.now-self.start

f = flo()

while True:
    dose=input("what volume? in mL.")
    GPIO.output(solPin, False)
    while f.vol()<dose:
        GPIO.output(solPin, True)
        
    f.clear()

    


