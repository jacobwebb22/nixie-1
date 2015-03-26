#!/usr/bin/python

import spidev
import time
import datetime

spi = spidev.SpiDev()
spi.open(0,0)

for i in range(1,200):
	current = datetime.datetime.now()
	one=current.second%10
	two=current.second/10
	one = one<<4
	seconds = one + two
	one=current.minute%10
        two=current.minute/10
        one = one<<4
        minutes = one + two
	spi.writebytes([seconds, minutes])
	time.sleep(0.1)   # sleep in seconds
# end for

spi.close()  
