#include <stdio.h>
#include <time.h>
#include "E101.h"

int adjust_trajectory(int err){
	int speed = 100;
	int speed_left = speed + err*5;
	int speed_right = speed - err*5;
	//need scaleing factor
	
	//printf("%i,    sl %i , sr %i\n",err, speed_left, speed_right);
	return 0;
}

int back_track(){
	return 0;
}

int checkPicture(){
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
			printf("1");
		}
		else{
			white[counter] = 0; //round color
			printf("0");
		}
		counter++;
	}
	for (int i=0;i<test_points;i++){
		if(white[i] > 0){
			err = err + (i - test_points/2); //calculating how "off-trajectory" robot is
			nwp++; //+1 white pixel
		}
	}
	printf("\n");
	if(err != 0){ //if not centered
		err = err/nwp; //actual error on tracjectory
		//printf("Error: %i \n",err);
		adjust_trajectory(err);
	}
	else{ //if centered
		back_track(); //go back because white line was lost
	}
	return 0;
}
int main (){
	init(); //initialiase hardware

	while(true){ //infinite loop
		checkPicture(); //check picture
		sleep1(0,025000); //|testing| adjust this to adjust framerate
	}
	return 0;
}
