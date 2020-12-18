PROGRAM  = shared
CXX      = g++
LD       = g++
CXXFLAGS = -g -std=c++17 -Wall
LDFLAGS  = -L./lib/ -lmatf

$(PROGRAM): main.o libmatf.so
	$(LD) -o $(PROGRAM) $< $(LDFLAGS) 

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $<

libmatf.so: list.o fraction.o
	$(CXX) -shared -o $@ $^
	mkdir -p lib
	mv $@ lib/$@
	rm $^

list.o: list.cpp 
	$(CXX) -fPIC $(CXXFLAGS) -c $<

fraction.o: fraction.cpp 
	$(CXX) -fPIC $(CXXFLAGS) -c $<

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)
	-rm lib/*.so 
	-rmdir lib 

dist: clean
	tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)


