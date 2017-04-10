#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "Color.h"
#include "Vector.h"
#include "Types.h"
#include "Volume.h"

using namespace lux;

class Light:public Volume<float>
{
	public:
		Light (Color S, Vector p, Volume<float>& v, float ds) : source_color(S), position(p), volume(v), delta_s(ds) {}
		~Light () {}
		float eval(const Vector& x);
		Color getColor() {return source_color;}
		float gets() {return delta_s;}
	private:
		Color source_color;
		Vector position;
		Volume<float>& volume;
		float delta_s;
};

#endif
