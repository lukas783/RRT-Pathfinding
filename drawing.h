/*********************************************************************************************
* File: drawing.h
* Author: Lucas Carpenter
* Class: CSC372 (Analysis of Algorithms)
* Date: 12/05/2016
* Bugs: none that I could find, if you find one, let me know.
*
* Notes:
*  = This file handles declarations for functions that draw objects for a GLUT window
**********************************************************************************************/
#ifndef __DRAWING_H_
#define __DRAWING_H_
void drawText(char *str, int x, int y);	// function declaration for text drawing
void drawLine(float x1, float y1, float x2, float y2);	// function declaration for black lines (width = 1)
void drawPath(float x1, float y1, float x2, float y2);	// function declaration for green lines (width = 3)
void drawFilledEllipse(float xR, float yR, int x, int y, float r, float g, float b); // function declaration for filled ellipses
void drawRect(float x1, float y1, float x2, float y2);  // function declaration for rectangle
#endif