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

	MapParser map("./map/Aurora.map");	

	map.parse();	
	
	MapTraverser traverse(&map);
	for(int i = 1; i < sceneLoader.GetNumExperiments(); i++){
		traverse.resetNodes();	
		Experiment experiment = sceneLoader.GetNthExperiment(i);
		cout << traverse.djikstra(experiment.GetStartX() + experiment.GetStartY() * 1024, experiment.GetGoalX() + 1024 * experiment.GetGoalY()) << " =?= " << experiment.GetDistance() << endl;
	}
	return 0;
}
