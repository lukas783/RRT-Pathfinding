/*********************************************************************************************
* File: callbacks.cpp
* Author: John Weiss, modifications made by Lucas Carpenter
* Class: CSC372 (Analysis of Algorithms)
* Date: 12/05/2016
* Bugs: none that I could find, if you find one, let me know.
*
* Notes:
*  = This file handles functions for handling callbacks that go off when something happens in
*    the GLUT window
**********************************************************************************************/
#include "globals.h"

/*** idleCallback(void) | function to handle the loop when no other callback is occurring ***/
void idleCallback(void) {
	if (rrt.getStage() == 3) // if the rrt's stage is set to run
		rrt.search();		 // then it'll run and search till a path is found
}

/*** displayCallback(void) | function to handle drawing to the screen (called whenever glutPostRedisplay() is called ***/
void displayCallback(void) {
	glClear(GL_COLOR_BUFFER_BIT);	// clear the screen

	// Draws the origin and the goal if able to
	if (rrt.getStage() != 0 && rrt.getStage() != 5) 
		drawFilledEllipse(6.0, 6.0, rrt.getOrigin()->x, rrt.getOrigin()->y, 255.0, 0.0, 0.0);
	if ( (rrt.getStage() > 1 && rrt.getStage() < 5) || rrt.getStage() > 6 || rrt.getStage() == -1 ) 
		drawFilledEllipse(6.0, 6.0, rrt.getGoal()->x, rrt.getGoal()->y, 0.0, 0.0, 255.0);
	
	// if the simulation is finished, draw the traced route instead
	if (rrt.getStage() == -1) 
		rrt.trace_route();
	
	// Draws the lines between two points
	for (unsigned int i = 0; i < rrt.lines.size(); i++) 
		drawLine(rrt.lines[i]->x1, rrt.lines[i]->y1, rrt.lines[i]->x2, rrt.lines[i]->y2);

	// Draw the rectangles for the obstacles
	for (unsigned int i = 0; i < rrt.obst.size(); i++) {
		if(rrt.obst[i]->finished)
			drawRect(rrt.obst[i]->x1, rrt.obst[i]->y1, rrt.obst[i]->x2, rrt.obst[i]->y2);
	}

	// Instructional text 
	drawText(rrt.getStagePrompt(), 380, 740);
	drawText(rrt.getObstPrompt(), 380, 725);

	// Swap the buffer (display everything created above)
	glutSwapBuffers();
}

/*** mouseCallback(int, int, int, int) | function to handle mouse actions in the GLUT window ***/
void mouseCallback(int button, int state, int x, int y) {
	y = height - y;	// reverse the y with the current height
	
	if (button == 0 && state == 1) { // If left click && depressing button
		// If stage == 0, set origin
		if (rrt.getStage() == 0) { 
			rrt.setOrigin(x, y);
			rrt.setStage(1);
		}
		// If stage == 1, set goal
		else if (rrt.getStage() == 1) {
			rrt.setGoal(x, y);
			rrt.setStage(2);
		}
	}
	else if (button == 2 && state == 1) { // If right click && depressing button
		if (rrt.getStage() >= 5 && rrt.getStage() < 10) {
			rrt.finishObst(x, y);
			rrt.setStage(prevStage);
		} 

		else if (rrt.getStage() <= 2) {
			prevStage = rrt.getStage();
			rrt.setStage(rrt.getStage() + 5);
			rrt.beginObst(x, y);
		}
	}
	glutPostRedisplay();
}

/*** keyboardCallbakc(unsigned char, int, int) | function that handles keyboard actions in the GLUT window ***/
void keyboardCallback(unsigned char key, int x, int y) {
	// if the current stage is 2, 4, or 10 (ready for first time, ready to continue, or ready to start unit_test), set the stage to 3 (running)
	if (rrt.getStage() == 2 || rrt.getStage() == 4 || rrt.getStage() == 10)
		rrt.setStage(3); // run the RRT continuously
	// if current stage is 3 (currently running), set the stage to 4 (paused)
	else if (rrt.getStage() == 3)
		rrt.setStage(4); // pause RRT
	glutPostRedisplay(); // call the display function
}

/*** reshapeCallback(int, int) | function to handle when the screen reshapes ***/
void reshapeCallback(int w, int h) {
	// I didn't add a resize function, so the window will always be set to 1024, 768
	glMatrixMode(GL_PROJECTION);	// sets up a projection view
	glLoadIdentity();				
	gluOrtho2D(0.0, w, 0.0, h);		// sets the coords of the orthogonal plane
	glViewport(0, 0, w, h);			// sets the viewed coords
}


