#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <functional>
#include <vector>
#include <cmath>
#include "mapparser.h"
#include "maptraverser.h"
#include "ScenarioLoader.h"
using namespace std;
class ComparePair
{
	public:
		bool operator()(const pair<double, int>* p1, const pair<double, int>* p2) const
		{
			return p1->first > p2->first;
		}
};

int main ( int argc, const char* argv[])
{
	
	ScenarioLoader sceneLoader("./map/Aurora.map.scen");

	cout << sceneLoader.GetNumExperiments();
	MapParser map("./map/Aurora.map");	

	map.parse();	
	
	MapTraverser traverse(&map);
	cout << traverse.djikstra(749 + 1024 * 97, 749 + 1024 * 104);
	return 0;
}
