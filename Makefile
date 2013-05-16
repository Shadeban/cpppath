objects = main.o mapparser.o

path.exe : $(objects)
	g++ -o path.exe $(objects)

main.o : mapparser.h
