//main avc program

#include <stdio.h>
#include "E101.h"

int frameRate = 40;

int adjust_trajectory(int err){
	int speed = 50;
	int kp = 2;
	int speed_left = speed - err*kp;
	int speed_right = speed + err*kp;
	//need scaleing factor
	printf("Left motor: %i \nRight Motor: %i \n",speed_left, speed_right);
	set_motor(2, speed_left);
	set_motor(1, speed_right);
	return 0;
}

int back_track(){
	return 0;
}

int doLine(){
	char pix = 0; //holds pixel's color and location
	char white [64]; //holds pixel's rounded color (0=black and 1=white) and location
	int err = 0; //error | how offcentered the robot is (-ve for left +ve for right and 0 is centered)
	int nwp = 0; //number of white pixels detected
	int test_points = 64; //can be adjusted
	int threshold_var = 100; //can be adjusted
	take_picture(); //take picture and store in memory
	int counter = 0;
	for(int i=0;i<320;i+=320/test_points){ 
		pix = get_pixel(120, i, 3); //save pixel color
		//printf("%i ", i);
		if(pix>threshold_var){
			white[counter] = 1; //round color
			//printf("1");
		}
		else{
			white[counter] = 0; //round color
			//printf("0");
		}
		counter++;
	}
	for (int i=0;i<test_points;i++){
		if(white[i] > 0){
			err = err + (i - test_points/2); //calculating how "off-trajectory" robot is
			nwp++; //+1 white pixel
		}
	}
	//printf("Error: %i \n",err);
	if(err != 0){ //if not centered
		err = err/nwp; //actual error on tracjectory
		printf("Error: %i \n",err);
		adjust_trajectory(err);
	}
	else{ //if centered
		back_track(); //go back because white line was lost
	}
	return 0;
}

int main (){
	init(); //initialiase hardware
	set_motor(1,50);
	set_motor(2,50);
	while(true){ //infinite loop
		doLine(); //executes line following method
		sleep1(0,1000000/frameRate); //|testing| adjust this to adjust framerate
	}
	return 0;
}
