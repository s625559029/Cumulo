#ifndef __Renderer_H__
#define __Renderer_H__

#include <math.h>
#include <unistd.h>
#include "Vector.h"
#include "LightSet.h"

using namespace std;
using namespace lux;

class Renderer
{
    public:
    Renderer(){}
    ~Renderer(){}

   const Color render(Volume<Color>& cu, const Vector& x0, Vector& np,float nearPlane, float farPlane, Volume<float> &volume, float K,float delta_s, Volume<Color> & light)
   {
      Vector x = x0+np*nearPlane;
      int i = 0;
      float T = 1;
      float delta_T = 0;
      Color L;
      while(i*delta_s<=farPlane-nearPlane && T>0.1)
      {
        x += np*delta_s;
        if(volume.eval(x) != 0)
        {
			delta_T =  exp(-volume.eval(x)*delta_s*K);
			L += ((cu.eval(x)*light.eval(x))/K)*T*(1-delta_T);
			T *= delta_T;
		}
		i++;
      }
      return L;
    }
    
  private:

};

#endif
