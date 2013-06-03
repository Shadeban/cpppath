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
	ScenarioLoader * sceneLoader = new ScenarioLoader("D:/Projects/all/cpp/path/map/Enigma.map.scen");
	outputTime();
	cout << "scenario loaded" << endl;
	MapParser * map = new MapParser("D:/Projects/all/cpp/path/map/Enigma.map");	
	bool djikstra = false;
	map->parse();	
	outputTime();
	cout << "map parsed" << endl;	
	MapTraverser * traverse = new MapTraverser(map);
	outputTime();
	cout << "traverser initialized" << endl;
	time_t start = time(0);
	int startExp = 0;//sceneLoader->GetNumExperiments() ;
	int endExp = sceneLoader->GetNumExperiments();
	if(djikstra){	
	for(int i = startExp; i < endExp; i++){
		traverse->resetNodes();	
		Experiment experiment = sceneLoader->GetNthExperiment(i);
		double result = traverse->djikstra(experiment.GetStartX() + experiment.GetStartY() * map->getX(), experiment.GetGoalX() + map->getX() * experiment.GetGoalY());
		bool match = abs(result -  experiment.GetDistance()) < 0.01;
		if(match) {cout << "\r" << i << "/" << sceneLoader->GetNumExperiments();}
		else {cout << endl << result << " =/=" << experiment.GetDistance() << endl;}
	}

	cout << difftime(start, time(0)) << " seconds total dj" << endl;
	}	
	start = time(0);
	for(int i = startExp; i < endExp; i++){
		traverse->resetNodes();	
		Experiment experiment = sceneLoader->GetNthExperiment(i);
		double result = traverse->astar(experiment.GetStartX() + experiment.GetStartY() * map->getX(), experiment.GetGoalX() + map->getX() * experiment.GetGoalY());
		bool match = abs(result -  experiment.GetDistance()) < 0.01;
		if(match) {cout << "\r" << i + 1 << "/" << sceneLoader->GetNumExperiments();}
		else {cout << endl << result << " =/=" << experiment.GetDistance() << endl;}
	}

	cout << difftime(start, time(0)) << " seconds total as" << endl;
	return 0;
}


