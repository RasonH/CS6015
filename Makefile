#all - build everything and run executable at the same time as the lab required to
#program - link all object files together for generating an executable
#*.o - create separate .o files, reduce compilation to only those changed files
#clean - deletes compiled link and executable files

CXX = c++
CFLAGS = -std=c++11
OBJS = main.o cmdline.o expr.o test.o parse.o
CXXSOURCE = main.cpp cmdline.cpp expr.cpp test.cpp
HEADERS = cmdline.h catch.h expr.h test.h parse.h


msdscript: $(OBJS)
	$(CXX) $(OBJS) -o msdscript

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

cmdline.o: cmdline.cpp cmdline.h catch.h
	$(CXX) $(CFLAGS) -c cmdline.cpp

expr.o: expr.cpp expr.h
	$(CXX) $(CFLAGS) -c expr.cpp

test.o: test.cpp catch.h
	$(CXX) $(CFLAGS) -c test.cpp

parse.o: parse.cpp parse.h
	$(CXX) $(CFLAGS) -c parse.cpp

test_msdscript: test_msdscript.cpp exec.h
	$(CXX) $(CFLAGS) test_msdscript.cpp exec.cpp -o test_msdscript


.PHONY:clean test doc clean_test_msdscript
clean:
	rm -rf *.o *.out msdscript test_msdscript

test: msdscript
	./msdscript --test

doc:
	cd documentation && doxygen

clean_test_msdscript:
	rm test_msdscript.o test_msdscript