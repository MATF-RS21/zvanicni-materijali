PROGRAM   = collections
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall -Wextra

$(PROGRAM): main.o vector.o set.o map.o forward_list.o list.o deque.o
	$(CXX) -o $(PROGRAM) $^

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *
