#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bitset>
using namespace std;

class MapParser {
	public:
		MapParser(const char * filename);
		void output () const;
		void parse();	
	private:
		int x;
		int y;
		const char* filename;
		char* map;
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
		
		unsigned char neighbors(int k) const;	


};

