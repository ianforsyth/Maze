//Ian Forsyth
//CPSC 478
//Final Project

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <Fl/Fl_Multiline_Output.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Button.H>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "interaction.h"

using namespace std;

interaction theInteraction;
void displayWrapper();
void mouseWrapper(int x, int y);
void mouse2Wrapper(int button, int state, int x, int y);
void spinGoalWrapper(int useless);
void arrowKeysWrapper(int key, int x, int y);
void makeRasterFont(void);
void play();

void sizeCB(Fl_Widget* o, void*);
void sphereCB(Fl_Widget* o, void*);
void cubeCB(Fl_Widget* o, void*);
void donughtCB(Fl_Widget* o, void*);


int temp, theSize=0, playerShape=0;
char** temp2;

int main(int argc, char** argv){	
	temp = argc;
	temp2 = argv;

	//All the FLTK controls
	Fl_Window win (500,500, "window");

	//Title Box
	Fl_Box title(-5,-5,510,50,"Teapot Finder!");
  	title.box(FL_UP_BOX);
  	title.labelsize(36);
  	title.labelfont(FL_BOLD+FL_ITALIC);

	//Description section
	Fl_Multiline_Output desc(0,45,500,250,"");
	desc.value(
		" Welcome to Teapot Finder. This is a maze game, find the spinning teapot!\n\nControls:\n\t~Drag the mouse along the x axis (side to side) to control the camera.\n\t~Use the arrow keys to navigate the maze\n\t~Click the right mouse button for a bird's eye view\n\nSetup:\n\t~Choose the level of difficulty on the slider below (5=easy, 20=hard).\n\t  Then, choose your player!\n\nDescription:\n\t~In this game you must navigate through a maze and find the spinning\n\t  teapot. But be aware! Every time you find the teapot, it changes\n\t  location and maze regenerates! Find the teapot 5 times to win!");

	//Maze size slider, still getting a seg fault if never moved
	Fl_Value_Slider sizeSlider (100,300,300,50,"Maze Size (Must Slide To Prevent Seg Fault)");
	sizeSlider.type(FL_HORIZONTAL);
	sizeSlider.value(5);
	sizeSlider.minimum(5);
	sizeSlider.maximum(20);
	sizeSlider.step(1);
	sizeSlider.callback(sizeCB);

	//Buttons for different player shapes
    Fl_Button sphereButton (50,400,120,25,"Super Sphere");
    sphereButton.callback (sphereCB);
	Fl_Button cubeButton (200, 400, 120, 25, "Courageous Cube");
	cubeButton.callback (cubeCB);
	Fl_Button donughtButton (350, 400, 120, 25, "Doughnut!");
	donughtButton.callback (donughtCB);

    win.end();
    win.show();
    return Fl::run();

	return 0;
}

//Get maze size
void sizeCB(Fl_Widget* o, void*){
	Fl_Value_Slider* gettingValue = (Fl_Value_Slider*)o;
	theSize=gettingValue->value();
}

//Handling input for different shapes
void sphereCB(Fl_Widget* o, void*){	
	playerShape = 1;
	play();
}
void cubeCB(Fl_Widget* o, void*){
	playerShape = 2;
	play();
}
void donughtCB(Fl_Widget* o, void*){
	playerShape = 3;
	play();
}

void play(){
	theInteraction = interaction(theSize, 500, 500);

	//Create the glut window
	glutInit(&temp, temp2);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("TEAPOT FINDER!");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//Start with the perspective projection
	gluPerspective(60.0f, 1.0, 1.0, 400.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Enabling some default functions to remove hidden surfaces,
	//and add the lighting, all built into glut
	glEnable(GL_DEPTH_TEST); glEnable(GL_CULL_FACE);  
	glEnable(GL_LIGHTING); glEnable(GL_COLOR_MATERIAL);

	//Set lighting parameters
	GLfloat ambientLight[] = 
		{ 0.1f, 0.1f, 0.1f, 0.1f }; 
	GLfloat diffuseLight[] = 
		{ 0.8f, 0.8f, 0.8f, 0.0f };
	GLfloat specular[] = 
		{ 1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPos0[] = 
		{ 100.0f, 125.0f, 200.0f, 1.0f };

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	//Implement lighting paramets
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight); glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular); glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);
	glEnable(GL_LIGHT0);

	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.3f, 0.3f, 0.3f,1.0f);

	//Handle all user input through the mouse and keyboard
	glutDisplayFunc(displayWrapper); glutMotionFunc(mouseWrapper);
	glutMouseFunc(mouse2Wrapper); glutSpecialFunc(arrowKeysWrapper);
	glutTimerFunc(100, spinGoalWrapper, 0);
	
	glLineWidth(7);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	
	//Send shape preference
	theInteraction.playerObj = playerShape;
	glutMainLoop();
	
}
void spinGoalWrapper(int temp){
	theInteraction.spinGoal();
	//Determines how fast the goal object is rotating
	glutTimerFunc(80, spinGoalWrapper, 0);
}

//Wrapper functions to handle user input properly
void arrowKeysWrapper(int key, int x, int y){
	theInteraction.arrowKeys(key);
}

void displayWrapper(){
	theInteraction.display();
}

void mouseWrapper (int x, int y){
	theInteraction.mouse(x, y);
}

void mouse2Wrapper (int button, int state, int x, int y){
	theInteraction.mouse2(button, state, x, y);
}


