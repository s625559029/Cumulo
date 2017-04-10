#ifndef 	__POINT_H__
#define		__POINT_H__

class Point
{
	public:
		Point (float xx, float yy, float zz):x(xx), y(yy), z(zz) {}
		~Point () {}
	
		float x, y, z;
};

#endif
