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
	for (i = 1; i <= 5000; i++)
	{

//	struct tm *tm_struct = localtime(time(NULL));

	time_t rawtime;
	struct tm *info;
//	char buffer[80];
	time( &rawtime );
	info = localtime( &rawtime );

	one = (unsigned char)info->tm_sec%10;
	two = (unsigned char)info->tm_sec/10;
	one = one << 4;
	Text = one + two;

	wiringPiSPIDataRW (channel, &Text, 1) ;
	printf( "%d\n", i);
	delay(10);
	}

	return 0 ;
}
