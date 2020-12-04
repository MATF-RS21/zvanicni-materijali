PROGRAM = biginteger
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall

$(PROGRAM): biginteger_test.o catch.o
	$(CXX) -o $(PROGRAM) $^
	
biginteger_test.o: test.cpp BigInteger.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
catch.o: catch.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *
