#ifndef _map_traverser_h
#define _map_traverser_h
#include "mapparser.h"
#include <memory>
#include <map>
#include <queue>
#include <cmath>
using namespace std;

struct Node{
	int index;
	double score;
	double dist;
	bool visited;
	bool closed;
	Node* prev;
	map<Node*, double> neighbors;
};

class CompareNode {
	public:
		bool operator()(const Node* n1, const Node* n2) {
			return n1->score > n2->score;		
		}
};

class MapTraverser{
	public:
		MapTraverser(MapParser* mapParser); 
		double djikstra(int start, int end);		
		double astar(int start, int end);		
		void resetNodes();
		double heuristic(int start, int end);
	private:
		void createNodes();
		void outputpath(Node* end);
		Node* getNode(int index, bool create);
		MapParser * mapParser;
		map<int, Node* >* nodes;
		vector<int>* dirtyNodes;
};


static const double infDouble = 1.0 / 0.0; //inf 
static const double diagCoef = sqrtTwo - 2;

#endif
