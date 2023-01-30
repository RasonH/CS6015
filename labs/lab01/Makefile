#all - build everything and run executable at the same time as the lab required to
#program - link all object files together for generating an executable
#*.o - create seperate .o files, reduce compilation to only those changed files
#clean - deletes compiled link and executable files

CXX = c++
CFLAGS = -std=gnu++11
OBJS = main.o Caps.o Clothing.o Pants.o
CXXSOURCE = main.cpp Caps.cpp Clothing.cpp Pants.cpp
HEADERS = Caps.h Clothing.h Pants.h


all: program
	./program

program: $(OBJS)
	$(CXX) $(OBJS) -o program
	
main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

Caps.o: Caps.cpp Caps.h
	$(CXX) $(CFLAGS) -c Caps.cpp
	
Clothing.o: Clothing.cpp Clothing.h
	$(CXX) $(CFLAGS) -c Clothing.cpp

Pants.o: Pants.cpp Pants.h
	$(CXX) $(CFLAGS) -c Pants.cpp



.PHONY:clean printM

printM:
	echo "CXX = $(CXX)\nCFLAGS = $(CFLAGS)\nOBJS = $(OBJS)\nCXXSOURCE = $(CXXSOURCE)\nHEADERS = $(HEADERS)"

clean:
	rm -rf *.o *.out program
