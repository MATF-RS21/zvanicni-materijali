PROGRAM = helloclass
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall

$(PROGRAM): helloclass_test.o catch.o
	$(CXX) -o $(PROGRAM) $^
	
helloclass_test.o: test.cpp HelloClass.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
catch.o: catch.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *
