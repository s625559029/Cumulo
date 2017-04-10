
#ifndef 	__VDB_OBJREADER_H__
#define		__VDB_OBJREADER_H__

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include "Types.h"
#include "Face.h"

using namespace std;

class vdb_ObjReader
{
	public:
		vdb_ObjReader(string r, vector <Vec3s>& p, vector <Vec3I>& t): route(r), points(p), triangles(t), vn(0), vnum(0), fnum(0) {}
		~vdb_ObjReader() {}
		void read_Obj();
		
	private:
		string route, s, str, s1;
		vector <Vec3s>& points;
		vector <Vec3I>& triangles;
		float s2, s3, s4;
		ifstream file;
		int vn, vnum, fnum;
};

#endif
