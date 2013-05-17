objects = main.o mapparser.o ScenarioLoader.o maptraverser.o
CXXFLAGS = -std=c++0x  
path.exe : $(objects)
	g++ -o path.exe $(objects)

main.o : mapparser.h
mapparser.o : mapparser.h
ScenarioLoader.o : ScenarioLoader.h
maptraverser.o: maptraverser.h
