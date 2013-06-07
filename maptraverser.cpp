#include "maptraverser.hpp"
MapTraverser::MapTraverser(MapParser* mapParser) :mapParser(mapParser){
	createNodes();
	unsigned char upleft = mapParser->upleft;
	unsigned char upright = mapParser->upright;
	unsigned char downleft = mapParser->downleft;
	unsigned char downright = mapParser->downright;
	unsigned char up = mapParser->up;
	unsigned char down = mapParser->down;
	unsigned char left = mapParser->left;
	unsigned char right = mapParser->right;
	forceTriggerDirs[up] = new unsigned char[2];
	forceTriggerDirs[up][0] = downleft;
	forceTriggerDirs[up][1] = downright;
		
	forceTriggerDirs[down] = new unsigned char[2];
	forceTriggerDirs[down][0] = upleft;
	forceTriggerDirs[down][1] = upright;
	forceTriggerDirs[left] = new unsigned char[2];
	forceTriggerDirs[left][0] = upright;
	forceTriggerDirs[left][1] = downright;
	forceTriggerDirs[right] = new unsigned char[2];
	forceTriggerDirs[right][0] = upleft;
	forceTriggerDirs[right][1] = downleft;
	
	dirsBetween[upleft][right] = new unsigned char[2];
	dirsBetween[upleft][right][0] = up;
	dirsBetween[upleft][right][1] = upright;
	dirsBetween[upleft][down] = new unsigned char[2];		
	dirsBetween[upleft][down][0] = left;
	dirsBetween[upleft][down][1] = downleft;
	dirsBetween[upright][left] = new unsigned char[2];
	dirsBetween[upright][left][0] = up;
	dirsBetween[upright][left][1] = upleft;
	dirsBetween[upright][down] = new unsigned char[2];		
	dirsBetween[upright][down][0] = right;
	dirsBetween[upright][down][1] = downright;
	dirsBetween[downleft][right] = new unsigned char[2];
	dirsBetween[downleft][right][0] = down;
	dirsBetween[downleft][right][1] = downright;
	dirsBetween[downleft][up] = new unsigned char[2];		
	dirsBetween[downleft][up][0] = left;
	dirsBetween[downleft][up][1] = upleft;
	dirsBetween[downright][left] = new unsigned char[2];
	dirsBetween[downright][left][0] = down;
	dirsBetween[downright][left][1] = downleft;

	dirsBetween[downright][up] = new unsigned char[2];		
	dirsBetween[downright][up][0] = right;
	dirsBetween[downright][up][1] = upright;

	complements[upleft] = new unsigned char[2];
	complements[upleft][0] = up; 
	complements[upleft][1] = left; 
	complements[upright] = new unsigned char[2];
	complements[upright][0] = up; 
	complements[upright][1] = right; 
	complements[downleft] = new unsigned char[2];
	complements[downleft][0] = down; 
	complements[downleft][1] = left; 
	complements[downright] = new unsigned char[2];
	complements[downright][0] = down; 
	complements[downright][1] = right; 
	

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
		iter->second->forced = false;
		iter->second->travelDir = 0;
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
			a->travelDir = 0;
			a->index = index;
			a->visited = false;	
			a->forced = false;
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
double MapTraverser::jps(int start, int end) {
	
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
			unsigned char travelDir = dirTo(current, iter->first);	
			neighbor = jump(current, travelDir, end);
			if(!neighbor){
				continue;
			}		
			//cout << neighborDist << endl;	
		//
		//	neighborScore = 
			if(neighbor->closed){
				continue;
			}	
			if(!neighbor->forced){
				if(current->travelDir > 0){
					if (travelDir & current->travelDir == 0){
						if(current->travelDir & mapParser->diags){
							if(travelDir & complements[current->travelDir][0] == 0 && travelDir & complements[current->travelDir][1] == 0) {continue;}	
						} else {
							continue;
						}
					}
				}

			}	
			neighborDist = heuristic(current->index, neighbor->index) + current->dist;
			
			if(neighborDist < neighbor->dist ){
				neighbor->score = neighborDist + heuristic(neighbor->index, end);		
				neighbor->dist = neighborDist;
				neighbor->prev = current;
				neighbor->travelDir = travelDir;
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

unsigned char MapTraverser::dirTo(Node* start, Node* end){
	for(int i = 0; i < 8; i++){
		if(mapParser->findNeighborIndex(start->index, mapParser->alldirs[i]) == end->index){
			return mapParser->alldirs[i];	
		}
	}
		
}

bool MapTraverser::hasForced(int index, unsigned char direction){
	if(mapParser->diags & direction){return false;} //diags can't jump corners, can't have forced neighbors
	bool forced = false;
	for(int i = 0; i < 2; i++){
		if(mapParser->travel(index, forceTriggerDirs[direction][i]) == -1){
			//potential force
			for(int k = 0; k < 2; k ++){
				int forcedIndex = mapParser->travel(index, dirsBetween[forceTriggerDirs[direction][i]][direction][k]);  
				if(forcedIndex > 0){ getNode(forcedIndex)->forced = true;forced = true; } //forced node exists 
			
			}	
		}
	}	
	return forced;
}


bool MapTraverser::isDiagAndHasOrthogJumps(int index, unsigned char travelDir, int goalIndex){
	if(mapParser->diags & travelDir){
		for(int i = 0; i < 2; i++){	
			if(jump(getNode(index), complements[travelDir][i], goalIndex)){
				return true;
			}
		}	
	}
	return false;

}
Node* MapTraverser::jump(Node * current, unsigned char direction, int goalIndex) {
	int next = mapParser->travel(current->index, direction);
	if(next == -1) return NULL;
	if(next == goalIndex) return getNode(next);
	if(hasForced(next, direction)) return getNode(next);
	if(isDiagAndHasOrthogJumps(next, direction, goalIndex)) return getNode(next);
	return jump(getNode(next), direction, goalIndex);
}
