import math
import sys
import numpy as np
import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

global solPin=15#BCM 22
global floPin=11#BCM 17
global tickVol=206#1000mL/485 pulses 2.06 mL/pulse

GPIO.setup(solPin, GPIO.OUT)
GPIO.setup(floPin, GPIO.IN)

class flo():
    def __init__(self):
        self.clicks=0
        self.last=time.time()
        self.now=time.time()
    def update():  
        self.clicks++
        self.last=self.now()
        self.now()=time.time()
    def clear():
        self.clicks=0
        self.last=time.time()
        self.now=time.time()
    def vol():
        return 2.06*self.clicks
    def delta():
        return self.now-self.last

meter = flo()
GPIO.add_event_detect(floPin, GPIO.RISING, callback=flo.update)

while
    


