#ifndef 	__FACE_H__
#define		__FACE_H__

#include "Point.h"

class Face
{
	public:
		Face (Point p11, Point p22, Point p33):p1(p11), p2(p22), p3(p33) {}
		~Face () {}
		
		Point p1, p2, p3;
};

#endif
