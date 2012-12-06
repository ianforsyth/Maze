//Ian Forsyth
//CPSC 478
//Final Project

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include <cstdlib> 
#include <time.h>  

#include <math.h>
#include <string>
#include "createMaze.h"
#include "interaction.h"


//Begin stacking matrixes for the score display
void interaction::beginText(){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);
}

//Draw the score
void interaction::drawBitmapString(float x, float y, float z, string score)
{
	glRasterPos3f(x, y, z);
	for(int counter = 0; score[counter] != '\0'; counter++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[counter]);
}

//Draw winner!
void interaction::drawStrokeString(float x, float y, float z, string winner)
{
	zoom = 15;
	glPushMatrix();
	glColor3f(0.0,1.0,1.0);
	glRasterPos3f(x, y, z);
	glTranslatef(x, y, z);
	for (int counter = 0; winner[counter] != '\0'; counter++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, winner[counter]);

	glPopMatrix();
}

//Finish displaying text
void interaction::endText(){
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

//Rotate the goal object
void interaction::spinGoal(){
	goalSpin += 25;

	if (goalSpin > 360)
		goalSpin = goalSpin - 360;

	glutPostRedisplay();
}

//Set all initial values
interaction::interaction(float mazeSize, int w, int h){
	theMaze = createMaze(mazeSize, mazeSize);

	height = h; 
	width = w;
	zoom = 5;

	yRot = 0; 
	goalSpin = 0; 
	cameraDir = 0;
	
	prevX=0; 
	yCounter=0; 
	yChecker=0;
}


void interaction::display(){
	//Clear the screen
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//Set the camera position
	gluLookAt(0,sin(44.7)*zoom, cos(44.7)*zoom,  0,0,0,  0,1,-1);

	//Handle the mouse controlled Y rotation
	glRotatef(yRot, 0, 1, 0);
	draw();
	glPopMatrix();
	
	//Draw the score (or WINNER)
	beginText();
	if(theMaze.score == 5)
		drawStrokeString(10, height-300, 0, "WINNER");
	else{	
		drawBitmapString(10, height-25, 0, "Teapot Finder!");
		drawBitmapString(10, height-50, 0, theMaze.scoreString());
	}
	endText();

	glutSwapBuffers();
}


void interaction::arrowKeys(int key){
	//Don't allow any movement after player has won.
	if(theMaze.score == 5){}
	else

	switch(key){
		case GLUT_KEY_UP:  //move ball up.
			theMaze.movePlayer((0+cameraDir)%4);
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:  //move ball left.
			theMaze.movePlayer((3+cameraDir)%4);
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:  //move ball down.
			theMaze.movePlayer((2+cameraDir)%4);
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:  //move ball right.
			theMaze.movePlayer((1+cameraDir)%4);
			glutPostRedisplay();
			break;
  	}
}
void interaction::mouse (int x, int y){
	int dir = 0;

	//Dragging right to left
	if(yChecker > x){
		yCounter += 1;
		dir = 1;
	}
	//Dragging left to right
	else{
		yCounter -=1;
		dir = 2;
	}
	yRot = prevX+yCounter;

	//Rotate the camera and change control orientation based on angle
	//This can be somewhat buggy still.
	if(dir==1){
		if(yRot>=360)
			yRot = yRot - 360;
		if(yRot == 45 || yRot == 135 || yRot == 225 || yRot == 315)
			orientLeft();
	}
	if(dir==2){
		if(yRot<=0)
			yRot = 360 - yRot;
		if(yRot == 45 || yRot == 135 || yRot == 225 || yRot == 315)
			orientRight();	
	}
	
	yChecker=x;
}
void interaction::mouse2(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		prevX = yRot;
		yCounter = 0;
	}
	if(button == GLUT_RIGHT_BUTTON){
		if(state == GLUT_DOWN)
			zoom = 15;
		else
			zoom = 5;
	}
}

