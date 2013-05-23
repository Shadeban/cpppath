#include "maptraverser.h"
MapTraverser::MapTraverser(MapParser* mapParser) :mapParser(mapParser){
	createNodes();
}
void MapTraverser::createNodes(){
	nodes = new map<int, Node*>();	
	for(int i = 0; i < mapParser->mapSize(); i++){
		
		if(mapParser->map[i]){
			Node* node = getNode(i, true);
			vector<int> neighborIds;
			vector<double> neighborDists;
			mapParser->allNeighbors(i, &neighborIds, &neighborDists);
			for(int k = 0; k < neighborIds.size(); k++){
				node->neighbors.insert(pair<Node *, double>(getNode(neighborIds[k], true), neighborDists[k]));
			}			
		}	
	}
}
void MapTraverser::resetNodes(){
	for(int i = 0; i < mapParser->mapSize(); i++){
		Node* node = getNode(i, true);
		if(node != NULL) {
			node->score = 1.0/0.0;
		
		}
	
	}


}
Node* MapTraverser::getNode(int index, bool create = false){
	if(nodes->count(index) != 1 ){
		if (create){	
			Node* a = new Node();
			a->score = 1.0/0.0;
			a->index = index;
			a->prev = NULL;			
			nodes->insert(pair<int,Node*>(index, a));	
		}else if (!create) {
			return NULL;
		}

	} 
	
	
	
		
	return nodes->at(index);


}

double MapTraverser::djikstra(int start, int end) {
	priority_queue<Node *, vector<Node *>, CompareNode> open;
	getNode(start)->score = 0;
	open.push(getNode(start));
	while (!open.empty()){
		Node* current = open.top();
		open.pop();
		map<Node *, double>::iterator iter;  
		for(iter = current->neighbors.begin(); iter != current->neighbors.end(); ++iter){
			Node * neighbor = iter->first;
			double neighborDist = iter->second + current->score;
			if(neighbor->index == end){return neighborDist;}	
			if(neighborDist < neighbor->score ){

				neighbor->score = neighborDist;
				open.push(neighbor);	
			}
			
		
		}
	
	}




}
