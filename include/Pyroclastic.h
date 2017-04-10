//
// Created by ysun3 on 4/9/17.
//

#ifndef WEDGES_PYROCLASTIC_H
#define WEDGES_PYROCLASTIC_H

#include "Vector.h"
#include "Volume.h"
#include "PerlinNoise.h"
#include "Noise.h"
#include "Types.h"

using namespace lux;

class Pyroclastic : public Volume<float>
{
public:
    Pyroclastic(FloatGrid::Ptr g, Volume& sdf, FractalSum<PerlinNoiseGustavson>& fspn) : grid(g), SDF(sdf), FSPN(fspn){}
    ~Pyroclastic(){}

    const float eval(const Vector& P) const;

private:
    FloatGrid::Ptr grid;
    Volume& SDF;
    FractalSum<PerlinNoiseGustavson>& FSPN;

};


#endif //WEDGES_PYROCLASTIC_H