//Function used to draw the walls on screen. Renders the left, right, front, back, and top
//of wall, no need for bottom
inline void interaction::drawWall(float xA, float yA, float zA, float xB, float yB, float zB){
	glNormal3f(-1, 0, 0);	//Left
		glVertex3f(xA, yA, zA); glVertex3f(xA, yA, zB); 
		glVertex3f(xA, yB, zB); glVertex3f(xA, yB, zA);
	glNormal3f(1, 0, 0);	//Right
		glVertex3f(xB, yA, zB);	glVertex3f(xB, yA, zA); 
		glVertex3f(xB, yB, zA); glVertex3f(xB, yB, zB);
	glNormal3f(0, 0, 1);	//Front
		glVertex3f(xA, yA, zB); glVertex3f(xB, yA, zB); 
		glVertex3f(xB, yB, zB); glVertex3f(xA, yB, zB);
	glNormal3f(0, 0, -1);	//Back	
		glVertex3f(xA, yA, zA); glVertex3f(xA, yB, zA); 
		glVertex3f(xB, yB, zA);	glVertex3f(xB, yA, zA);
	glNormal3f(0, 1, 0); 	//Top 	
		glVertex3f(xA, yB, zA); glVertex3f(xA, yB, zB); 
		glVertex3f(xB, yB, zB); glVertex3f(xB, yB, zA);
}

//Draws the the bottom and left maze border, player object, and goal object
void interaction::draw(){
	glTranslatef(0,.5, 0);
	//cout<<"Actual: "<<playerObj<<"\n";
	//Super sphere	
	if(playerObj == 1){
		glColor3f(0, 1, 1);	
		glutSolidSphere(0.32f, 13, 26);
	}
	//Courageous Cube
	else if(playerObj == 2){
		glColor3f(0, 1, 0);
		glutSolidCube(0.5);
	}
	//Doughnut!
	else if(playerObj == 3){
		glColor3f(1.0, 0.2, 0.7);
		glutSolidTorus(0.1, 0.3, 12, 12);
	}

	glTranslatef(-.4-theMaze.findPlayer().x, -0.5, -.4-theMaze.findPlayer().y);
	
	glBegin(GL_QUADS);
		//Color of the floor of the maze
		glColor3f(0,0,0);
		
		float mazeHeight = theMaze.height();
		float mazeWidth = theMaze.width();
	
		//Big floor square
		drawWall(0, -0.01, -0.2, mazeWidth, 0, mazeHeight-0.2);
		
		//Color of the walls of the maze
		glColor3f(1,0,0);

		//Draw the left and bottom border of the maze
		drawWall(-0.2, 0, -0.2, 0, 1, mazeHeight-.2); 
		drawWall(-0.2, 0, mazeHeight-.2, mazeWidth, 1, mazeHeight); 
	glEnd();
	
	for (int counter = 0; counter < mazeHeight; counter++){
		for (int counter2 = 0; counter2 < mazeWidth; counter2++){
			glBegin(GL_QUADS);
				drawWall(0.8, 0.0, -0.2, 1.0, 1.0, 0.0);
				if (!theMaze.stepChecker(0, location(counter2, counter)))
					drawWall(0.0, 0.0, -0.2, 0.8, 1.0, 0.0);
				if (!theMaze.stepChecker(1, location(counter2, counter)))
					drawWall(0.8, 0.0, 0.0, 1.0, 1.0, 0.8);
			glEnd();
			glTranslatef(1, 0, 0);
		}
		glTranslatef(-mazeWidth, 0, 1);
	}

	glPushMatrix();
	glTranslatef(theMaze.findGoal().x+0.4, 0.5, theMaze.findGoal().y-theMaze.height()+0.4);
	glColor3f(1.0, 1.0, 0.0); 
	glRotatef(goalSpin, 0, 1, 0);
	glutSolidTeapot(.25);
	glPopMatrix();
	glPopMatrix();
}


void interaction::orientRight(){
	if (cameraDir == 0)
		cameraDir = 3;
	else
		cameraDir--;
}

void interaction::orientLeft(){
	if(cameraDir == 3)
		cameraDir = 0;
	else
		cameraDir++;
}

void interaction::reshapeViewport(int w, int h){
	height = h;
	width = w;
}

interaction::interaction(){
	return;
}

