//
// Created by ysun3 on 4/9/17.
//

#include "../include/Pyroclastic.h"

const float Pyroclastic::eval(const Vector &P) const
{
    float value;
    float sdf_result = SDF.eval(P);
    FloatGrid::Accessor acc = grid->getAccessor();
    Transform::Ptr transform = grid->transformPtr();

    Vec3f pos(P.X(), P.Y(), P.Z());
    Coord ijk(transform->worldToIndexNodeCentered(pos));
    if (acc.isValueOn(ijk)) {
        UniformScaleMap::Ptr map = transform->map<UniformScaleMap>();
        openvdb::math::CPT_RANGE<UniformScaleMap, openvdb::math::CD_2ND> cptROp;

        Vec3d cpt_result = cptROp.result(*map, acc, ijk);
        Vector CPT(cpt_result.x(), cpt_result.y(), cpt_result.z());
        float f = FSPN.getAmplitude() * FSPN.eval(CPT);
        value = sdf_result + pow(abs(f), FSPN.getGamma());

    } else
        value = sdf_result;

    return value;
}