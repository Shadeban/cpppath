#include <iostream>
#include <fstream>
#include "mapparser.h"
using namespace std;
int main ( int argc, const char* argv[])
{
	MapParser map = MapParser("./map/Aurora.map");	
	map.parse();	
	return 0;
}
