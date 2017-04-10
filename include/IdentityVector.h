//
// Created by ysun3 on 4/9/17.
//

#ifndef WEDGES_IDENTITYVECTOR_H
#define WEDGES_IDENTITYVECTOR_H

#include "Volume.h"
#include "Vector.h"

using namespace lux;

class IdentityVector : public Volume<Vector> {
public:
    IdentityVector() {}
    ~IdentityVector() {}
    const Vector eval(const Vector& P) const{ return P; }
private:
};
#endif //WEDGES_IDENTITYVECTOR_H
