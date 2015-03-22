#include <fcntl.h>				//Needed for SPI port
#include <sys/ioctl.h>			//Needed for SPI port
#include <linux/spi/spidev.h>	//Needed for SPI port
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


int spi_cs0_fd;				//file descriptor for the SPI device
int spi_cs1_fd;				//file descriptor for the SPI device

int spifd;
int SpiOpenPort();
int SpiClosePort();

unsigned char spi_mode;
unsigned char spi_bitsPerWord;
unsigned int spi_speed;


using namespace std;
 

int main(void)
{

    SpiOpenPort(0);

    unsigned char one = 1;
    unsigned char two = 2;
    one = one << 4;
    unsigned char Text = one + two;

    for (int i = 1; i <= 10; i++)
    {
    int SpiWriteRead(0, *Text, int sizeof(Text));
    cout << i << endl;
    }

    SpiClosePort(0);
   
}

//********************************
// NIXIE CODE
//********************************


/*
byte[] GetBytes()
{
    byte[] Text = new byte[5];

    byte one = (byte)(DateTime.Now.Day % 10);
    byte two = (byte)(DateTime.Now.Day / 10);
    one = (byte)(one << 4);
    Text[0] = (byte)(one + two);

    one = (byte)(DateTime.Now.Month % 10);
    two = (byte)(DateTime.Now.Month / 10);
    one = (byte)(one << 4);
    Text[1] = (byte)(one + two);

    one = (byte)(DateTime.Now.Second % 10);
    two = (byte)(DateTime.Now.Second / 10);
    one = (byte)(one << 4);
    Text[2] = (byte)(one + two);

    one = (byte)(DateTime.Now.Minute % 10);
    two = (byte)(DateTime.Now.Minute / 10);
    one = (byte)(one << 4);
    Text[3] = (byte)(one + two);

    int hournew = DateTime.Now.Hour;

    if (hournew > 12) { hournew = hournew - 12; }
    one = (byte)(hournew % 10);
    two = (byte)(hournew / 10);
    one = (byte)(one << 4);
    Text[4] = (byte)(one + two); 

    return Text;
}



byte[] ReturnDigits(int[] digits)
{
    byte[] WriteBuffer = new byte[5];

    int count = 0;

    for (int i = 4; i >= 0; i-- )
    {
        byte one = (byte)digits[(2*i)+1];
        one = (byte)(one << 4);
        byte two = (byte)digits[(2*i)];
        byte out1 = (byte)(one + two);
        WriteBuffer[count] = out1;
        count++;
    }

    return WriteBuffer;
}


*/



//********************************
// SPI Interface
//********************************

//********** SPI OPEN PORT **********

//spi_device	0=CS0, 1=CS1

int SpiOpenPort (int spi_device)
{
	int status_value = -1;
    int *spi_cs_fd;

    // Following line is from netduino setup
    //SPI.Configuration Tubes = new SPI.Configuration(Pins.GPIO_PIN_D7, false, 0, 0, false, true, 4000, SPI.SPI_module.SPI1);

    //----- SET SPI MODE -----
    //SPI_MODE_0 (0,0) 	CPOL = 0, CPHA = 0, Clock idle low, data is clocked in on rising edge, output data (change) on falling edge
    //SPI_MODE_1 (0,1) 	CPOL = 0, CPHA = 1, Clock idle low, data is clocked in on falling edge, output data (change) on rising edge
    //SPI_MODE_2 (1,0) 	CPOL = 1, CPHA = 0, Clock idle high, data is clocked in on falling edge, output data (change) on rising edge
    //SPI_MODE_3 (1,1) 	CPOL = 1, CPHA = 1, Clock idle high, data is clocked in on rising, edge output data (change) on falling edge
    
    // For 74hc595 sample rising edge, clock idle low => mode 0

    spi_mode = SPI_MODE_0;
    
    //----- SET BITS PER WORD -----
    spi_bitsPerWord = 8;
    
    //----- SET SPI BUS SPEED -----
    //spi_speed = 1000000;		//1000000 = 1MHz (1uS per bit)
    // 4000 khz = 4Mhz
    spi_speed = 4000000;

    if (spi_device)
    	spi_cs_fd = &spi_cs1_fd;
    else
    	spi_cs_fd = &spi_cs0_fd;


    if (spi_device)
    	*spi_cs_fd = open(std::string("/dev/spidev0.1").c_str(), O_RDWR);
    else
    	*spi_cs_fd = open(std::string("/dev/spidev0.0").c_str(), O_RDWR);

    if (*spi_cs_fd < 0)
    {
        perror("Error - Could not open SPI device");
        exit(1);
    }

    status_value = ioctl(*spi_cs_fd, SPI_IOC_WR_MODE, &spi_mode);
    if(status_value < 0)
    {
        perror("Could not set SPIMode (WR)...ioctl fail");
        exit(1);
    }

    status_value = ioctl(*spi_cs_fd, SPI_IOC_RD_MODE, &spi_mode);
    if(status_value < 0)
    {
      perror("Could not set SPIMode (RD)...ioctl fail");
      exit(1);
    }

    status_value = ioctl(*spi_cs_fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bitsPerWord);
    if(status_value < 0)
    {
      perror("Could not set SPI bitsPerWord (WR)...ioctl fail");
      exit(1);
    }

    status_value = ioctl(*spi_cs_fd, SPI_IOC_RD_BITS_PER_WORD, &spi_bitsPerWord);
    if(status_value < 0)
    {
      perror("Could not set SPI bitsPerWord(RD)...ioctl fail");
      exit(1);
    }

    status_value = ioctl(*spi_cs_fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed);
    if(status_value < 0)
    {
      perror("Could not set SPI speed (WR)...ioctl fail");
      exit(1);
    }

    status_value = ioctl(*spi_cs_fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed);
    if(status_value < 0)
    {
      perror("Could not set SPI speed (RD)...ioctl fail");
      exit(1);
    }
    return(status_value);
}


//********** SPI CLOSE PORT **********


int SpiClosePort (int spi_device)
{
	int status_value = -1;
    int *spi_cs_fd;

    if (spi_device)
    	spi_cs_fd = &spi_cs1_fd;
    else
    	spi_cs_fd = &spi_cs0_fd;


    status_value = close(*spi_cs_fd);
    if(status_value < 0)
    {
    	perror("Error - Could not close SPI device");
    	exit(1);
    }
    return(status_value);
}


//********** SPI WRITE & READ DATA **********

//data		Bytes to write.  Contents is overwritten with bytes read.

int SpiWriteRead (int spi_device, unsigned char *data, int length)
{
	struct spi_ioc_transfer spi[length];
	int i = 0;
	int retVal = -1;
    int *spi_cs_fd;

    if (spi_device)
    	spi_cs_fd = &spi_cs1_fd;
    else
    	spi_cs_fd = &spi_cs0_fd;

	//one spi transfer for each byte

	for (i = 0 ; i < length ; i++)
	{
		spi[i].tx_buf        = (unsigned long)(data + i); // transmit from "data"
		spi[i].rx_buf        = (unsigned long)(data + i) ; // receive into "data"
		spi[i].len           = sizeof(*(data + i)) ;
		spi[i].delay_usecs   = 0 ;
		spi[i].speed_hz      = spi_speed ;
		spi[i].bits_per_word = spi_bitsPerWord ;
		spi[i].cs_change = 0;
	}

	retVal = ioctl(*spi_cs_fd, SPI_IOC_MESSAGE(length), &spi) ;

	if(retVal < 0)
	{
		perror("Error - Problem transmitting spi data..ioctl");
		exit(1);
	}

	return retVal;
}


