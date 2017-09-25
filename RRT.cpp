/*********************************************************************************************
* File: RRT.cpp
* Author: Lucas Carpenter
* Class: CSC372 (Analysis of Algorithms)
* Date: 12/05/2016
* Bugs: none that I could find, if you find one, let me know.
*
* Notes:
*  = This file handles functions for the RRT algorithm
**********************************************************************************************/
#include "globals.h"

/*** RRT() | constructor, nothing to initialize really... ***/
RRT::RRT() {
}

/*** ~RRT() | destructor, nothing to destroy or free... ***/
RRT::~RRT() {
}

/*** setOrigin(x, y) | sets the origin's x and y coords ***/
void RRT::setOrigin(int x, int y) {
	node* n = new node();	// declare new node
	n->x = x;				// set x coord for node
	n->y = y;				// set y coord for node
	origin = n;				// declare it the origin
	nodes.push_back(n);		// add it to the vector of nodes in graph
}

/*** setEnd(x, y) | sets the end's x and y coords ***/
void RRT::setGoal(int x, int y) {
	node* n = new node();	// declare new node
	n->x = x;				// set x coord for node
	n->y = y;				// set y coord for node
	goal = n;				// declare it the goal
}

/*** getStringPrompt() | returns a string to prompt the user for what to do next ***/
char* RRT::getStagePrompt() {
	// The return statements are self-explanatory as to what each stage means..
	if (stage == 0)
		return "Left-Click anywhere to place the starting position.";
	else if (stage == 1)
		return "Left-Click anywhere to place the goal.";
	else if (stage == 2)
		return "Press any key to finalize and begin the path searching.";
	else if (stage == 3)
		return "Press any key to pause the path searching.";
	else if (stage == 4)
		return "Press any key to continue the path searching.";
	else if (stage == 10)
		return "Press any key to begin path searching";
	else if (stage == -1)
		return "Goal found, path is shown below";
	// if stage isn't in here, return nothing
	return "";
}

/*** getObstPrompt() | returns a string to give the user instructions for creating obstacles ***/
char* RRT::getObstPrompt() {
	// The return statements are self-explanatory as to what each stage means..
	if (stage == 0 || stage == 1 || stage == 2)
		return "Right-Click anywhere to begin placing an obstacle";
	if (stage >= 5 && stage < 10)
		return "Right-Click anywhere to finish placing an obstacle";
	// if stage isnt in here, return nothing
	return "";
}

/*** search() | this is the BUILD_RRT function for the algorithm, function searches for a node to add to the graph ***/
void RRT::search() {
	points++;	// increment the iteration counter
	node* n = new node();	// declare a new node
		n->x = rand() % width;	// set the x coord of the new node to a rand configuration
		n->y = rand() % height;	// set the y coord of the new node to a rand configuration
		n->parent = find_nearest(n->x, n->y);	// set the parent of the new node using the find_nearest func
		if (isValid(n)) {	// if the newly created node and parent combo is valid...
			n->parent->children.push_back(n);	// set the parent nodes children as the current new node
			line* nl = new line();				// declare a new line
			nl->x1 = n->parent->x;				// set the first x as the parent's x
			nl->x2 = n->x;						// set the second x as the node's x
			nl->y1 = n->parent->y;				// set the first y as the parent's y
			nl->y2 = n->y;						// set the second y as the node's y
			lines.push_back(nl);				// add the newly made line to the vector of lines
			nodes.push_back(n);					// add the new node to the vector of nodes
			if (abs(n->x - goal->x) < 60 && abs(n->y - goal->y) < 60) { // check if new node is close enough to the goal
				setStage(-1);			 // if it is, set the stage to -1 (done stage)
				goal->parent = n;		 // set the goals parent to the current new node
				line* n2 = new line();	 // declare a new line
				n2->x1 = goal->parent->x;// set the new line's first x to goal's parent's x
				n2->x2 = goal->x;		 // set the new line's second x to goal's x
				n2->y1 = goal->parent->y;// set the new line's first y to goal's parent's y
				n2->y2 = goal->y;		 // set the new line's second y to goal's y
				lines.push_back(n2);	 // add the new line to the vector of lines
				nodes.push_back(goal);		 // add the goal to the vector of nodes (completes the vector)
				trace_route();			 // call the func to trace a route back to the origin
			}
		}
		displayCallback();	// i call displayCallback() here so the effects are immediate instead of after the main loop resets
}

