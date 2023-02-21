#all - build everything and run executable at the same time as the lab required to
#program - link all object files together for generating an executable
#*.o - create separate .o files, reduce compilation to only those changed files
#clean - deletes compiled link and executable files

CXX = c++
CFLAGS = -std=c++11
OBJS = main.o cmdline.o expr.o test.o
CXXSOURCE = main.cpp cmdline.cpp expr.cpp test.cpp
HEADERS = cmdline.h catch.h expr.h test.h

msdscript: $(OBJS)
	$(CXX) $(OBJS) -o msdscript

#%.o : %.h

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

cmdline.o: cmdline.cpp cmdline.h catch.h
	$(CXX) $(CFLAGS) -c cmdline.cpp

expr.o: expr.cpp expr.h
	$(CXX) $(CFLAGS) -c expr.cpp

test.o: test.cpp catch.h expr.h
	$(CXX) $(CFLAGS) -c test.cpp

parse.o: parse.cpp parse.h
	$(CXX) $(CFLAGS) -c parse.cpp

.PHONY:clean test
clean:
	rm -rf *.o *.out msdscript

test: msdscript
	./msdscript --test

.PHONY: doc
doc:
	cd documentation && doxygen
