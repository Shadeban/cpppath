#include "maptraverser.h"
MapTraverser::MapTraverser(MapParser* mapParser) :mapParser(mapParser){
	createNodes();
}
void MapTraverser::createNodes(){
	if(!nodes.empty()){nodes.clear();}	
	for(int i = 0; i < mapParser->mapSize(); i++){
		
		if(mapParser->map[i]){
			shared_ptr<Node> node = getNode(i, true);
			vector<int> neighborIds;
			mapParser->allNeighbors(i, neighborIds);
			
		}	
	}
	cout << nodes.size();
}

shared_ptr<Node> MapTraverser::getNode(int index, bool create = false){

	if(nodes.find(index) == nodes.end() && create){
		shared_ptr<Node> a(new Node);
		a->score = 1.0/0.0;
		a->index = index;
		a->prev = NULL;			
		nodes[index] = a;		
	} else if (!create) {
		return NULL;
	}
	return nodes[index];


}
