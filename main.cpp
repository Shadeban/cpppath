#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <functional>
#include <vector>
#include <cmath>
#include <ctime>
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

void outputTime(){
	time_t t = time(0);
	struct tm * now = localtime( &t);
	cout << asctime(now);
}
int main ( int argc, const char* argv[])
{
	outputTime();
	ScenarioLoader sceneLoader("D:/Projects/all/cpp/path/map/Aurora.map.scen");
	outputTime();
	cout << "scenario loaded" << endl;
	MapParser map("D:/Projects/all/cpp/path/map/Aurora.map");	

	map.parse();	
	outputTime();
	cout << "map parsed" << endl;	
	MapTraverser traverse(&map);
	outputTime();
	cout << "traverser initialized" << endl;
	cout << traverse.heuristic(176 + 639 * 1024, 294 + 639 * 1024) << endl;
	cout << traverse.heuristic(177 + 639 * 1024, 294 + 639 * 1024) << endl;
	time_t start = time(0);
	int startExp = 800;
	int endExp =  1000;//sceneLoader.GetNumExperiments();
	
//	for(int i = startExp; i < endExp; i++){
//		traverse.resetNodes();	
//		Experiment experiment = sceneLoader.GetNthExperiment(i);
//		bool match = traverse.djikstra(experiment.GetStartX() + experiment.GetStartY() * 1024, experiment.GetGoalX() + 1024 * experiment.GetGoalY()) ==  experiment.GetDistance();
//		if(match) {cout << ".";}
//		else {cout << endl << experiment.GetDistance() << endl;}
//	}

//	cout << difftime(start, time(0)) << " seconds total dj" << endl;
	start = time(0);
	for(int i = startExp; i < endExp; i++){
		traverse.resetNodes();	
		Experiment experiment = sceneLoader.GetNthExperiment(i);
		double result = traverse.astar(experiment.GetStartX() + experiment.GetStartY() * 1024, experiment.GetGoalX() + 1024 * experiment.GetGoalY());
		bool match = abs(result -  experiment.GetDistance()) < 0.001;
		if(match) {cout << ".";}
		else {cout << endl << result << " =/=" << experiment.GetDistance() << endl;}
	}

	cout << difftime(start, time(0)) << " seconds total as" << endl;
	return 0;
}


