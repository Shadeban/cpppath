#ifndef _map_traverser_h
#define _map_traverser_h
#include "mapparser.h"
#include <memory>
#include <map>
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
		MapTraverser(MapParser* mapParser) :mapParser(mapParser){};
	private:
		void createNodes();
		shared_ptr<Node> getNode(int index, bool create);
		MapParser * mapParser;
		map<int, shared_ptr<Node> > nodes;
};

static const double sqrtTwo = 1.41421356237309504880168872420969807857; // sqrt(2)
#endif
