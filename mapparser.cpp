#include "mapparser.h"

MapParser::MapParser(const char* filename) :filename(filename) {
}
MapParser::~MapParser(){
	delete[] map;
}
const unsigned char MapParser::alldirs[] = {upleft, up, upright, left, right, downleft, down, downright};	

void MapParser::output() const{
	ifstream file;
	file.open(filename);
	char c = file.get();	
	while (file.good()) {
		cout << c;
		c = file.get();
	}	
	file.close();

}
int MapParser::mapSize() const {
	return x * y;
}

void MapParser::allNeighbors(int index, vector<int> buffer) {
	for(int i = 0; i < 8; i++){
		if(map[index] & alldirs[i]){
			buffer.push_back(findNeighborIndex(index, alldirs[i]));	
		}
	
	}

}
void MapParser::parse() {
	ifstream file;
	file.open(filename);
	string line;
	x = 0;
	y = 0;
	int i = 0;
	char* tempmap;	
	while (getline(file, line)) {
		i++;
		if(i == 2){
			istringstream heightline (line);
			heightline.ignore(100, ' ');
			heightline >> y;
		} else if (i == 3){
			istringstream widthline (line);
			widthline.ignore(100, ' ');
			widthline >> x;	
			tempmap = new char[x*y];	
			map = new unsigned char[x * y];
		}
		if(i > 4){
			istringstream(line).read(tempmap + (x * (i - 5)), x);
		}

	}

	createTraversalMap(tempmap);
	file.close();
	delete[] tempmap;		

}



void MapParser::createTraversalMap(char * parsedmap){
	for(int i = 0; i < x * y; i++){
		map[i] = neighbors(i, parsedmap);
	}

}

int MapParser::findNeighborIndex(int index, unsigned char dir) const{
	int offset = 0;
	if(dir & upside) {
		offset = offset - x;
	}
	if(dir & downside) {
		offset = offset + x;
	}
	if(dir & leftside) {
		offset--;
	}
	if(dir & rightside) {
		offset++;
	}
	return index + offset;
}
bool MapParser::canPass(char start, char end) const{
	if(end == '.'){
		return true;
	}
	return false;

}
bool MapParser::canMove(int k, unsigned char dir, char * map) const{
	if(canPass(map[k], map[findNeighborIndex(k, dir)])){
		if(dir & orthogs){
			return true;
		}
		bool canMoveVert = false;
		//is a diag, need to check complementary dirs
		if(dir & upside){
			canMoveVert = canMove(k, up, map);		
		} else if (dir & downside){
			canMoveVert = canMove(k, down, map);
		}
		if(canMoveVert){
			if(dir & leftside){
				return canMove(k,left,map);
			}else if (dir & rightside){
				return canMove(k, right, map);
			}	
		}
	}
	return false;
}
unsigned char MapParser::neighbors(int k, char * map) const{
	unsigned char potential_neighbors = ~0;

	//remove neighbors from edges
	if(k % x == 0){
		potential_neighbors = potential_neighbors & ~leftside;
	}else if (k % x == x - 1){
		potential_neighbors = potential_neighbors & ~rightside;
	}
	if(k / x == 0){
		potential_neighbors = potential_neighbors & ~upside;
	}else if (k / x == y - 1){
		potential_neighbors = potential_neighbors & ~downside;
	}
	for(int i = 0; i < 8; i++){
		if(potential_neighbors & alldirs[i] && !canMove(k, alldirs[i], map)){
			potential_neighbors = potential_neighbors & ~alldirs[i];
		}
	}
	return potential_neighbors;



}
