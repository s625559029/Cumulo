//
// Created by ysun3 on 4/9/17.
//

#ifndef WEDGES_WARP_H
#define WEDGES_WARP_H

#include "Volume.h"
#include "Types.h"

using namespace lux;

class Warp:public Volume<float>{
public:
    Warp(Volume<float>& f, Volume<Vector> &x) : F(f), X(x) {}
    ~Warp() {}

    const float eval(const Vector& P) const{
        return F.eval(X.eval(P));
    }

private:
    Volume<float> & F;
    Volume<Vector> & X;
};

#endif //WEDGES_WARP_H
