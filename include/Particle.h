//
// Created by ysun3 on 3/11/17.
//

#ifndef WEDGES_PARTICLE_H
#define WEDGES_PARTICLE_H

#include "Noise.h"

using namespace lux;

class Particle
{
    public:
        Particle(Vector p, float ps, float c, float o, float d) : P(p), pscale(ps), clump(c), opacity(o), dscale(d) {}
        ~Particle() {}

        Vector P;
        float pscale;
        float clump;
        float opacity;
        float dscale;
};

#endif //WEDGES_PARTICLE_H
