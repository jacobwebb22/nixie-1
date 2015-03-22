#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

int channel = 0;
int speed = 4000000;

int main (void)
{
	wiringPiSetup () ;
	wiringPiSPISetup (channel, speed) ;

	unsigned char one = 1;
    unsigned char two = 2;
    one = one << 4;
    unsigned char Text = one + two;

	for (int i = 1; i <= 10000000; i++)
	{
	wiringPiSPIDataRW (channel, &Text, sizeof(Text)) ;
	std::cout << i << std::endl;
	}

}