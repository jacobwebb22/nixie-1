#!/usr/bin/python

import spidev
import time
import datetime

spi = spidev.SpiDev()
spi.open(0,0)

for i in range(1,100):
	one=datetime.datetime.now().second%10
	two=datetime.datetime.now().second/10
	one = one<<4
	Text = one + two
	spi.xfer2([Text])
	time.sleep(0.1)   # sleep in seconds
# end for

spi.close()  
