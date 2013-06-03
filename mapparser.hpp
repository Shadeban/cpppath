#ifndef _map_parser_h
#define _map_parser_h
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bitset>
#include <vector>
using namespace std;

class MapParser {
	public:
		MapParser(const char * filename);
		~MapParser();	
		void output () const;
		void parse();	
		unsigned char* map;
		int mapSize() const;
		void allNeighbors(int index, vector<int> * buffer, vector<double> * dists);
	private:
		int test;	
		int x;
		int y;
		const char* filename;
		static const unsigned char upleft = 1;
		static const unsigned char up = 1 << 1;
		static const unsigned char upright = 1 << 2;
		static const unsigned char left = 1 << 3;
		static const unsigned char right = 1 << 4;
		static const unsigned char downleft = 1 << 5;
		static const unsigned char down = 1 << 6;
		static const unsigned char downright = 1 << 7;
		static const unsigned char diags = upleft + upright + downleft + downright;
		static const unsigned char orthogs = up + down + left + right;
		static const unsigned char leftside = upleft + left + downleft;
		static const unsigned char rightside = upright + right + downright;
		static const unsigned char upside = upleft + up + upright;
		static const unsigned char downside = downleft + down + downright;
		static const unsigned char alldirs[8];
		void createTraversalMap(char * parsedmap);
		int findNeighborIndex(int index, unsigned char dir) const;
		unsigned char neighbors(int k, char * map) const;
		bool canPass(char start, char end) const;
		bool canMove(int index, unsigned char dir, char* map) const;



};

static const double sqrtTwo = 1.41421356237309504880168872420969807857; // sqrt(2)
#endif
