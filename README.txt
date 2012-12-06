Ian Forsyth
CPSC 478
Final Project - Teapot Finder!

TO RUN: SIMPLY TYPE "make" AND THEN RUN ./Maze

DESCRIPTION & GAMEPLAY:
In this folder are the source files to run my final project game titled "Teapot Finder." It is very close to the final product I expected with only a couple elements missing and some tiny bugs I couldn't quite work out in time.

The game is programmed using c++, openGL, glut, and fltk. 

The object of the game is to navigate through a maze and find the spinning teapot. Every time the teapot is found, it is moved and the maze is regenerated around the player. To win the game, the player must find the teapot 5 times. The score is recorded in the upper left corner of the screen.

Gameplay starts with a fltk prompt that gives the title and description of the game. The description gives the object of the game and the controls. The player uses the slider to pick a value between 5 and 20, this is the size of the maze and dictates the difficulty of the game. The player then clicks one of three buttons, choosing which object to play as (Super Sphere, Courageous Cube, or Doughnut!).

Then the fltk window is disabled and the glut window appears. A maze is generated and the player object and goal object are placed in opposite corners.

To play the game, the player uses the mouse and arrow keys. The arrow keys are used to move the object within the maze. The left mouse button changes the camera angle by clicking and dragging on the window. The right mouse button allows the player to zoom out and get a bird's eye view of part of the maze.

----------------------------

METHODS AND INTERESTING ELEMENTS

The maze is based on "parts." Each part of the overall maze has a boolean variable determining if there is a wall above or to the right (no need for bottom or left, can just check neighboring part to avoid redundancy). 

The maze generation itself is a randomized implementation of Kruskal's algorithm. 

The process basically takes a maze and puts up all the walls. Then they are taken down one at a time if they belong to distinct sets. Eventually it becomes one big set, allowing for a clear path through the maze.

The objects in the maze are rendered through glut. The maze is made of boxes, the player object is either a sphere, cube, or torus, and the goal object is a Utah teapot. 

The score is displayed using a glut function and when the player wins, "WINNER" is displayed on the screen and gameplay is frozen.

Collision detection is handled through the grid based algorithm. It prevents the user from moving through the maze walls, beyond the boundary of the maze, and records when the player finds the object.

The goal object (teapot) rotates on its own based on a timer.

Rotating the camera was a tough part to get right because the arrow keys had to be adjusted based on the angle. If the rotation goes beyond a 45 degree plane, the controls are rotated too.

-----------------------------

UNFINISHED POINTS

There were a couple other things I wanted to do but ran out of time. I wanted to use my elephant from the transformations assignment and have it search through the maze for a peanut but I never got around to making that work. 

I also wanted to add an evil AI element that roamed through the maze. The player would have to avoid it, colliding with it would result in a subtraction from the score.

-----------------------------

KNOWN BUGS

There are two known bugs. First, in the fltk window, if the slider is left at the default value of 5, the program seg faults and terminates. It runs fine if the slider is moved, even if moved away from and then back to 5 but it must be moved at least 1 step. Second, in some cases, changing the camera angle can result in the arrow keys not corresponding to the correct direction in the maze. I couldn't isolate the exact reason this happens** but it does occur more often if the dragging is violent or circular. Simply dragging horizontally works fine. 

**With some trial and error, I found that if you first drag the mouse from left to right, the controls get mixed up. If the first dragging motion is right to left (anything after that first motion doesn't matter) the controls stay matched to the camera angle.

------------------------------

SOURCES

The libraries used were openGL, glut, and fltk. I used the documentation frequently for glut when learning it.

The maze generation algorithm is based on the one the wikipedia page on maze generation algorithms. I used kruskal's randomized algorithm because I thought it would be the simplest to implement. http://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_Kruskal.27s_algorithm 

I used a beginner fltk tutorial to learn how to make the gui: http://www3.telus.net/public/robark/

I used two tutorials (and looked at the source code) from two sites to get a handle on glut. They were http://www.lighthouse3d.com/opengl/glut/ and http://mindfuck.de-brauwer.be/articles/glut/


