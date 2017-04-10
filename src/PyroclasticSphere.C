//
// Created by ysun3 on 3/9/17.
//

#include "../include/PyroclasticSphere.h"

const float PyroclasticSphere::eval(const Vector &P) const
{
    float value;
    Vector x = P;
    float d = (x - x0).magnitude();     //Distance from x to x0
    Vector n = x.unitvector();        //Vector n from x to x0
    float f = FSPN.getAmplitude() * FSPN.eval(r * n);             //FSPN
    float sphere = r - x.magnitude();
    value = sphere + pow(abs(f), FSPN.getGamma());

    return value;
}