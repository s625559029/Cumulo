//
// Created by ysun3 on 4/9/17.
//

#ifndef WEDGES_VADVECT_H
#define WEDGES_VADVECT_H

#include "Volume.h"
#include "Vector.h"

using namespace lux;

class VAdvect : public Volume<Vector>{
public:
    VAdvect(Volume<Vector> & vf, Volume<Vector> & vn, float dt) : vector_field(vf), VNoise(vn), delta_t(dt) {}
    ~VAdvect() {}
    const Vector eval(const Vector& P) const{
        Vector result = vector_field.eval(P) - VNoise.eval(P) * delta_t;
        return result;
    }

private:
    Volume<Vector> & vector_field;
    Volume<Vector> & VNoise;
    float delta_t;
};

#endif //WEDGES_VADVECT_H
