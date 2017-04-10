#include "Volume.h"

using namespace lux;

class Sphere:public Volume<float>
{
  public:

    Sphere(float r0):r(r0){}
    ~Sphere(){}

    const float eval(const Vector& P) const {return  r-sqrt(P*P);}

  private:

    int r;	//radius of the sphere
};

