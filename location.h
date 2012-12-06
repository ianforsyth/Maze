//Ian Forsyth
//CPSC 478
//Final Project

//Location.h is a class used to keep the locations
//of the player object and goal object

#ifndef LOCATION_H	
#define LOCATION_H

class location {
public:
	float x;
	float y;
	location(float first, float second){
		x = first;
		y = second;
	}
	location(){
		x = NULL;
		y = NULL;
	}
};

#endif

