PROGRAM  = plugin
CXX      = g++
LD       = g++
CXXFLAGS = -g -std=c++17 -Wall
LDFLAGS  = -ldl # Moramo da povezemo sa bibliotekom "libdl.so"

$(PROGRAM): main.o libmatf.so
	$(LD) -o $(PROGRAM) $< $(LDFLAGS) 

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $<

libmatf.so: triangle.o
	$(CXX) -shared -o $@ $^
	mkdir -p lib
	mv $@ lib/$@
	rm $^

triangle.o: triangle.cpp 
	$(CXX) -fPIC $(CXXFLAGS) -c $<

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)
	-rm lib/*.so 
	-rmdir lib 

dist: clean
	tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
