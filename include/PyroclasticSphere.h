//
// Created by ysun3 on 3/9/17.
//

#ifndef WEDGES_PYROCLASTICSPHERE_H
#define WEDGES_PYROCLASTICSPHERE_H

#include "Vector.h"
#include "Volume.h"
#include "PerlinNoise.h"
#include "Noise.h"

using namespace lux;

class PyroclasticSphere : public Volume<float>
{
    public:
        PyroclasticSphere( float r0, FractalSum<PerlinNoiseGustavson>& fspn) : r(r0), FSPN(fspn), x0(Vector(0,0,0)){}
        ~PyroclasticSphere(){}

        const float eval(const Vector& P) const;

    private:
        float r;
        FractalSum<PerlinNoiseGustavson>& FSPN;
        Vector x0;
};


#endif //WEDGES_PYROCLASTICSPHERE_H
