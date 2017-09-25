/*********************************************************************************************
* File: callbacks.h
* Author: Lucas Carpenter
* Class: CSC372 (Analysis of Algorithms)
* Date: 12/05/2016
* Bugs: none that I could find, if you find one, let me know.
*
* Notes:
*  = This file handles function declarations for GLUT window callbacks
**********************************************************************************************/
#include "globals.h"

#ifndef __CALBACKS_H_ 
#define __CALBACKS_H_

void displayCallback(void); // declaration of function for when glutPostRedisplay() is called
void mouseCallback(int button, int state, int x, int y); // declaration of function for mouse actions
void keyboardCallback(unsigned char key, int x, int y);	 // declaration of function for keyboard actions
void reshapeCallback(int w, int h); // declaration of function for reshaping the screen
void idleCallback(void); // declaration of function for the idle loop, (happens if nothing else happens)

#endif