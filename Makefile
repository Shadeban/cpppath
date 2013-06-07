BOOST = D:/boost_1_53_0
objects = main.o mapparser.o ScenarioLoader.o maptraverser.o
CC = g++
CXX_LDFLAGS = -I$(BOOST) -o 
CXXFLAGS =  -I$(BOOST) -g 
pathf.exe : $(objects)
	$(CC) $(CXX_LDFLAGS) pathf.exe $(objects)  
main.o : mapparser.o maptraverser.o
mapparser.o : mapparser.hpp
ScenarioLoader.o : ScenarioLoader.h
maptraverser.o: maptraverser.hpp

.PHONY : clean
clean:
	rm -f $(objects) pathf.exe 
