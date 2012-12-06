//Ian Forsyth
//CPSC 478
//Final Project

#ifndef CREATEMAZE_H
#define CREATEMAZE_H

#include <utility>
#include <vector>
#include "location.h"
#include "part.h"

using namespace std;

class createMaze
{
	private:
		vector<vector<part> > theMaze;			//The maze with parts of boolean value
		vector<vector<int> > setChecker;		//The number grid used to generate the maze
		location goal;							//Locaiton of the goal object
		location player;						//Location of the player object
		void resetMaze();						//Used to regenerate the maze after teapot is found
		location partStepper(location start, int dir);	//Handles where the player will move
	public:
		int score;								//Player's score out of 5
		createMaze(float height, float width);		//Maze object with height and width
		bool stepChecker(unsigned int dir, location start);	//Determines if allowed to move
															//Handles collision detection
		void movePlayer(int dir);							//Actual moving of the player object
		location findPlayer();								
		float height();
		float width();
		location findGoal();
		createMaze();
		string scoreString();
		bool makeMaze(location start);
};

#endif
