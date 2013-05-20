#ifndef _map_traverser_h
#define _map_traverser_h
#include "mapparser.h"
#include <memory>
#include <map>
#include <queue>
using namespace std;

struct Node{
	int index;
	double score;
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
	private:
		void createNodes();
		Node* getNode(int index, bool create);
		MapParser * mapParser;
		map<int, Node* > nodes;
};

#endif
