#include "maptraverser.h"
MapTraverser::MapTraverser(MapParser* mapParser) :mapParser(mapParser){
	createNodes();
}
void MapTraverser::createNodes(){
	if(!nodes.empty()){nodes.clear();}	
	for(int i = 0; i < mapParser->mapSize(); i++){
		
		if(mapParser->map[i]){
			Node* node = getNode(i, true);
			vector<int> neighborIds;
			vector<double> neighborDists;
			mapParser->allNeighbors(i, neighborIds, neighborDists);
			for(int k = 0; k < neighborIds.size(); k++){
				node->neighbors.insert(pair<Node *, double>(getNode(neighborIds[k], false), neighborDists[k]));
			}			
		}	
	}
	cout << nodes.size();
}

Node* MapTraverser::getNode(int index, bool create = false){
	if(index == 100077){
		cout << "start index " << create << endl;
	}
	if(nodes.find(index) == nodes.end() && create){
		Node* a = new Node;
		a->score = 1.0/0.0;
		a->index = index;
		a->prev = NULL;			
		nodes[index] = a;		
	} else if (!create) {
		cout << "node not found" << endl;
		return NULL;
	}
	return nodes[index];


}

double MapTraverser::djikstra(int start, int end) {
	priority_queue<Node *, vector<Node *>, CompareNode> open;
	cout << "open declared" << endl;
	getNode(start)->score = 0;
	cout << "get node start set score" << endl;
	open.push(getNode(start));
	while (!open.empty()){
		Node* current = open.top();
		open.pop();
		cout << "open topped and popped";
		map<Node *, double>::iterator iter;  
		for(iter = current->neighbors.begin(); iter != current->neighbors.end(); ++iter){
			Node * neighbor = iter->first;
			cout << "neighbor declared" << endl;
			double neighborDist = iter->second + current->score;
			cout << "neighbor Dist" << endl;
			if(neighbor->index == end){return neighborDist;}	
			if(neighborDist < neighbor->score ){

				neighbor->score = neighborDist;
				cout << "neighbor score set" << endl;
				open.push(neighbor);	
			}
			
		
		}
	
	}




}
