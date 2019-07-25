/*
Add support for the screen auto rotation to most non-convertable laptop.
Made By TinLethax, Thanks to Giovanni Bauermeister for the driver library
https://github.com/giobauermeister/ads1115-linux-rpi
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "ads1115_rpi.h"

float Ax , Ay ;
float PrevX , PrevY ;

int main(void){
//system ("dmesg"); 
	if(openI2CBus("/dev/i2c-1") == -1)
	{
		printf("Can't connect to the ADS1115 \n");
		printf("Please check the connection, ADC, Sensor");
	}else {
	setI2CSlave(0x48); // set the I2C address of the ADS1115 at 0x48
	while(1){
	sleep(1.6);// delay like in the mobile phone 	
	
	Ax = readVoltage(0); // read the X axis voltage value on the ADC port A0
	Ay = readVoltage(1); // read the Y axis voltage value on the ADC port A1
	
	if ( (PrevX < (Ax + 0.1)) || (PrevX > (Ax + 0.1)) || (PrevX != Ax) ){
		if ((Ax < 0.410 && Ax > 0.38) && (Ay != Ax))  {
		system ("xrandr --output LVDS-1-1 --rotate right");// rotate right
		}	else if ((Ax < 0.28 && Ax > 0.24) && (Ay != Ax)) {
		system ("xrandr --output LVDS-1-1 --rotate left");// rotate left
		}
	}else if ( (PrevX < (Ax + 0.1)) || (PrevX > (Ax + 0.1)) || (PrevX == Ax) ) {
		return 0;
	}

	if ( (PrevY < (Ay + 0.1)) || (PrevY > (Ay + 0.1)) || (PrevY != Ay) ){
		if ((Ay < 0.410 && Ay > 0.38) && (Ay != Ay))  {
		system ("xrandr --output LVDS-1-1 --rotate inverted");// rotate inverted
		}	else if ((Ay < 0.28 && Ay > 0.24) && (Ay != Ax)) {
		system ("xrandr --output LVDS-1-1 --rotate normal");// rotate normal
		}
	}else if ( (PrevY < (Ay + 0.1)) || (PrevY > (Ay + 0.1)) || (PrevY == Ay) ) {
		return 0;
	}

	Ax = PrevX;
	Ay = PrevY;
	}
}
}