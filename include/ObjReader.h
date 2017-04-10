
#ifndef 	__OBJREADER_H__
#define		__OBJREADER_H__

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>

#include "Face.h"

using namespace std;

class ObjReader
{
	public:
		ObjReader(string r, vector <Point>& ps, vector <Face>& fs): route(r), points(ps), faces(fs), vn(0), vnum(0), fnum(0) {}
		~ObjReader() {}
		void read_Obj();
		
	private:
		string route, s, str, s1;
		vector <Point>& points;
		vector <Face>& faces;
		float s2, s3, s4;
		ifstream file;
		int vn, vnum, fnum;
};

#endif
