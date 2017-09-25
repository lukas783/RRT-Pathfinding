/*********************************************************************************************
 * File: collision.cpp
 * Author: Martin Thoma, translated to C++ with modifications by Lucas Carpenter
 * Class: CSC372 (Analysis of Algorithms)
 * Date: 12/05/2016
 * Bugs: none that I could find, if you find one, let me know.
 *
 * Notes:
 *  = This file handles functions for finding whether two lines intersect with each other
 * 
 * Credit for this code goes to Martin Thoma
 * - http://www.martin-thoma.com/
 * - This code was originally written in Java to test whether
 * - two lines intersect or not using a bounding box intersect
 * - test and a line segment touches or crosses test.
 * - The code has been converted from Java to C++ by Lucas Carpenter
 *
**********************************************************************************************/
#include "collision.h"

// Point - a struct to handle an x and y coordinate together
struct Point {
	int x, y;	// declaration of x and y coords
	Point(int i, int j) { // constructor for node
		x = i; // set the node's x coord to i
		y = j; // set the node's y coord to j
	}
	Point() { // constructor for node with no input
		x = 0; // set the node's x coord to 0
		y = 0; // set the node's y coord to 0
	}
};

// LineSegment - a struct to handle a line segment between two points
struct LineSegment {
	Point first; // declaration of a point
	Point second;// declaration of another point
	LineSegment(int x1, int y1, int x2, int y2) { // constructor
		first.x = x1; // the node's first x coord is x1
		first.y = y1; // the node's first y coord is y1
		second.x = x2;// the node's second x coord is x2
		second.y = y2;// the node's second y coord is y2
	}
};


/*** crossProduct(Point, Point) | function to take the cross product of two points ***/
static double crossProduct(Point a, Point b) {
	return a.x * b.y - b.x * a.y; // returns the cross product of Point a and Point b
}

/*** isPointOnLine(LineSegment, Point) | function to see if point is on the line ***/
static bool isPointOnLine(LineSegment a, Point b) {
	LineSegment atmp = LineSegment(0, 0, (a.second.x - a.first.x), (a.second.y - a.first.y)); // declare temp LineSegment
	Point btmp((b.x - a.first.x), b.y - a.first.y);	// declare temp Point
	double r = crossProduct(atmp.second, btmp); // take the crossproduct of the input point and the temp segment's second point
	return abs(r) < EPSILON; // if the abs value of the cross product is under .00001(EPSILON) then it's on the line, otherwise it's not 
}

/*** isPointRightOfLine(LineSegment, Point) | checks if the point is to the right of the line segment ***/
static bool isPointRightOfLine(LineSegment a, Point b) {
	LineSegment atmp(0, 0, (a.second.x - a.first.x), (a.second.y - a.first.y)); // declare temp LineSegment
	Point btmp((b.x - a.first.x), (b.y - a.first.y));	// declare temp Point
	return crossProduct(atmp.second, btmp) < 0;	// return whether the cross product of line segment's second point and temp point is less than 0
}

/*** doBoundingBoxesIntersect(vector<Point*>, vector<Point*>) | checks if the two bounding boxes of each line intersect ***/
static bool doBoundingBoxesIntersect(vector<Point*> a, vector<Point*> b) {
	return a[0]->x <= b[1]->x && a[1]->x >= b[0]->x && a[0]->y <= b[1]->y && a[1]->y >= b[0]->y; // formula to return whether the bounding boxes intersect
}

/*** touchesOrCrosses(LineSegment, LineSegment) | function that calls other functions to see if two lines cross or touch ***/
static bool touchesOrCrosses(LineSegment a, LineSegment b) {
	return isPointOnLine(a, b.first) || isPointOnLine(a, b.second)
		|| (isPointRightOfLine(a, b.first) ^ isPointRightOfLine(a, b.second)); // returns whether the two lines intersect
}

/*** doLinesIntersect(int, int, int, int, int, int, int, int) | function to see if two lines intersect with each other ***/
bool doLinesIntersect(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
	LineSegment a(ax1, ay1, ax2, ay2);	// declare line segment a
	LineSegment b(bx1, by1, bx2, by2);	// declare line segment b
	vector<Point*> box1, box2;			// declare the two bounding boxes
	box1.resize(2);						// resize box1 to hold 2 points
	box2.resize(2);						// resize box2 to hold 2 points
	// Sets the points in the bounding box vectors
	box1[0] = new Point(min(a.first.x, a.second.x), min(a.first.y, a.second.y));
	box1[1] = new Point(max(a.first.x, a.second.x), max(a.first.y, a.second.y));
	box2[0] = new Point(min(b.first.x, b.second.x), min(b.first.y, b.second.y));
	box2[1] = new Point(max(b.first.x, b.second.x), max(b.first.y, b.second.y));


	return doBoundingBoxesIntersect(box1, box2) && touchesOrCrosses(a, b) && touchesOrCrosses(b, a); // returns whether the two lines intersect
}
