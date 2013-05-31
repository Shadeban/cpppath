BOOST = D:/boost_1_53_0
objects = main.o mapparser.o ScenarioLoader.o maptraverser.o
CC = g++
CXX_LDFLAGS = -I$(BOOST) -o 
CXXFLAGS =  -I$(BOOST)  -O3
pathf.exe : $(objects)
	$(CC) $(CXX_LDFLAGS) pathf.exe $(objects)  
main.o : mapparser.h
mapparser.o : mapparser.h
ScenarioLoader.o : ScenarioLoader.h
maptraverser.o: maptraverser.h

.PHONY : clean
clean:
	rm -f $(objects) pathf.exe 
