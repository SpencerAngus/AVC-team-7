#include <stdio.h>
#include <time.h>
#include "E101.h" 

//Light

int main(){
	//This sets up the RPi hardware and ensures everything is working correctly
	init();
	select_IO(7, 0);
	while(true){
		set_PWM(7,150);
	}
}
