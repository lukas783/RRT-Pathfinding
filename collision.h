/*********************************************************************************************
* File: collision.h
* Author: Martin Thoma, translated to C++ with modifications by Lucas Carpenter
* Class: CSC372 (Analysis of Algorithms)
* Date: 12/05/2016
* Bugs: none that I could find, if you find one, let me know.
*
* Notes:
*  = This file handles a single declaration for the line intersect function
**********************************************************************************************/
#ifndef __COLLISION_H_
#define __COLLISION_H_
#include "globals.h"
bool doLinesIntersect(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);
#endif