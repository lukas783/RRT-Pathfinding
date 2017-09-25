/*********************************************************************************************
* File: drawing.cpp
* Author: John Weiss, modifications made by Lucas Carpenter
* Class: CSC372 (Analysis of Algorithms)
* Date: 12/05/2016
* Bugs: none that I could find, if you find one, let me know.
*
* Notes:
*  = This file handles functions for drawing objects in a GLUT window
**********************************************************************************************/
#include "globals.h"

/***
 * This code was taken from Dr. Weiss's CSC300 Programs
 * drawText(char*, int, int)
 * - draws the text from char*, at pos (int, int)
***/
void drawText(char *str, int x, int y) {
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(x, y);
	while (*str)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *str++);
}

/***
 * This code was taken from Dr. Weiss's CSC300 Programs
 * drawFilledEllipse(float, float, int, int, float, float, float)
 * - draws a filled ellipse at pos (int, int) with a radius of (float, float)
 * - and a color of (float, float, float)
***/
void drawFilledEllipse(float xR, float yR, int x, int y, float r, float g, float b) {
	float radius = xR < yR ? xR : yR;
	glColor3f(r, g, b);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0);
	glScalef(xR / radius, yR / radius, 1.0);
	GLUquadricObj *disk = gluNewQuadric();
	gluDisk(disk, 0, radius, int(radius), 1);
	gluDeleteQuadric(disk);
	glLoadIdentity();
	glFlush();
}

/***
 * This code was taken from Dr. Weiss's CSC300 Programs
 * drawLine(float, float, float, float)
 * - draws a line from (float, float) to (float, float)
***/
void drawLine(float x1, float y1, float x2, float y2) {
	glLineWidth(1);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
	glFlush();
}

/***
* This code was taken from Dr. Weiss's CSC300 Programs
* drawLine(float, float, float, float)
* - draws a line from (float, float) to (float, float)
***/
void drawPath(float x1, float y1, float x2, float y2) {
	glLineWidth(3);
	glColor3f(0.0, 150.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();
}

/***
 * This code was taken from Dr. Weiss's CSC300 Programs
 * drawRect(float, float, float, float)
 * - draws a rectangle with diagonal corners at (float, float)
 * - and (float, float)
***/
void drawRect(float x1, float y1, float x2, float y2) {
	glColor3f(0.9, 0.8, 0.5);
	glBegin(GL_QUADS);
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
	glEnd();
	glFlush();
}