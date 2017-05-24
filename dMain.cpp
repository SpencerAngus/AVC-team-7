#include <stdio.h>
#include "E101.h"

int frameRate = 80;
int initSpeed = 50;
int mode = 2;

float err_1 = 0; //error | how offcentered the robot is (-ve for left +ve for right and 0 is centered)
int nwp = 0; //number of white pixels detected
int nwp1 = 0; //number of white pixels detected

const int MLEFT = 2;
const int MRIGHT = 1;

const int SFRONT = 0;
const int SLEFT = 1;
const int SRIGHT = 2;

int doGate() {
	char server_ip[] = "130.195.6.196";
	int server_port = 1024;
	char server_request[] = "Pozhaluysta - Please";

	connect_to_server(server_ip, server_port);
	send_to_server(server_request);
	char password[24];
	receive_from_server(password);
	send_to_server(password);
	return 0;
}

int back_track(){
	printf("reversing \n");
	set_motor(MLEFT, -initSpeed);
	set_motor(MRIGHT, -initSpeed);
	return 0;
}

void scanLine(){
	char pix = 0; //holds pixel's color
	char pix1 = 0; //holds pixel's color
	int test_points = 64; //can be adjusted
	char white [64]; //holds pixel's rounded color (0=black and 1=white) and location
	err_1 = 0; //error | how offcentered the robot is (-ve for left +ve for right and 0 is centered)
	nwp = 0; //number of white pixels detected
	nwp1 = 0; //number of white pixels detected
	int threshold_var = 100; //can be adjusted
	int derivpixel=70;//pixel difference verticaly for the deriviate calculation.
	
	take_picture(); //take picture and store in memory
	//first line scan
	for(int i=0;i<test_points;i++){ 
		pix = get_pixel(200, i*(320/test_points), 3); //save pixel color
		if(pix>threshold_var){
			white[i] = 1; //round color
			nwp++;
		}
		else{
			white[i] = 0; //round colo
		}
		err_1 = err_1 + (i - test_points/2)*white[i]; //total err signalf
	}
	// second line scan
	for(int i=0;i<test_points;i++){ 
		pix1 = get_pixel(120-derivpixel, i*(320/test_points), 3); //save pixel color
		//printf("%i ", i);
		if(pix1>threshold_var){
			nwp1++;
		}
	}	
}

bool checkRed(){
	int rgb[3] = {0,0,0};
	for(int i = 0; i <3; i++){
		char r = get_pixel(120, 150+10*i, 0);
		char b = get_pixel(120, 150+10*i, 1);
		char g = get_pixel(120, 150+10*i, 2);
		rgb[0] += r;
		rgb[1] += g;
		rgb[2] += b;
	}
	rgb[0] = rgb[0]/3;
	rgb[1] = rgb[1]/3;
	rgb[2] = rgb[2]/3;
	//printf("RGB: %d, %d, %d \n", rgb[0],rgb[1],rgb[2]);
	if(rgb[0] > 200 && rgb[1] < 100 && rgb[2] < 100){
		return 1;
	} else {
		return 0;
	}
}

int doLine(){
	int pSignal = 0; //proportinal signal, scaled by kP (P for Proportional in PID)
	float kp = 0.07; //for tuning pSignal
	int v_left;
	int v_right;
	
	scanLine();
	
	pSignal = (int)(err_1*kp);//error signal is tuned to suit velocity

	v_left = initSpeed - pSignal;
	v_right	= initSpeed + pSignal;
	set_motor(MRIGHT,v_right);
    	set_motor(MLEFT,v_left);
	
	if(nwp > 55){//intersection found
		/*set_motor(MRIGHT,40);
    		set_motor(MLEFT,40);
		sleep1(0,250000);*/
		mode = 1;
	}
	if(nwp <= 2){ // no road ahead, so backtrack
		back_track();
		sleep1(0,050000);
	}
	
	return 0;
}

int doQ3(){
	int pSignal = 0; //proportinal signal, scaled by kP (P for Proportional in PID)
	float kp = 0.08; //for tuning pSignal
	int v_left;
	int v_right;
	
	initSpeed = 50;
	
	scanLine();
	
	pSignal = (int)(err_1*kp);//error signal is tuned to suit velocity

	
	if(nwp > 55){//intersection found
		printf("intersection found \n");
		printf("nwp1: %i \n", nwp1);
		
		if(nwp1 <= 2){// T-Junction, so turn left
			printf("juction detected \n");
			set_motor(MRIGHT,0);
			set_motor(MLEFT,0);
			sleep1(0,100000);
			initSpeed = 35;
			set_motor(MRIGHT,-60);
			set_motor(MLEFT,60);
			sleep1(0,250000);
		} else {
			v_left = initSpeed - pSignal;
			v_right	= initSpeed + pSignal;
			set_motor(MRIGHT,v_right);
			set_motor(MLEFT,v_left); 
		}
		
	} else if(nwp <= 2) { // no road ahead, so backtrack
		back_track();
		sleep1(0,100000);
	}  else { 
		
		v_left = initSpeed + pSignal;
		v_right	= initSpeed - pSignal;
		set_motor(MRIGHT,v_right);
    		set_motor(MLEFT,v_left); 
	}
	
	if(checkRed()){
		mode = 2;
	}
	//frameRate = 5;
	/*printf("nwp: %i \n", nwp);
	printf("nwp1: %i \n", nwp1);
	printf("err_1: %f \n", err_1);*/
	
	return 0;
}

void doMaze(){
	initSpeed = 40;
	int errInt = 1;
	double err;
	double kp = 0.05;
	int pSignal = 0;
	
	int front = read_analog(SFRONT);
	int right = read_analog(SRIGHT);
	int left = read_analog(SLEFT);
	
	err = (double)(left - right);	
	pSignal = (int)(err*kp);
	
	
	set_motor(MRIGHT, initSpeed + pSignal);
	set_motor(MLEFT, initSpeed - pSignal);
}

int main (){
	init(); //initialiase hardware
	doGate();
	set_motor(MRIGHT,initSpeed);
	set_motor(MLEFT,initSpeed);
	while(mode == 0){ //infinite loop
		doLine(); //executes line following method
		sleep1(0,1000000/frameRate); //|testing| adjust this to adjust framerate
	}
	while(mode == 1){ //infinite loop
		doQ3(); //executes line following method
		sleep1(0,1000000/frameRate); //|testing| adjust this to adjust framerate
	}
	printf("maze \n");
	while(mode == 2){ //infinite loop
		doMaze(); //executes line following method
		sleep1(0,1000000/frameRate); //|testing| adjust this to adjust framerate
	}
	return 0;
}
