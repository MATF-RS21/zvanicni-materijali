PROGRAM  = static
CXX      = g++
LD       = g++
CXXFLAGS = -g -std=c++17 -Wall
LDFLAGS  = -L./lib/ -lmatf

$(PROGRAM): main.o libmatf.a
	$(LD) -o $(PROGRAM) $< $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $<

libmatf.a: list.o fraction.o
	ar -crs $@ $^
	mkdir -p lib
	mv $@ lib/$@
	rm $^

list.o: list.cpp 
	$(CXX) $(CXXFLAGS) -c $<

fraction.o: fraction.cpp 
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)
	-rm lib/*.a 
	-rmdir lib 

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)


