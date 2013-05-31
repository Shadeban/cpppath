objects = main.o mapparser.o ScenarioLoader.o maptraverser.o
CC = g++
CXX_LDFLAGS = -o
CXXFLAGS =  -O2 -g
pathf.exe : $(objects)
	$(CC) $(CXX_LDFLAGS) pathf.exe $(objects)  
main.o : mapparser.h
mapparser.o : mapparser.h
ScenarioLoader.o : ScenarioLoader.h
maptraverser.o: maptraverser.h

.PHONY : clean
clean:
	rm -f $(objects) pathf.exe 
