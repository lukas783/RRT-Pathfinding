/*********************************************************************************************
* File: WindowManager.h
* Author: Lucas Carpenter
* Class: CSC372 (Analysis of Algorithms)
* Date: 12/05/2016
* Bugs: none that I could find, if you find one, let me know.
*
* Notes:
*  = This file handles declarations for the GLUT window manager
**********************************************************************************************/
#include "globals.h"

#ifndef __WINDOWMANAGER_H_
#define __WINDOWMANAGER_H_
using namespace std;

class GLUTWindow {

public:
	GLUTWindow();	// constructor
	~GLUTWindow();	// destructor
	void setTitle(string s);	// function for title of the window
	void setSize(int w, int h);	// fucntion for size of the window
	void setupWindow(int argc, char*argv[]);// required GLUT function
	void init();	// function to initialize the GLUT main loop
	void setMouseFunction(void(*func)(int button, int state, int x, int y)); // function for mouse callback
	void setKeyboardFunction(void(*func)(unsigned char key, int x, int y));	 // function for keyboard callback
	void setDisplayFunction(void(*func)(void));								 // function for display callback
	void setReshapeFunction(void(*func)(int w, int h));						 // function for reshape callback
	void setIdleFunction(void(*func)(void));								 // function for idler callback

private:
	int width = 1024, height = 768;	// default value for window size
	string title = "heres a title";	// default value for title of window
};

#endif
