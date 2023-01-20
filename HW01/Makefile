#all - build everything and run executable at the same time as the lab required to
#program - link all object files together for generating an executable
#*.o - create seperate .o files, reduce compilation to only those changed files
#clean - deletes compiled link and executable files

CXX = c++
CFLAGS = -std=gnu++11
OBJS = main.o cmdline.o
CXXSOURCE = main.cpp cmdline.cpp
HEADERS = cmdline.h

msdscript: $(OBJS)
	$(CXX) $(OBJS) -o msdscript
	
main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

cmdline.o: cmdline.cpp cmdline.h
	$(CXX) $(CFLAGS) -c cmdline.cpp

.PHONY:clean
clean:
	rm -rf *.o *.out msdscript
