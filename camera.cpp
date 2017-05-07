#include <stdio.h>
#include "E101.h"
int main (){
	init();
	int counter = 0; //debugging
	 while(true){
	 	checkPath();
	 	sleep1(1/30);
	 	counter ++; //debugging
	 	if(counter == 30){
	 		break;
	 	}
	 }
	return 0;
}
int checkPath(){
	take_picture(); //takes picture
	int centered = checkPicture();
	if(centered == 0){// if off trajectory
		adjustTrajectory(); //adjust it
	}
	return 0;
}
int checkPicture(){//this function returns 0 if off trajectory and 1 if on trajectory
	//Part 1
	//Save image to array
	int[] pictureArray_left = new int[21600];
	int[] pictureArray_right = new int[21600];
	int rows = 240;
	int columns = 360;
	for(int i=0;i<columns;i+2){//image is 360x240
		for(int j=0;j<rows;j+=2){// check every 2 pixels
			int pixelColor = get_pixel(i,j,3);
			int pos = j*i;
			if(pos < 21600){ //left hand side of picture
				pictureArray_left[pos] = pixelColor;
			}
			else{//right hand side of picture
				pictureArray_right[pos] = pixelColor;
			}
		}
	}
	//Psudo code
	//if pictureArray_left > pictureArray_right then road is to the left and should turn left, otherwise right etcc.
	
}
int adjustTrajectory(){
	//set_motor(0,255);
	//et_motor(1,255);
	// here we will adjust the trajectory using functions like 15 degrees oand 30 degrees etc..
}