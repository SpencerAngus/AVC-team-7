//When inside the maze there will be 6 situations;
//  1. dead end
//  2. left turn
//  3. right turn
//  4. T intersection
//  5. 4 way ("+") intersection
//  6. rotated T intersection

const int LEFT_SENSOR = 0;
const int RIGHT_SENSOR = 1;
const int FORWARD_SENSOR = 2;
	
const int LEFT_MOTOR = 1;
const int RIGHT_MOTOR = 2;

//const int THRESHOLD = 80; // Threshold value to allow turning - Change with testing.
const int DEF_SPD = 50; // Default speed for motors

double mazeFactor = 0; // To be changed with testing.
bool mazeDone = false;

int main(){
	init();
	
	//Variables for the sensor readings.
	int left_reading = 0;
	int right_reading = 0;
  int forward_reading = 0;
  
  int sensorError;

  
   printf("Left Sensor: %d    Middle Sensor: %d    Right Sensor: %d\n",adc_reading, adc_reading2, adc_reading3);
  	//Reading sensors - will need to be set to analog sensor pins.
		left_reading = read_analog(LEFT_SENSOR); 
		right_reading = read_analog(RIGHT_SENSOR);
  forward_reading = read_analog(FORWARD_SENSOR);
 int sensor_error = (right_reading - left_reading) * mazeFactor;
      

	
//  1. At a dead end, the robot should turn 180 degrees on the spot and then continue in a straight line from where it come from.

//  2. At a left turn (where the robot detects a wall at the front and right, but no wall on the left) the robot should turn 90 degrees anticlockwise and then contine in a straight line.
	
		// If left reading is greater (further away), turn left.
		if(left_reading > right_reading && left_reading > forward_reading){
			set_motor(LEFT_MOTOR, DEF_SPD+1*sensor_difference);
			set_motor(RIGHT_MOTOR, DEF_SPD-sensor_difference);
//  3. At a right turn (where the robot detects a wall at the front and left, but no wall on the right) the robot should turn 90 degrees clockwise and then contine in a straight line.
	// If right reading is greater, turn right.
		else if(right_reading > left_reading && right_reading > forward_reading) {			
			set_motor(LEFT_MOTOR, DEF_SPD-1*sensor_difference);
			set_motor(RIGHT_MOTOR, DEF_SPD+sensor_difference);
		}
      else{
		set_motor(LEFT_MOTOR, DEF_SPD);
			set_motor(RIGHT_MOTOR, DEF_SPD);
		}
//  4. At a T intersection (where the robot detects no walls at the right and left, with a wall at the front) it should turn left (90 degrees anticlockwise) and continue in a straight line.

//  5. At a 4 way ("+") intersection, the robot should turn left (90 degrees anticlockwise) and continue. This will ensure that if it comes back along this path, that it will always try the next possible path that it has not yet explored.

//  6. At a rotated T intersection (where there is a opening to the front and either the left or right side) the robot should continue going straight rather than turn.

//while (in quadrant 4- detect colour red) {
//  frontReading = get reading from front facing IR sensor
//  leftReading = get reading from left hand IR sensor
//  rightReading = get reading from right hand IR sensor
//  if (frontReading > 500) {
//    //There is a wall in front
//    if (leftReading > 500 && rightReading < 500) {
//      //There is a wall in front and no wall to the left
//      //Turn left
//    }
//    else if (leftReading < 500 && rightReading > 500) {
//      //There is a wall in front and no wall to the right
//      //Turn right
//    }
//    else if (leftReading > 500 && rightReading > 500) {
//      //There is a wall in front and walls on both sides
//      //Turn 180 degrees
//    }
//    else if (leftReading < 500 && rightReading < 500) {
//      //There is a wall in front and no walls on either side
//      //Go straight
//    }
//  }
//  else {
//  //There is no wall in front
//    if (leftReading > rightReading) {
//      //Turn right
//    }
//    else if (rightReading > leftReading) {
//      //Turn left
//    }
//  }
//}
