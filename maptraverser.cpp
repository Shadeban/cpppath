#include "maptraverser.hpp"
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
		iter->second->dist = infDouble;
		iter->second->visited = false;
		iter->second->closed = false;
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
			a->dist = infDouble;
			a->index = index;
			a->visited = false;	
			a->closed = false;	
			a->prev = NULL;			
			nodes->insert(pair<int,Node*>(index, a));	
		}else if (!create) {
			return NULL;
		}

	} 
	
	
	
		
	return nodes->at(index);


}

double MapTraverser::djikstra(int start, int end) {
	NodeHeap open;
	getNode(start)->score = 0;
	open.push(getNode(start));
	Node* current;
	Node* neighbor;
	double neighborDist;
	map<Node *, double>::iterator iter;  
	while (!open.empty()){
		current = open.top();
		open.pop();	
		if(current->index == end){
				return current->score;}	
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
			if(neighborDist < neighbor->score ){
				neighbor->score = neighborDist;
				open.push(neighbor);	
			}
			
		
		}
	
	}




}
double MapTraverser::heuristic(int start, int end){
	int dx = abs(start % (mapParser->getX()) - end % (mapParser->getX()));
	int dy = abs(start / mapParser->getX() - end / mapParser->getX());
	return dx + dy  + (diagCoef * min(dx,dy));	


}

void MapTraverser::outputpath(Node* end){
	Node* current = end;
	while(current->prev != NULL){
		cout << current->index % mapParser->getX() << "," << current->index / mapParser->getX() << " dist: " << current->dist << " score: " << current->score << endl;
		current = current->prev;
	}
}	



double MapTraverser::astar(int start, int end) {
	
	NodeHeap open;
	
	Node* current = getNode(start);
	current->score = heuristic(start, end);
	current->dist = 0;
	current->visited = true;
	current->handle = open.push(current);
	Node* neighbor;
	double neighborDist;
	double neighborScore;
	map<Node *, double>::iterator iter; 
	while (!open.empty()){
		current = open.top();	
		open.pop();
		if(current->index == end){
			return current->dist;}	
		current->closed = true;
		for(iter = current->neighbors.begin(); iter != current->neighbors.end(); iter++){
			neighbor = iter->first;
				
			neighborDist = iter->second + current->dist;
			//cout << neighborDist << endl;	
		//
		//	neighborScore = 
			if(neighbor->closed){
				continue;
			}	
			if(neighborDist < neighbor->dist ){
				neighbor->score = neighborDist + heuristic(neighbor->index, end);		
				neighbor->dist = neighborDist;
				neighbor->prev = current;
				if (!neighbor->visited){	
					neighbor->handle = open.push(neighbor);	
					neighbor->visited = true;
				} else {
					open.update(neighbor->handle);	
				}

			}
			
		
		}
	
	}




}
