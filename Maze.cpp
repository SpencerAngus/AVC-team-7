//When inside the maze there will be 6 situations;
//  1. dead end
//  2. left turn
//  3. right turn
//  4. T intersection
//  5. 4 way ("+") intersection
//  6. rotated T intersection

//  1. At a dead end, the robot should turn 180 degrees on the spot and then continue in a straight line from where it come from.

//  2. At a left turn (where the robot detects a wall at the front and right, but no wall on the left) the robot should turn 90 degrees anticlockwise and then contine in a straight line.

//  3. At a right turn (where the robot detects a wall at the front and left, but no wall on the right) the robot should turn 90 degrees clockwise and then contine in a straight line.

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