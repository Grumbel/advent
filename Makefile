OBJECTS = Advent.o Background.o AdventObj.o Scenario.o CollisionMap.o \
	  Inventory.o Coin.o Font.o GuileAdventObj.o AdventObjSmob.o

Advent : $(OBJECTS)
	g++ $(OBJECTS) -o Advent -lclanCore -lclanPNG -lclanJPEG -lguile -lqthreads

clean: 
	rm $(OBJECTS) Advent

Advent.o : Advent.cc Advent.hh Scenario.hh
Background.o : Background.hh Background.cc Advent.hh
AdventObj.o : AdventObj.cc AdventObj.hh Position.hh Scenario.hh Advent.hh
Scenario.o :  AdventObj.hh Scenario.cc Scenario.hh
CollisionMap.o : CollisionMap.cc CollisionMap.hh
Inventory.o : Inventory.cc Inventory.hh AdventObj.hh
Coin.o : Coin.cc Coin.hh Advent.hh
Font.o : Font.cc Font.hh Advent.hh
GuileAdventObj.o : GuileAdventObj.hh GuileAdventObj.cc Advent.hh
AdventObjSmob.o : AdventObjSmob.cc AdventObjSmob.hh AdventObj.hh

# EOF #