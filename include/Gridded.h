#ifndef __GRIDDED_H__
#define __GRIDDED_H__

#include <openvdb/tools/Interpolation.h>

#include "Types.h"
#include "Volume.h"
#include "Vector.h"

using namespace lux;
using namespace openvdb;

//Class girdded for distance
class Gridded:public Volume<float>
{
  public:	
    Gridded(FloatGrid::Ptr g):grid(g) { cout << "gridded volume..." << endl;}
	~Gridded(){}

    const float eval(const Vector& P) const;

  private:
    FloatGrid::Ptr grid;
};

//Class girdded for vdb
class VDB_Gridded:public Volume<float>
{
  public:	
    VDB_Gridded(FloatGrid::Ptr g):grid(g) { cout << "gridded volume..." << endl;}
	~VDB_Gridded(){}

    const float eval(const Vector& P) const;

  private:
    FloatGrid::Ptr grid;
};

//Class gridded for color
class Gridded_Color:public Volume<Color>
{
	public:
		Gridded_Color(Vec4fGrid::Ptr g, float k) : grid(g), K(k) { cout << "Gridded color..." << endl;}
		~Gridded_Color(){}
		
		const Color eval(const Vector& P) const;
		
	private:
		Vec4fGrid::Ptr grid;
		float K;
};

//Class gridded for Vector
class Gridded_Vector:public Volume<Vector>
{
public:
	Gridded_Vector(Vec3fGrid::Ptr g) : grid(g) { cout << "Gridded vector..." << endl;}
	~Gridded_Vector(){}

	const Vector eval(const Vector& P) const;

private:
	Vec3fGrid::Ptr grid;
};

class Gridded_Light:public Volume<Color>
{
	public:
		Gridded_Light(FloatGrid::Ptr g, Color s, float k) : grid(g), S(s), K(k) { cout << "Gridded light..." << endl;}
		~Gridded_Light() {}
		
		const Color eval(const Vector& P) const;
		
	private:
		FloatGrid::Ptr grid;
		Color S;
		float K;
};

#endif
