//
// Created by ysun3 on 4/9/17.
//

#ifndef WEDGES_VNOISE_H
#define WEDGES_VNOISE_H

#include "Volume.h"
#include "Vector.h"
#include "PerlinNoise.h"
#include "Noise.h"

using namespace lux;

class VNoise : public Volume<Vector>{
public:
    VNoise (FractalSum<PerlinNoiseGustavson>& fspn) : FSPN(fspn){}
    ~VNoise () {}

    const Vector eval(const Vector& P) const{
        Vector delta_x(1,0,0);
        Vector delta_y(0,1,0);
        Vector delta_z(0,0,1);
        float nx = FSPN.eval(P+delta_x);
        float ny = FSPN.eval(P+delta_y);
        float nz = FSPN.eval(P+delta_z);
        return Vector(nx,ny,nz);
    }

private:
    FractalSum<PerlinNoiseGustavson>& FSPN;
};

#endif //WEDGES_VNOISE_H
