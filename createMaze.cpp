//Ian Forsyth
//CPSC 478
//Final Project

#include <iostream>
#include <string>

#include <GL/gl.h>
#include <GL/glut.h>

#include <cstdlib>
#include <ctime>
#include <math.h>
#include <sstream>
#include "createMaze.h"

createMaze::createMaze(float height, float width){
	goal = location(width-1, height-1);		//Start the goal in the far corner
	player = location(0.0,0.0);				//Start the player in the opposite corner
	srand(time(0));
	score = 0;								//Start the score at 0
	
	//Set the maze height
	theMaze.resize(height);			
	setChecker.resize(height);
	
	//Set the maze width, fill with walls in actual maze, fill
	//with sequential numbers for pseudo-maze
	for (int counter = 0; counter < height; counter++)
	{
		theMaze[counter].resize(width, part(false, false));
		setChecker[counter].resize(width, NULL);

		for (int counter2 = 0; counter2 < width; counter2++)
			setChecker[counter][counter2] = (counter*width)+counter2;
	}

	//Iterate randomly through every wall in the maze and 
	//clear a path through the walls using Kruskal's algorithm,
	//implemented in the makeMaze function
	for (int counter = 0; counter < theMaze.size()*theMaze[0].size()*10; counter++)
		makeMaze(location(rand()%(int)theMaze[0].size(), rand()%(int)theMaze.size()));
}

//Returns a true or false value about whether
//the player can move. Based on the 'start' location
//and the bool values in upClear and rightClear of the 
//location itself and neighbors.
bool createMaze::stepChecker(unsigned int dir, location start){
	//Check up direction
	if (dir == 0)
		return theMaze[start.y][start.x].upClear;

	//Check right direction
	else if (dir == 1)
		return theMaze[start.y][start.x].rightClear;

	//Check down direction
	else if (dir == 2 & start.y < theMaze.size()-1)
		return theMaze[start.y+1][start.x].upClear;

	//Check left direction
	else if (dir == 3 & start.x > 0)
		return theMaze[start.y][start.x-1].rightClear;
	return false;
}

//After checking if the player can move, handle
//actually moving in the corresponding direction
location createMaze::partStepper(location start, int dir){
	//Move up
	if (dir == 0)
		return location(start.x, start.y-1);

	//Move right
	else if (dir == 1)
		return location(start.x+1, start.y);

	//Move down
	else if (dir == 2)
		return location(start.x, start.y+1);

	//Move left
	else if (dir == 3)
		return location(start.x-1, start.y);
	else
		return start;
}

bool createMaze::makeMaze(location start){
	int dir = rand()%2;								//Random up or right
	int setID = setChecker[start.y][start.x];	
	int newSetID;
	
	//Check to make sure the border of the maze stays solid
	if ((dir == 0 && start.y == 0) || (dir == 1 && start.x == theMaze[0].size()-1))
		return false;
		
	//Depending on the random, check if the upper or right wall should be 
	//removed based on previous removals
	if (dir == 0){
		newSetID = setChecker[start.y-1][start.x];
		if (newSetID == setID)
			return false;
		theMaze[start.y][start.x].upClear = true;
	}

	if (dir == 1){
		newSetID = setChecker[start.y][start.x+1];
		if (newSetID == setID)
			return false;
		theMaze[start.y][start.x].rightClear = true;
	}

	//Here renumber the big numbered-grid to start creating sets
	for (int row = 0; row < theMaze.size(); row++)
		for (int column = 0; column < theMaze[0].size(); column++)
			if (setChecker[row][column] == setID)
				setChecker[row][column] = newSetID;
}

//Resets the maze to have all the walls back up
//iterates through and sets all the clear boolean
//values to false
void createMaze::resetMaze(){
	//Placing all the walls back in the maze
	for (int row = 0; row < theMaze.size(); row++)
		for (int column = 0; column < theMaze[0].size(); column++){
			theMaze[row][column].upClear = false;
			theMaze[row][column].rightClear = false;
			setChecker[row][column] = (row*theMaze[0].size())+column;
		}

	//Iterate through every wall in the maze randomly and run
	//Kruskal's algorithm to create a path
	for (int counter = 0; counter < theMaze.size()*theMaze[0].size()*10; counter++)
		makeMaze(location(rand()%(int)theMaze[0].size(), rand()%(int)theMaze.size()));
	
	//Place the goal object at a random location in the maze
	goal = location(rand()%(int)(height()-1), rand()%(int)(width()-1));

	//If the goal object is placed on the player object, reset again
	if(goal.x == player.x && goal.y == player.y)
		resetMaze();

	//Add to score total
	score++;
}

//Move the player based on the permission boolean
void createMaze::movePlayer(int dir){
	if(stepChecker(dir, player)){
		player = partStepper(player, dir);
	
		//If move causes a collision between player and goal,
		//reset the maze (score total incremented in resetMaze)
		if(player.x == goal.x && player.y == goal.y)
			resetMaze();
	}
}

//References
location createMaze::findPlayer() {return player;}
float createMaze::height() {return theMaze.size();}
float createMaze::width() {return theMaze[1].size();}
location createMaze::findGoal() {return goal;}
createMaze::createMaze() {return;}

//Converts the integer 'score' to a string so it can be drawn 
//on the play screen
string createMaze::scoreString(){
	stringstream output;	
	output << "Your score: "<<score<<"/5";
	return output.str();
}







