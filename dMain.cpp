#include <stdio.h>
#include "E101.h"


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

int frameRate = 80;
int initSpeed = 50;

const int MLEFT = 2;
const int MRIGHT = 1; 

int back_track(){
	set_motor(MLEFT, -initSpeed);
	set_motor(MRIGHT, -initSpeed);
	return 0;
}

int doLine(){
	char pix = 0; //holds pixel's color
	int test_points = 64; //can be adjusted
	char white [64]; //holds pixel's rounded color (0=black and 1=white) and location
	float err_1 = 0; //error | how offcentered the robot is (-ve for left +ve for right and 0 is centered)
	int nwp = 0; //number of white pixels detected
	int nwp1 = 0; //number of white pixels detected
	int threshold_var = 100; //can be adjusted
	int derivpixel=30; //pixel difference verticaly for the deriviate calculation.
	
	int pSignal = 0; //proportinal signal, scaled by kP (P for Proportional in PID)
	float kp = 0.07; //for tuning pSignal
	
	int v_left;
	int v_right;
	take_picture(); //take picture and store in memory
	//first line scan
	for(int i=0;i<test_points;i++){ 
		pix = get_pixel(120, i*(320/test_points), 3); //save pixel color
		//printf("%i ", i);
		if(pix>threshold_var){
			white[i] = 1; //round color
			nwp++;
			//printf("1");
		}
		else{
			white[i] = 0; //round color
			//printf("0");
		}
		err_1 = err_1 + (i - test_points/2)*white[i]; //total err signalf
	}
	// second line scan
	for(int i=0;i<test_points;i++){ 
		pix = get_pixel(120+derivpixel, i*(320/test_points), 3); //save pixel color
		//printf("%i ", i);
		if(pix>threshold_var){
			nwp1++;
		}
	}
	printf("Err: %f\n",err_1);
	pSignal = (int)(err_1*kp);//error signal is tuned to suit velocity
	printf("pSignal: %i\n",pSignal);
	printf("nwp = %i\n",nwp);

	v_left = initSpeed - pSignal;
	v_right	= initSpeed + pSignal;
    set_motor(MRIGHT,v_right);
    set_motor(MLEFT,v_left);
	
	if(nwp > 55){//intersection found
		if(nwp1 <= 2){// T-Junction, so turn left
			set_motor(MRIGHT,initSpeed);
			set_motor(MLEFT,-initSpeed);
			sleep1(0,250000);//1/4 seconds
		}
		//otherwise go straight
	}
	else if(nwp <= 2){ // no road ahead, so backtrack
		back_track();
		sleep1(0,050000);
	}
	
	return 0;
}

int main (){
	init(); //initialiase hardware
	doGate();
	set_motor(MRIGHT,initSpeed);
	set_motor(MLEFT,initSpeed);
	while(true){ //infinite loop
		doLine(); //executes line following method
		sleep1(0,1000000/frameRate); //|testing| adjust this to adjust framerate
	}
	return 0;
}
