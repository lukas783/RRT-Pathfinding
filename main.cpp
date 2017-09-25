/*********************************************************************************************
 * File: main.cpp
 * Author: Lucas Carpenter
 * Class: CSC372 (Analysis of Algorithms)
 * Date: 12/05/2016
 * Bugs: none that I could find, if you find one, let me know.
 *
 * Notes:
 *  = The unit test is handled by the #define statements below
 *  = The global declaration for the RRT class (RRT rrt;) should be moved to a better location
 *    but I couldn't find a place to throw it elsewhere that made it seem any better and not
 *    break the code..
 *  
 *  = This file contains the main entry point of the program and a function to handle setting
 *    up the program for a unit test
**********************************************************************************************/

#include "globals.h"

/***
 * If UNIT_TEST is set to false, the program will start up and 
 * obstacles can be placed manually, as well as the origin and goal
 * If UNIT_TEST is set to true, then the program will load up with a 
 * predefined map defined by TEST_TYPE
 *
 * TEST_TYPE 1 = no obstacles, start point at top left, end point at bottom right
 * TEST_TYPE 2 = large obstacle in center, start point at top left, end point at bottom right
 * TEST_TYPE 3 = obstacle in center, start point right of obstacle, end point left of obstacle
 * TEST_TYPE 4 = obstacle in center, start point at top, end point at bottom
***/
#define UNIT_TEST false		//whether the unit test is active
#define TEST_TYPE 4			//if unit test is active, which map to run [1 - 4]
RRT rrt;					// the global declaration for the RRT class 
using namespace std;


/***
 * setupUnitTest()
 * - Function handles setting up the predefined origin/goal and obstacles
 * - and sets the rrt's stage to 10, which is the unit_test stage
***/
void setupUnitTest() {
	if (UNIT_TEST) {
		switch (TEST_TYPE) {
		// Setup for map 4
		case 4:
			rrt.setOrigin((double)width / 2.0, height - 10);
			rrt.setGoal((double)width / 2.0, 10);
			rrt.beginObst((double)width*0.05, (double)height*0.6);
			rrt.finishObst((double)width*0.95, (double)height*0.4);
			break;
		// setup for map 3
		case 3:
			rrt.setOrigin((double)width*0.22, (double)height/2.0);
			rrt.setGoal((double)width*0.77, (double)height / 2.0);
			rrt.beginObst((double)width*0.25, (double)height*0.75);
			rrt.finishObst((double)width*0.75, (double)height*0.25);
			break;
		// setup for map 2
		case 2:
			rrt.setOrigin(20, height - 20);
			rrt.setGoal(width - 20, 20);
			rrt.beginObst((double)width*0.25, (double)height*0.75);
			rrt.finishObst((double)width*0.75, (double)height*0.25);
			break;
		// setup for map 1 and any other invalid TEST_TYPE
		default:
			rrt.setOrigin(20, height - 20);
			rrt.setGoal(width - 20, 20);
			break;
		}
		rrt.setStage(10);	// sets the rrt's stage to 10, the UNIT_TEST stage
	}

}

/***
 * int main(int, char*)
 * - The entry point for the program; this function just finds out if
 * - the program is doing a unit test or a normal run and sets up the
 * - window and handlers from the GLUTWindow class
 *
 * - To change the unit test, modify the two #defines at the beginning of the file
***/
int main(int argc, char*argv[]) {
	setupUnitTest();	// setup for possible unit test
	srand(time(NULL));	// init rand()
	
	//Custom GLUTWindow class, opens a window using GLUT
	GLUTWindow window;
	window.setSize(width, height);	// sets window size (width and height are in globals.h)
	window.setTitle("RRT path-finding simulation");	// sets the title of the window
	window.setupWindow(argc, argv);	// required GLUT function
	window.setDisplayFunction(displayCallback);		// declares the display callback
	window.setMouseFunction(mouseCallback);			// declares the mouse callback
	window.setKeyboardFunction(keyboardCallback);	// declares the keyboard callback
	window.setReshapeFunction(reshapeCallback);		// declares the reshape function callback
	window.setIdleFunction(idleCallback);			// declares the idle callback
	window.init();									// begins our main loop
	// EVERYTHING ELSE IS HANDLED BY CALLBACKS (callbacks.cpp)
	return 0;
}