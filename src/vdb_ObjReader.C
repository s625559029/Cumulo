#include "vdb_ObjReader.h"

void vdb_ObjReader::read_Obj()
{
	//Open obj file.
	file.open(route.c_str());
	
	while(getline(file, s))
	{
		
		istringstream iss(s);
		iss >> s1 >> s2 >> s3 >> s4;
		
		if(s[0] == 'v')
		{
			if(s[1] == 'n')
			{
				vn ++;
				//Store normal
			}
			else
			{
				vnum ++;
				Vec3s p(s2, s3, s4);
				points.push_back(p);
				//Store vertice
			}
		}
		else if(s[0] == 'f')
		{
			fnum ++;
			Vec3I face(s2 - 1, s3 - 1, s4 - 1);
			triangles.push_back(face);
			//Store face
		}
	}
	cout << "Number of vertices:" << vnum << endl;
	cout << "Number of normals:" << vn << endl;
	cout << "Number of faces:" << fnum << endl;
	
}
