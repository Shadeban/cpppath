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
	cout << 3.1 << endl;
	pair<double, int> a_pairs[] = {make_pair(3.1, 1), make_pair(2.1, 2), make_pair(1.1, 3)};
	vector<pair<double, int>* > pairs;
	pairs.push_back(&a_pairs[0]);
	pairs.push_back(&a_pairs[1]);
	pairs.push_back(&a_pairs[2]);

	cout << "pairs front" << pairs.front()->first << endl;
	make_heap(pairs.begin(), pairs.end(), ComparePair());
	cout << "after make heap " << pairs.front()->first << "  " <<a_pairs[0].first << endl;
	a_pairs[1].first = 0.001;
		
	make_heap(pairs.begin(), pairs.end(), ComparePair());
	cout << "after make heap 2 " << pairs.front()->first << endl;
	
	ScenarioLoader sceneLoader("./map/Aurora.map.scen");

	cout << sceneLoader.GetNumExperiments();
	MapParser map("./map/Aurora.map");	
	map.parse();	
	return 0;
}