/*** find_nearest(int, int) | a function that traverses through the list of current nodes to find the closest neighbor ***/
node* RRT::find_nearest(int x, int y) {
	int distance = 0, nearest = INT_MAX; // declaration of var for distance and current nearest
	node* n;							 // declaration of node pointer
	for (unsigned int i = 0; i < nodes.size(); i++) {
		// calc distance and compare to nearest node so far, if current node is closer, nearest = n
		distance = (x - nodes[i]->x)*(x - nodes[i]->x) + (y - nodes[i]->y)*(y - nodes[i]->y); // no need to get sqrt of func, pointless cost
		if (distance < nearest) {	// check if new distance is lower than current nearest distance
			n = nodes[i];	// set n to nodes[i]
			nearest = distance; // set the new nearest as the calculated distance above
		}
	}
	return n; // return our node n as the nearest node
}

/*** isValid(node*) | finds out if the node* is able to connect to its parent in a straight line without hitting an obstacle ***/
bool RRT::isValid(node* n) {
	int ax1 = n->x, ax2 = n->parent->x, ay1 = n->y, ay2 = n->parent->y; // pre calc these so the func calls dont get so long
	for (unsigned int i = 0; i < obst.size(); i++) {
		if (doLinesIntersect(ax1, ay1, ax2, ay2, obst[i]->x1, obst[i]->y1, obst[i]->x2, obst[i]->y1) ||
			doLinesIntersect(ax1, ay1, ax2, ay2, obst[i]->x1, obst[i]->y2, obst[i]->x2, obst[i]->y2) ||
			doLinesIntersect(ax1, ay1, ax2, ay2, obst[i]->x1, obst[i]->y1, obst[i]->x1, obst[i]->y2) ||
			doLinesIntersect(ax1, ay1, ax2, ay2, obst[i]->x2, obst[i]->y1, obst[i]->x2, obst[i]->y2)) { // check if lines intersect (collision.cpp)
			return false;// if they do, return false
		}
	}
	return true; // if we've made it through all obstacles with no collisions, we can return true and connection can be added
}

/*** beginObst(int, int) | sets the first diagonal of an obstacle ***/
void RRT::beginObst(int x, int y) {
	obstacle* o = new obstacle(); // declare new obstacle
	o->x1 = x;					  // set the obstacles first x coord
	o->y1 = y;					  // set the obstacles first y coord
	obst.push_back(o);			  // add to end of vector of obstacles
}

/*** finishObst(int, int) | sets the second diagonal of an obstacle ***/
void RRT::finishObst(int x, int y) {
	obstacle* o = obst.back();	// declare an obstacle equal to the last obstacle in the vector of obstacles (tongue twister..)
	o->x2 = x;					// set the obstacles second x coord
	o->y2 = y;					// set the obstacles second y coord
	o->finished = true;			// set the obstacle to finished so it will be added into the display
}

/*** trace_route() | function starts at goal and traverses through each parent till the origin, highlighting the path in green ***/
void RRT::trace_route() {
	node* n = goal;				// declare a node pointer to goal
	while (n != origin) {		// loop until we hit the origin node
		path_points++;			// with each iteration, increment the points in solution counter
		drawPath(n->x, n->y, n->parent->x, n->parent->y); // draw the path from each child to its parent
		n = n->parent;			// set the current node to its own parent
	}
	cout << endl << endl;		// a few endlines for formatting
	cout << "Number of points attempted: " << points << endl;	  // output for # of iterations
	cout << "Number of points in path: " << path_points << endl;  // output for # of points in solution
	cout << "Number of points in space: " << nodes.size() << endl;// output for # of points in graph
	path_points = 0;											  // reset the path_points since its a global and not a local.. 
}