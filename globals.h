/*********************************************************************************************
* File: globals.h
* Author: Lucas Carpenter
* Class: CSC372 (Analysis of Algorithms)
* Date: 12/05/2016
* Bugs: none that I could find, if you find one, let me know.
*
* Notes:
*  = This file handles all #includes and global variables used throughout the program
**********************************************************************************************/

#ifndef __GLOBALS_H_
#define __GLOBALS_H_
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>
#include <random>
#include <string>
#include <time.h>
#include <vector>
#include "callbacks.h"
#include "collision.h"
#include "glut.h"
#include "WindowManager.h"
#include "drawing.h"
#include "RRT.h"
using namespace std;

extern RRT rrt;						// RRT class declaration, (declared elsewhere)
static int width = 1024;			// declaration of window width
static int height = 768;			// declaration of window height
static int prevStage = -1;			// declaration of RRT stage holder for obstacles
static double EPSILON = 0.000001;	// declaration of a variable used by collision.cpp
static int points = 0;				// declaration of variable for number of iterations
static int path_points = 0;			// declaration of varaible for points in final solution

#endif 