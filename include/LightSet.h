#ifndef __LIGHTSET_H__
#define __LIGHTSET_H__

#include "Light.h"
#include "Gridded.h"

using namespace lux;

class LightSet:public Volume<Color>
{
	public:
		LightSet (vector<Gridded_Light>& ls) : light_set(ls) {cout << "Create light set..." << endl;}
		~LightSet () {}
		const Color eval(const Vector& x) const {
            Color color;
            for(int i=0; i<light_set.size();i++) {
                color += light_set[i].eval(x);
            }
            return color;
        }
	private:
        vector<Gridded_Light>& light_set;
};

#endif
