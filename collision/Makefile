all: message collision tessellation lines

message:
	@echo Compiling Collision test

lines: Intermediate/lines.o
	g++ -Wall Intermediate/lines.o -o lines -lclanCore -g  -lclanApp -lclanDisplay

collision: Intermediate/collision.o
	g++ -Wall Intermediate/collision.o -o collision -lclanCore -g -fprofile-arcs -ftest-coverage -pg -a -lclanApp -lclanDisplay

tessellation: Intermediate/tessellation.o
	g++ -Wall Intermediate/tessellation.o -o tessellation -lclanCore -g  -lclanApp -lclanDisplay

clean:
	@rm -Rf Intermediate
	@rm -f collision 
	@rm -f tessellation

distclean: clean

Intermediate/%.o : %.cpp
	@echo "  Compiling $<..."
	@if [ ! -d Intermediate ]; then mkdir Intermediate; fi
	gcc -Wall -c $< -o $@
