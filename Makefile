#Ian Forsyth
#CPSC 478
#Final Project

#Makefile, adapted from the makefile in raytracer example

INCLUDE =-I/usr/include -I/usr/local/include  -O2 -march=x86-64 -fmessage-length=0 -Wall -I/usr/X11R6/include

LIBDIR = -L/usr/X11R6/lib -Wl,-rpath

LIBS = -lfltk -lfltk_gl -lXext -lX11 -lm -lGL -lGLU -lglut -o Maze

CFLAGS = -g -O

CC = g++

.SUFFIXES: .o .cpp .cxx

.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $*.o $<

.cxx.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $*.o $<

ALL.O = createMaze.o interaction.o display.o

Maze: $(ALL.O)
	$(CC) $(CFLAGS) -o $@ $(ALL.O) $(INCLUDE) $(LIBDIR) $(LIBS)

clean:
	rm -f interaction createMaze *.o
