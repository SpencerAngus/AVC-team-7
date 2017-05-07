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
			int random_color =  1 + (rand() % (int)(255 - 1 + 1));
			if(i < 180){
				if(random_color > (255/2)){
					pictureSum_left++; //1 is white
				}
			}
			else{
				if(random_color > (255/2)){
					pictureSum_right++;
				}
			}
			counter ++;
		}
	}
	int difference = pictureSum_left - pictureSum_right;
	if(pictureSum_left > pictureSum_right){ 
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
	int x = 0;
	while(x < 40){
		int white = checkPicture();
		if(white){
			printf("turn left");
		}
		else{
			printf("turn right");
		}
		usleep(25000);
		x++;
	}
	printf("finish");
	return 0;
}
