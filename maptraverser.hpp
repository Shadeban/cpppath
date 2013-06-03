#ifndef _map_traverser_h
#define _map_traverser_h
#include "mapparser.hpp"
#include <memory>
#include <map>
#include <queue>
#include <cmath>
#include <boost/heap/priority_queue.hpp>
#include <boost/heap/fibonacci_heap.hpp>
using namespace std;

class CompareNode {
	public:
		bool operator()(const void* n1, const void* n2) const ;
};
struct Node{
	int index;
	double score;
	double dist;
	bool visited;
	bool closed;
	Node* prev;
	map<Node*, double> neighbors;
	boost::heap::fibonacci_heap<Node*, boost::heap::compare<CompareNode> >::handle_type handle;
	
};

inline bool CompareNode::operator()(const void* n1, const void* n2) const  {return ((Node*)n1)->score > ((Node*)n2)->score;}

typedef boost::heap::fibonacci_heap<Node*, boost::heap::compare<CompareNode> > NodeHeap;

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
