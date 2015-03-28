# nixie-1
Code to get rpi communicating with ogilumen nixie driver.

There are a lot of useless files here. nixie.c is actaul funtioning C code but I decided to use python instead. Just execute nixie.py and the time will be displayed on the nixie tubes.

This code requires the following libraries;


SPI

sudo apt-get install python-dev

mkdir python-spi

cd python-spi

wget https://raw.github.com/doceme/py-spidev/master/setup.py

wget https://raw.github.com/doceme/py-spidev/master/spidev_module.c

sudo python setup.py install
