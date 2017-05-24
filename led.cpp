#include <stdio.h>
#include <time.h>
#include "E101.h" 

//Light

int main(){
	//This sets up the RPi hardware and ensures everything is working correctly
	init();
	while(true){
		set_PWM(7,150);
	}
}
