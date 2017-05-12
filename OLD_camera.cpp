#include <stdio.h>
#include <unistd.h>
#include <random>
#include <string> 
#include "E101.h"

int checkPicture(){//this function returns which direction (if any) to turn the robot and by how many degrees
	int pictureSum_left = 0;
	int pictureSum_right = 0;
	int rows = 240;
	int columns = 360;
	for(int i=1;i<columns+1;i+=4){//image is 360x240
		for(int j=1;j<rows+1;j+=4){// check every 4 pixels
			int pos [2] = {i, j};// X & Y
			int random_color =  1 + (rand() % (int)(255 - 1 + 1)); // this just replaces the get_pixel() function for debugging.
			if(i < 180){ //first half of image (left hand side
				if(random_color > (255/2)){
					pictureSum_left++; //add a white pixel
				}
			}
			else{ //right hand side
				if(random_color > (255/2)){ // current threshold, if color of pixel is 127 or more then its white, can be adjusted. 
					pictureSum_right++; //add a white pixel
				}
			}
		}
	}
	int difference = pictureSum_left - pictureSum_right; //we can use this difference to calculate how many degrees we need the robot to turn.
	if(pictureSum_left > pictureSum_right){ //more white pixels on the left hand side than the right hand side
		return 1;
	}
	else{
		return 0;
	}
}
int adjustTrajectory(int direction, int degrees){
	//set_motor(0,255);
	//et_motor(1,255);
	// here we will adjust the trajectory using functions like 15 degrees oand 30 degrees etc..
}
int main (){
	init();
	while(true){
		int white = checkPicture();
		if(white){ //if white == 1 then left hand side
			printf("turn left"); //can be changed to have a 50+- tollerance because the line will never be exactly centered.
		}
		else{ //right hand side
			printf("turn right");
		}
		usleep(25000); //this will change to sleep1(); once we run this on the raspberrypi, this makes it so we preform this action 40 times a second.
	}
	return 0;
}
