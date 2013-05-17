#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <functional>
#include <vector>
#include <cmath>
#include "mapparser.h"
#include "ScenarioLoader.h"
using namespace std;
int main ( int argc, const char* argv[])
{

	vector<pair<int, double> > pairs;
	pairs.push_back(make_pair(3.0, 1));	
	pairs.push_back(make_pair(2.0, 2));
	pairs.push_back(make_pair(1.0, 3));
	cout << "pairs front" << pairs.front().first << endl;
	make_heap(pairs.begin(), pairs.end(), greater<pair<int, double> >());
	cout << "after make heap" << pairs.front().first << endl;
	cout << "infi" << (1.414 < INFINITY) << endl;	
	ScenarioLoader sceneLoader("./map/Aurora.map.scen");

	cout << sceneLoader.GetNumExperiments();
	MapParser map("./map/Aurora.map");	
	map.parse();	
	return 0;
}
