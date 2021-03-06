/*
*			    .ue~~%u.     cuuu....uK      .--~*teu.        .ue~~%u.      .xH888888Hx.
*			  .d88   z88i    888888888      dF     988Nx    .d88   z88i   .H8888888888888:
*			 x888E  *8888    8*888**"      d888b   `8888>  x888E  *8888   888*"""?""*88888X
*			:8888E   ^""     >  .....      ?8888>  98888F :8888E   ^""   'f     d8x.   ^%88k
*			98888E.=tWc.     Lz"  ^888Nu    "**"  x88888~ 98888E.=tWc.   '>    <88888X   '?8
*			98888N  '888N    F     '8888k        d8888*`  98888N  '888N   `:..:`888888>    8>
*			98888E   8888E   ..     88888>     z8**"`   : 98888E   8888E         `"*88     X
*			'8888E   8888E  @888L   88888    :?.....  ..F '8888E   8888E    .xHHhx.."      !
*			 ?888E   8888" '8888F   8888F   <""888888888~  ?888E   8888"   X88888888hx. ..!
*			  "88&   888"   %8F"   d888"    8:  "888888*    "88&   888"   !   "*888888888"
*			    ""==*""      ^"===*%"`      ""    "**"`       ""==*""            ^"***"`
*/

/*
This is the driver control section of the program. You should put all of your driver functions here.
*/

#include "declareStuff.hpp" //adds your motors, sensors, controllers, variables, and functions to the file

const int NUM_HEIGHTS = 5; //how many different preset positions you have for the lift
const int height0 = 0; //the first preset position. Relative to the starting position.
const int height1 = 180; //the second preset position. Relative to the starting position.
const int height2 = 350; //the third preset position. Relative to the starting position.
const int height3 = 600; //the fourth preset position. Relative to the starting position.
const int height4 = 700; //the fifth preset position. Relative to the starting position.

const int heights[NUM_HEIGHTS] = {height0, height1, height2, height3, height4}; //an array of all the heights you have

int goalHeight = 0; //the current height the lift is at


void driveControl(void* param){ //a task that runs at the same time as the other tasks
  while (true) { //infinite loop
    pros::delay(5); //short delay of 5 ms so that we don't use too much resources
    drive.arcade(MasterC.getAnalog(ControllerAnalog::leftY), MasterC.getAnalog(ControllerAnalog::leftX)); //prebuilt drive controller
  }
}


void liftControl(void* param){ //a task that runs at the same time as the other tasks
  while (true) { //infinite loop
    pros::delay(5); //short delay of 5 ms so that we don't use too much resources
    if (liftUpButton.changedToPressed() && goalHeight < NUM_HEIGHTS - 1) {//if you press the lift up button and the lift isn't at its max height
      goalHeight++; //set the height of the lift to the next higher height
      lift.setTarget(heights[goalHeight]); //move the lift to the set height
    } else if (liftDownButton.changedToPressed() && goalHeight > 0) {//if you press the lift down button and the lift isn't at its min height
      goalHeight--; //set the height of the lift to the next lower height
      lift.setTarget(heights[goalHeight]); //move the lift to the set height
    }
  }
}


void opcontrol() { //This runs immediatly after the initialization
  pros::Task driveControlTask (driveControl, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, ""); //starts the drive control task
  pros::Task liftControlTask (liftControl, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, ""); //starts the lift control task
}
