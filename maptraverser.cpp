#include "maptraverser.h"
MapTraverser::MapTraverser(MapParser* mapParser) :mapParser(mapParser){
	createNodes();
	//dirtyNodes = new vector<int>();
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
	for(map<int, Node*>::iterator iter = nodes->begin(); iter != nodes->end(); iter++){
		iter->second->score = infDouble;
		iter->second->visited = false;
		iter->second->prev = NULL;
	}
	/*for(int i = 0; i < mapParserdirtyNodes->size(); i++){
		Node* node = getNode(dirtyNodes->at(i), true);
		if(node != NULL) {
			node->score = infDouble;
		
		}
	
	}*/
	//dirtyNodes->clear();


}
Node* MapTraverser::getNode(int index, bool create = false){
	if(nodes->count(index) != 1 ){
		if (create){	
			Node* a = new Node();
			a->score = infDouble;
			a->index = index;
			a->visited = false;	
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
	Node* current;
	Node* neighbor;
	double neighborDist;
	map<Node *, double>::iterator iter;  
	while (!open.empty()){
		current = open.top();
		open.pop();
		if(current->visited) {
			continue;
		}	
		current->visited = true;
		for(iter = current->neighbors.begin(); iter != current->neighbors.end(); ++iter){
			neighbor = iter->first;
			if(neighbor->visited){
				continue;
			}
			neighborDist = iter->second + current->score;
			if(neighbor->index == end){return neighborDist;}	
			if(neighborDist < neighbor->score ){
				neighbor->score = neighborDist;
				open.push(neighbor);	
			}
			
		
		}
	
	}




}
double MapTraverser::heuristic(int start, int end){
	int dx = abs(start % 1024 - end % 1024);
	int dy = abs(start / 1024 - end / 1024);
	return dx + dy  + (diagCoef * min(dx,dy));	


}

void MapTraverser::outputpath(Node* end){
	Node* current = end;
	while(current->prev != NULL){
		cout << current->index % 1024 << "," << current->index / 1024 << " dist: " << current->dist << " score: " << current->score << endl;
		current = current->prev;
	}
}	



double MapTraverser::astar(int start, int end) {
        vector<Node *> open;
	getNode(start)->score = heuristic(start, end);
	getNode(start)->dist = 0;
	getNode(start)->visited = true;
	open.push_back(getNode(start));
	Node* current;
	Node* neighbor;
	CompareNode compare;
	double neighborDist;
	double neighborScore;
	map<Node *, double>::iterator iter;  
	bool fix_heap = false;
	while (!open.empty()){
		pop_heap(open.begin(), open.end(), compare);	
		current = open.back();	
		open.pop_back();
		for(iter = current->neighbors.begin(); iter != current->neighbors.end(); iter++){
			neighbor = iter->first;
				
			neighborDist = iter->second + current->dist;
			if(neighbor->index == end){
				neighbor->prev = current;
				//outputpath(neighbor);	
				return neighborDist;}	
			neighborScore = neighborDist + heuristic(neighbor->index, end);		
			if(neighborScore < neighbor->score ){
				neighbor->score = neighborScore;
				neighbor->dist = neighborDist;
				neighbor->prev = current;
				if (!neighbor->visited){	
					open.push_back(neighbor);	
					push_heap(open.begin(), open.end(), compare);	
					neighbor->visited = true;
				}else {
					fix_heap = true;
				}

			}
			
		
		}
		if(fix_heap){
			make_heap(open.begin(), open.end(), compare);
			fix_heap = false;
		}	
	
	}




}
