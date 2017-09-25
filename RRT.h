/*********************************************************************************************
* File: RRT.h
* Author: Lucas Carpenter
* Class: CSC372 (Analysis of Algorithms)
* Date: 12/05/2016
* Bugs: none that I could find, if you find one, let me know.
*
* Notes:
*   = vector<node*> nodes: a list of all points in the search space
*   = node* origin: the starting x/y coordinate of our search
*   = node* goal: the x/y coordinate we want to pathfind to
*   = stage:	-1 = goal found, program finished.
*	  			0 = starting out, prompting for origin or obstacle placement
*				1 = prompting for goal or obstacle placement
*				2 = last chance for obstacle placement, prompting for starting the search
*				3 = search is running
*				4 = search is paused
*				5 = in process of placing obstacle
*				10 = UNIT_TEST is set to true, no modifying allowed.
*
*  = This file declares all the structs and classes for the RRT algorithm
**********************************************************************************************/
#include "globals.h"

#ifndef __RRT_H_
#define __RTT_H_

// node - a struct that's vertex containing the x, y coordinate and links to neighboring vertices
struct node {
	int x = 0, y = 0;	// the points of the vertex
	node* parent;		// the vertex's parent node
	vector<node*> children;	// the vertex's children nodes
};

// line - a struct containing the two points to connect with a line
struct line {
	int x1, x2, y1, y2; // the coordinates for the two points
};

// obstacle - a struct containing the two diagonals of a square for an obstacle
struct obstacle {
	int x1, y1, x2, y2;	// the coords for the two diagonals
	bool finished = false;	// a bool to see if the obstacle has been fully created yet
};


class RRT {
public:
	RRT();
	~RRT();
	void setOrigin(int x, int y);				// declaration of function to set the beginning
	void setGoal(int x, int y);					// declaration of function to set the ending
	int getStage() {		return stage;	};	// function to get the current stage
	void setStage(int i) {	stage = i;	};		// function to set the stage
	node* getOrigin() { return origin; };		// function to return the origin node
	node* getGoal() { return goal;  };			// function to return the goal node
	char* getStagePrompt();						// declaration of function to get text for curr stage
	char* getObstPrompt();						// declaration of function to get text for obst instructs
	void search();								// declaration of function to run the BUILD_RRT algorithm
	void beginObst(int x, int y);				// declaration of function to place the first diagonal of an obstacle
	void finishObst(int x, int y);				// declaration of function to place the second diagonal of an obstacle
	void trace_route();							// declaration of function that traces a route from goal to origin
	vector<line*> lines;						// vector of connected points
	vector<obstacle*> obst;						// vector of obstacles

private:
	// see notes above for info on private declarations
	vector<node*> nodes;
	node* find_nearest(int x, int y);
	bool isValid(node* n);
	node* origin = nullptr;
	node* goal = nullptr;
	int stage = 0;
};
#endif