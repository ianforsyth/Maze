#Ian Forsyth
#CPSC 478
#Final Project

#Makefile, adapted from the makefile in raytracer example

INCLUDE =-I/usr/include -I/usr/local/include -fmessage-length=0 -Wall -I/usr/X11R6/include

LIBDIR = -L/usr/X11R6/lib -Wl,-rpath

ALL.O = createMaze.o interaction.o display.o

LIBS =-Wl,--start-group -lfltk -lfltk_gl -lXext -lX11 -lm -lGL -lGLU -lglut $(ALL.O) -Wl,--end-group

CC = g++

.SUFFIXES: .o .cpp .cxx

.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $*.o $< 

.cxx.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $*.o $<



Maze: $(ALL.O)
	$(CC) $(CFLAGS) -o $@ $(INCLUDE) $(LIBS)

clean:
	rm -f interaction createMaze *.o
