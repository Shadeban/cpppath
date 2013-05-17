objects = main.o mapparser.o ScenarioLoader.o

path.exe : $(objects)
	g++ -o path.exe $(objects)

main.o : mapparser.h
mapparser.o : mapparser.h
ScenarioLoader.o : ScenarioLoader.h
