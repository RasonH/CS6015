#all - build everything and run executable at the same time as the lab required to
#program - link all object files together for generating an executable
#*.o - create seperate .o files, reduce compilation to only those changed files
#clean - deletes compiled link and executable files

CXX = c++
CFLAGS = -std=gnu++11
OBJS = main.o cmdline.o expr.o
CXXSOURCE = main.cpp cmdline.cpp expr.cpp
HEADERS = cmdline.h catch.h expr.h

msdscript: $(OBJS)
	$(CXX) $(OBJS) -o msdscript

#%.o : %.h

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

cmdline.o: cmdline.cpp cmdline.h catch.h
	$(CXX) $(CFLAGS) -c cmdline.cpp

expr.o: expr.cpp expr.h catch.h
	$(CXX) $(CFLAGS) -c expr.cpp

.PHONY:clean
clean:
	rm -rf *.o *.out msdscript
