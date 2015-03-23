#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void)
{
	int speed = 4000000;
	int channel = 0;

	unsigned char one = 0;
	unsigned char two = 0;
	unsigned char Text = 0;

	wiringPiSetup () ;
	wiringPiSPISetup (channel, speed) ;

	int i = 0;
	for (i = 1; i <= 5; i++)
	{

	one = i%10;
	two = i/10;
	one = one << 4;
	Text = one + two;

	wiringPiSPIDataRW (channel, &Text, 1) ;
	printf( "%d\n", i);
	delay(1000);
	}

	return 0 ;
}
