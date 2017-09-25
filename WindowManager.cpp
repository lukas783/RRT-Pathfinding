/*********************************************************************************************
* File: WindowManager.cpp
* Author: Lucas Carpenter
* Class: CSC372 (Analysis of Algorithms)
* Date: 12/05/2016
* Bugs: none that I could find, if you find one, let me know.
*
* Notes:
*  = This file handles the functions for creating a window and setting it up
**********************************************************************************************/
#include "globals.h"

// Constructor, nothing really needed..
GLUTWindow::GLUTWindow() {

}

// Destructor, nothing really needed..
GLUTWindow::~GLUTWindow() {

}

// setTitle(string) - Function sets the title of the window
void GLUTWindow::setTitle(string s) {
	title = s;
}

//setSize(int, int) - Function sets the size of the window
void GLUTWindow::setSize(int w, int h) {
	width = w;
	height = h;
}

//setupWindow(int, char*[]) - A required GLUT function, also sets up window and opens it
void GLUTWindow::setupWindow(int argc, char*argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutCreateWindow(title.c_str());
	glClearColor(255.0, 255.0, 255.0, 0.0);
}

//init() - Function to start up the GLUT main loop
void GLUTWindow::init() {
	glutMainLoop();
}

//setMouseFunction(void(*)) - function to setup the mouse callback
void GLUTWindow::setMouseFunction(void(*func)(int button, int state, int x, int y))
{
	glutMouseFunc(func);
}

//setKeyboardFunction(void(*)) - function to setup the keyboard callback
void GLUTWindow::setKeyboardFunction(void(*func)(unsigned char key, int x, int y))
{
	glutKeyboardFunc(func);
}

//setDisplayFunction(void(*)) - function to setup the display callback
void GLUTWindow::setDisplayFunction(void(*func)(void))
{
	glutDisplayFunc(func);
}

//setIdleFunction(void(*)) - function to setup the idler callback
void GLUTWindow::setIdleFunction(void(*func)(void))
{
	glutIdleFunc(func);
}

//setReshapeFunction(void(*)) - function to setup the reshape callback
void GLUTWindow::setReshapeFunction(void(*func)(int w, int h))
{
	glutReshapeFunc(func);
}