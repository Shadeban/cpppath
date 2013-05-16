#include "mapparser.h"

MapParser::MapParser(const char* filename) :filename(filename) {
}

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

void MapParser::parse() {
	ifstream file;
	file.open(filename);
	string line;
	x = 0;
	y = 0;
	int i = 0;
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
			map = new char[x * y];
		}
		if(i <= 4){
			cout << i << " " << x << " " << y << ".  " << line << endl;
		}
		else {
			
			istringstream(line).read(map + (x * (i - 5)), x);
		}
		 
	}
	
	cout << bitset<8>(neighbors(0))  <<endl;
	cout << bitset<8>(neighbors(100))  <<endl;
	cout << bitset<8>(neighbors(x-1))  <<endl;
	cout << bitset<8>(neighbors(x*10))  <<endl;
	cout << bitset<8>(neighbors(x* 10 + 100)) << endl;
	cout << bitset<8>(neighbors(x*10 - 1))  <<endl;
	cout << bitset<8>(neighbors(x*(y-1) ))  <<endl;
	cout << bitset<8>(neighbors(x*y -100))  <<endl;
	cout << bitset<8>(neighbors(x*y -1))  <<endl;
		
	delete[] map;	
	file.close();


}

unsigned char MapParser::neighbors(int k) const{
	unsigned char potential_neighbors = ~0;

	//remove neighbors from edge
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


	return potential_neighbors;



}
