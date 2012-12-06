//Ian Forsyth
//CPSC 478
//Final Project

#ifndef PART_H
#define PART_H

//Maze is made of parts, telling whether the up or right is passable

class part {
	public:
		bool upClear;
		bool rightClear;

		part(bool up, bool right){
			upClear = up;
			rightClear = right;
		}
		
		part(){
			upClear = NULL;
			rightClear = NULL;
		}
};

#endif
