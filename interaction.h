//Ian Forsyth
//CPSC 478
//Final Project

#ifndef INTERACTIONE_H
#define INTERACTION_H

#include <string>
#include <GL/gl.h>
#include <GL/glut.h>

#include "createMaze.h"

class	interaction
{
	private:
		createMaze theMaze;  	//The main maze object
		float yRot;  			//Mouse controlled Y Rotation
		int prevX;				//Used in Camera Rotaion
		int yCounter;			//			"
		int yChecker;			//			"
		double zoom;  			//Controls mouse click zoom out
		int cameraDir;  		//Camera Direction
		int goalSpin;  			//Handles ring rotation
		int height; 			//Viewport height
		int width; 				//Viewport width
	
		//Draw the walls of the maze with boxes
		void drawWall(float xA, float yA, float zA, float xB, float yB, float zB);	
		void draw(); 
	
		void orientRight();		//Based on yRot, change controls
		void orientLeft();		//			"
	
		//Drawing the score and winner message
		void beginText();
		void drawBitmapString(float x, float y, float z, string score);
		void drawStrokeString(float x, float y, float z, string score);
		void endText();

	public:
		interaction(float mazeSize, int w, int h);
		interaction();
		void display();
		void reshapeViewport(int w, int h);	
	
		//Handle user input from mouse and keyboard
		void mouse(int x, int y);
		void mouse2(int button, int state, int x, int y);
		void arrowKeys(int key);
		
		void spinGoal();	//Spins the teapot
		int playerObj;		//Holds the value on which shape will be used	
};

#endif
