#include <stdio.h>
#include <time.h>
#include "E101.h" 

//Basic methods to control the vehicle in the AVC

int adc_mean();
int turn_left(double turnTime);
int turn_right(double turnTime);
int forward();
int ifWall();
int slowReverse();

int main(){
	//This sets up the RPi hardware and ensures everything is working correctly
	init();
	printf("ADC Mean: %d /n", adc_mean());
	turn_left(0.5);
	turn_right(0.5);
	forward();
	ifWall();
	stop(0);
}

int adc_mean(){
	//We declare an integer variable to store the ADC data
	int adc_total = 0;
	int adc_mean;
	
	//Reads from Analog Pin 0 (A0) 
	for (int i=0; i<5; i++){
		adc_total += read_analog(0);
		sleep1(0,005000);	
	}
	
	adc_mean = adc_total/5;

	//Waits for 0.01 seconds
	sleep1(0,010000); 
	return adc_mean;
}

int turn_left(double turnTime){
	
	set_motor(1,0);
	sleep1(0,010000);
	set_motor(2,127); //assuming that motor 2 is right motor
	sleep1(0, turnTime * 1000000);
	stop(0);
	
return 0;}

int turn_right(double turnTime){
	
	set_motor(2,0);
	sleep1(0,010000);
	set_motor(1,127); //assuming that motor 1 is left motor
	sleep1(0, turnTime * 1000000);
	stop(0);
	
return 0;}

int forward(){
	
	set_motor(1,-255);
	sleep1(0,010000);//sleep may not be needed/wanted
	set_motor(2,255);
	sleep1(0,010000);
	
return 0;}

int slowReverse(){
	
	set_motor(1,100);
	sleep1(0,010000); //sleep may not be needed/wanted
	set_motor(2,-100);
	sleep1(0,010000);
	
return 0;}

int ifWall(){
	
	if (adc_mean() > 300){
		slowReverse();
	}
	
return 0;}
	
//picture reader needed
