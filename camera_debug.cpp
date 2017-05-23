//similar code to camera_test, but prints ASCII version of line instead of moving motors

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
	int nwp = 0; //number of white pixels detected
	int test_points = 64; //can be adjusted
	int threshold_var = 100; //can be adjusted
	take_picture(); //take picture and store in memory
	printf("image: \n");
	for(int i=0;i<320;i+=320/test_points){ 
		pix = get_pixel(120, i, 3); //save pixel color
		//printf("%i ", i);
		if(pix>threshold_var){
			printf("1");
		}
		else{
			printf("0");
		}
		
	} 
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	for(int i=0;i<320;i+=320/test_points){ 
		pix = get_pixel(20, i, 3); //save pixel color
		//printf("%i ", i);
		if(pix>threshold_var){
			printf("1");
		}
		else{
			printf("0");
		}
	}
	
	printf("\n");
	
	return 0;
}
int main (){
	init(); //initialiase hardware

	while(true){ //infinite loop
		checkPicture(); //check picture
		sleep1(0,700000); //|testing| adjust this to adjust framerate
	}
	return 0;
}
