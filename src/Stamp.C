#include "Stamp.h"
#include "omp.h"

void Stamp::density_stamping(FloatGrid::Ptr grid, Volume<float>& volume, float t, AABB& bbox)
{
        cout << "stamping density..." << endl;
        Transform::Ptr transform = grid->transformPtr();
        transform = Transform::createLinearTransform(t);
        grid->setTransform(transform);
        FloatGrid::Accessor accessor = grid->getAccessor();

        Vec3s min_pos(bbox.bounds[0].X(), bbox.bounds[0].Y(), bbox.bounds[0].Z());
        Vec3s max_pos(bbox.bounds[1].X(), bbox.bounds[1].Y(), bbox.bounds[1].Z());
        Coord min_coord = transform->worldToIndexNodeCentered(min_pos);
        Coord max_coord = transform->worldToIndexNodeCentered(max_pos);

        Int32 min_i = min_coord.x();
        Int32 min_j = min_coord.y();
        Int32 min_k = min_coord.z();
        Int32 max_i = max_coord.x();
        Int32 max_j = max_coord.y();
        Int32 max_k = max_coord.z();

        float new_min_i = max_i;
        float new_min_j = max_j;
        float new_min_k = max_k;
        float new_max_i = min_i;
        float new_max_j = min_j;
        float new_max_k = min_k;

        double start_time = omp_get_wtime();
        # pragma omp parallel for collapse(3)
        for (Int32 i = min_i; i <= max_i; i++) {
            for (Int32 j = min_j; j <= max_j; j++) {
                for (Int32 k = min_k; k <= max_k; k++) {
                    Coord ijk(i, j, k);
                    Vec3s vec3s_X = transform->indexToWorld(ijk);
                    Vector vector_X(vec3s_X.x(), vec3s_X.y(), vec3s_X.z());

                    if (volume.eval(vector_X) > 0) {
                    #pragma omp critical
                        {
                            //Refresh the bbox
                            if (i < new_min_i) new_min_i = i;
                            if (i > new_max_i) new_max_i = i;
                            if (j < new_min_j) new_min_j = j;
                            if (j > new_max_j) new_max_j = j;
                            if (k < new_min_k) new_min_k = k;
                            if (k > new_max_k) new_max_k = k;

                            accessor.setValue(ijk, volume.eval(vector_X));
                        }
                    }
                }
            }
        }

        //Refresh the bbox
        Coord min(new_min_i, new_min_j, new_min_k);
        Coord max(new_max_i, new_max_j, new_max_k);
        Vec3s new_min_pos = transform -> indexToWorld(min);
        Vec3s new_max_pos = transform -> indexToWorld(max);
        bbox.bounds[0] = Vector(new_min_pos.x(),new_min_pos.y(),new_min_pos.z());
        bbox.bounds[1] = Vector(new_max_pos.x(),new_max_pos.y(),new_max_pos.z());
        double exe_time = omp_get_wtime() - start_time;
        std::cout << "Elapsed Time: " << exe_time << "s" << std::endl;
}

void Stamp::color_stamping(Vec4fGrid::Ptr grid, Volume<Color>& volume, float t, AABB bbox)
{
        cout << "stamping color..." << endl;
        Transform::Ptr transform = grid->transformPtr();
        transform = Transform::createLinearTransform(t);
        grid->setTransform(transform);
        Vec4fGrid::Accessor accessor = grid->getAccessor();
        Vec3s min_pos(bbox.bounds[0].X(), bbox.bounds[0].Y(), bbox.bounds[0].Z());
        Vec3s max_pos(bbox.bounds[1].X(), bbox.bounds[1].Y(), bbox.bounds[1].Z());
        Coord min_coord = transform->worldToIndexNodeCentered(min_pos);
        Coord max_coord = transform->worldToIndexNodeCentered(max_pos);

        Int32 min_i = min_coord.x();
        Int32 min_j = min_coord.y();
        Int32 min_k = min_coord.z();
        Int32 max_i = max_coord.x();
        Int32 max_j = max_coord.y();
        Int32 max_k = max_coord.z();

        double start_time = omp_get_wtime();
        # pragma omp parallel for collapse(3)
        for (Int32 i = min_i; i <= max_i; i++) {
            for (Int32 j = min_j; j <= max_j; j++) {
                for (Int32 k = min_k; k <= max_k; k++) {
                    Coord ijk(i, j, k);
                    Vec3s vec3s_X = transform->indexToWorld(ijk);
                    Vector vector_X(vec3s_X.x(), vec3s_X.y(), vec3s_X.z());
                    Color color_c = volume.eval(vector_X);
                    if (color_c != Color(0, 0, 0, 0)) {
                        Vec4s vec4s_c(color_c.X(), color_c.Y(), color_c.Z(), color_c.W());
                        #pragma omp critical
                        {
                        accessor.setValue(ijk, vec4s_c);
                        }
                    }
                }
            }
        }
        double exe_time = omp_get_wtime() - start_time;
        std::cout << "Elapsed Time: " << exe_time << "s" << std::endl;
}

void Stamp::vector_stamping(Vec3fGrid::Ptr grid, Volume<Vector>& volume, float t, AABB bbox)
{
    cout << "stamping vector..." << endl;
    Transform::Ptr transform = grid->transformPtr();
    transform = Transform::createLinearTransform(t);
    grid->setTransform(transform);
    Vec3fGrid::Accessor accessor = grid->getAccessor();
    Vec3s min_pos(bbox.bounds[0].X(), bbox.bounds[0].Y(), bbox.bounds[0].Z());
    Vec3s max_pos(bbox.bounds[1].X(), bbox.bounds[1].Y(), bbox.bounds[1].Z());
    Coord min_coord = transform->worldToIndexNodeCentered(min_pos);
    Coord max_coord = transform->worldToIndexNodeCentered(max_pos);

    Int32 min_i = min_coord.x();
    Int32 min_j = min_coord.y();
    Int32 min_k = min_coord.z();
    Int32 max_i = max_coord.x();
    Int32 max_j = max_coord.y();
    Int32 max_k = max_coord.z();

    double start_time = omp_get_wtime();
    # pragma omp parallel for collapse(3)
    for (Int32 i = min_i; i <= max_i; i++) {
        for (Int32 j = min_j; j <= max_j; j++) {
            for (Int32 k = min_k; k <= max_k; k++) {
                Coord ijk(i, j, k);
                Vec3s vec3s_X = transform->indexToWorld(ijk);
                Vector vector_X(vec3s_X.x(), vec3s_X.y(), vec3s_X.z());
                Vector vector_v = volume.eval(vector_X);
                if (vector_v != Vector(0, 0, 0)) {
                    Vec3s vec3s_v(vector_v.X(), vector_v.Y(), vector_v.Z());
                    #pragma omp critical
                    {
                        accessor.setValue(ijk, vec3s_v);
                    }
                }
            }
        }
    }
    double exe_time = omp_get_wtime() - start_time;
    std::cout << "Elapsed Time: " << exe_time << "s" << std::endl;
}

void Stamp::light_stamping(FloatGrid::Ptr grid, Light light, Volume<float>& volume, float t, AABB bbox)
{
        cout << "stamping light..." << endl;
        Transform::Ptr transform = grid->transformPtr();
        transform = Transform::createLinearTransform(t);
        grid->setTransform(transform);
        FloatGrid::Accessor accessor = grid->getAccessor();

        Vec3s min_pos(bbox.bounds[0].X(), bbox.bounds[0].Y(), bbox.bounds[0].Z());
        Vec3s max_pos(bbox.bounds[1].X(), bbox.bounds[1].Y(), bbox.bounds[1].Z());
        Coord min_coord = transform->worldToIndexNodeCentered(min_pos);
        Coord max_coord = transform->worldToIndexNodeCentered(max_pos);

        Int32 min_i = min_coord.x();
        Int32 min_j = min_coord.y();
        Int32 min_k = min_coord.z();
        Int32 max_i = max_coord.x();
        Int32 max_j = max_coord.y();
        Int32 max_k = max_coord.z();

        double start_time = omp_get_wtime();
        # pragma omp parallel for collapse(3)
        for (Int32 i = min_i; i <= max_i; i++) {
            for (Int32 j = min_j; j <= max_j; j++) {
                for (Int32 k = min_k; k <= max_k; k++) {
                    Coord ijk(i, j, k);
                    Vec3s vec3s_X = transform->indexToWorld(ijk);
                    Vector vector_X(vec3s_X.x(), vec3s_X.y(), vec3s_X.z());
                    if (volume.eval(vector_X) > 0) {
                        float temp = 0;
                            temp = light.eval(vector_X);

                        if (temp > 0) {
                            #pragma omp critical
                            {
                                accessor.setValue(ijk, temp);
                            }
                        }
                    }
                    else{
                        Coord up(i+1, j, k);
                        Coord down(i-1, j, k);
                        Coord left(i, j+1, k);
                        Coord right(i, j-1, k);
                        Coord front(i, j, k+1);
                        Coord back(i, j, k-1);

                        Vec3s vec3s_up = transform->indexToWorld(up);
                        Vec3s vec3s_down = transform->indexToWorld(down);
                        Vec3s vec3s_left = transform->indexToWorld(left);
                        Vec3s vec3s_right = transform->indexToWorld(right);
                        Vec3s vec3s_front = transform->indexToWorld(front);
                        Vec3s vec3s_back = transform->indexToWorld(back);

                        Vector vector_up(vec3s_up.x(), vec3s_up.y(), vec3s_up.z());
                        Vector vector_down(vec3s_down.x(), vec3s_down.y(), vec3s_down.z());
                        Vector vector_left(vec3s_left.x(), vec3s_left.y(), vec3s_left.z());
                        Vector vector_right(vec3s_right.x(), vec3s_right.y(), vec3s_right.z());
                        Vector vector_front(vec3s_front.x(), vec3s_front.y(), vec3s_front.z());
                        Vector vector_back(vec3s_back.x(), vec3s_back.y(), vec3s_back.z());

                        bool hasValue = false;
                        if(volume.eval(vector_up) != 0) hasValue = true;
                        else if(volume.eval(vector_down) != 0) hasValue = true;
                        else if(volume.eval(vector_left) != 0) hasValue = true;
                        else if(volume.eval(vector_right) != 0) hasValue = true;
                        else if(volume.eval(vector_front) != 0) hasValue = true;
                        else if(volume.eval(vector_back) != 0) hasValue = true;

                        float temp = 0;

                        if(hasValue == true)
                            temp = light.eval(vector_X);

                        if (temp > 0) {
                            #pragma omp critical
                            {
                                accessor.setValue(ijk, temp);
                            }
                        }
                    }
                }
            }
        }
        double exe_time = omp_get_wtime() - start_time;
        std::cout << "Elapsed Time: " << exe_time << "s" << std::endl;
}

void Stamp::noise_stamping(FloatGrid::Ptr grid, Noise& noise, float pscale, float gamma, float t, AABB& bbox)
{
    cout << "stamping noise..." << endl;
    Transform::Ptr transform = grid -> transformPtr();
    transform = Transform::createLinearTransform(t);
    grid -> setTransform(transform);

    Vec3s min_pos (bbox.bounds[0].X(), bbox.bounds[0].Y(), bbox.bounds[0].Z());
    Vec3s max_pos (bbox.bounds[1].X(), bbox.bounds[1].Y(), bbox.bounds[1].Z());
    Coord min_coord = transform -> worldToIndexNodeCentered(min_pos);
    Coord max_coord = transform -> worldToIndexNodeCentered(max_pos);

    Int32 min_i = min_coord.x();
    Int32 min_j = min_coord.y();
    Int32 min_k = min_coord.z();
    Int32 max_i = max_coord.x();
    Int32 max_j = max_coord.y();
    Int32 max_k = max_coord.z();

    float new_min_i = max_i;
    float new_min_j = max_j;
    float new_min_k = max_k;
    float new_max_i = min_i;
    float new_max_j = min_j;
    float new_max_k = min_k;

    double start_time = omp_get_wtime();
    # pragma omp parallel for
    for(Int32 i = min_i; i <= max_i; i++)
    {
        FloatGrid::Accessor accessor = grid -> getAccessor();
        for(Int32 j = min_j; j <= max_j; j++)
        {
            for(Int32 k = min_k; k <= max_k; k++)
            {
                float value = 0;
                Coord ijk(i, j, k);
                Vec3s vec3s_X = transform -> indexToWorld(ijk);
                Vector vector_X(vec3s_X.x(), vec3s_X.y(), vec3s_X.z());

                Vector P(0,0,0);	//Center of the sphere
                float fadefactor = pow((1 - (vector_X - P).magnitude() / pscale), gamma);
                if(fadefactor > 0) value = noise.eval(vector_X);
                if(value >= 0) {
                    #pragma omp critical
                    {
                        //Refresh the bbox
                        if (i < new_min_i) new_min_i = i;
                        if (i > new_max_i) new_max_i = i;
                        if (j < new_min_j) new_min_j = j;
                        if (j > new_max_j) new_max_j = j;
                        if (k < new_min_k) new_min_k = k;
                        if (k > new_max_k) new_max_k = k;

                        accessor.setValue(ijk, value * fadefactor);
                    }
                }
            }
        }
    }
    //Refresh the bbox
    Coord min(new_min_i, new_min_j, new_min_k);
    Coord max(new_max_i, new_max_j, new_max_k);
    Vec3s new_min_pos = transform -> indexToWorld(min);
    Vec3s new_max_pos = transform -> indexToWorld(max);
    bbox.bounds[0] = Vector(new_min_pos.x(),new_min_pos.y(),new_min_pos.z());
    bbox.bounds[1] = Vector(new_max_pos.x(),new_max_pos.y(),new_max_pos.z());
    double exe_time = omp_get_wtime() - start_time;
    std::cout << "Elapsed Time: " << exe_time << "s" << std::endl;
}

void Stamp::wisps_stamping(FloatGrid::Ptr grid, int num, Particle& particle, Noise_t& parms1, Noise_t& parms2, float t, AABB& bbox)
{
    cout << "stamping wisps..." << endl;

    float coor = 0.5;

    Vector guide_p = particle.P;
    float pscale = particle.pscale;
    float clump = particle.clump;

    FractalSum<PerlinNoiseGustavson> FSPN1;
    FSPN1.setParameters(parms1);
    FractalSum<PerlinNoiseGustavson> FSPN2;
    FSPN2.setParameters(parms2);

    float scale1 = pow(1.0+parms1.roughness, parms1.octaves-1.0);
    float scale2 = pow(1.0+parms2.roughness, parms2.octaves-1.0);

    float dscale = particle.dscale;
    float opacity = particle.opacity;
    float delta_x = 1;

    Transform::Ptr transform = grid -> transformPtr();
    transform = Transform::createLinearTransform(t);
    grid -> setTransform(transform);

    FloatGrid::Accessor accessor = grid -> getAccessor();

    float min_box_i = bbox.bounds[1].X();
    float min_box_j = bbox.bounds[1].Y();
    float min_box_k = bbox.bounds[1].Z();
    float max_box_i = bbox.bounds[0].X();
    float max_box_j = bbox.bounds[0].Y();
    float max_box_k = bbox.bounds[0].Z();

    double start_time = omp_get_wtime();
    # pragma omp parallel for
    for(int i=0;i<num;i++)
    {
        //Create a coorelated random walk point
        float x = drand48() * 2 - 1;
        float y = drand48() * 2 - 1;
        float z = drand48() * 2 - 1;

        //Move to a surface of sphere
        float radius = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        float xs = x / radius;
        float ys = y / radius;
        float zs = z / radius;

        //Move off the sphere
        Vector xyz(x, y, z);
        float R = pow(fabs(FSPN1.eval(xyz)*2/scale1), clump);
        xs *= R;
        ys *= R;
        zs *= R;

        //Transform to world space
        Vector xyzs(xs, ys, zs);
        Vector xw = xyzs * pscale + guide_p;

        //Displace
        Vector p_xyzs(xs + delta_x, ys + delta_x, zs + delta_x);
        Vector m_xyzs(xs - delta_x, ys - delta_x, zs - delta_x);
        float dx = FSPN2.eval(xyzs)*2/scale2;
        float dy = FSPN2.eval(p_xyzs)*2/scale2;
        float dz = FSPN2.eval(m_xyzs)*2/scale2;
        Vector dxyz(dx, dy, dz);
        Vector D = dxyz * dscale;
        xw += D;

        //refresh bbox

        if(xw.X() < min_box_i) min_box_i = xw.X();
        if(xw.Y() < min_box_j) min_box_j = xw.Y();
        if(xw.Z() < min_box_k) min_box_k = xw.Z();
        if(xw.X() > max_box_i) max_box_i = xw.X();
        if(xw.Y() > max_box_j) max_box_j = xw.Y();
        if(xw.Z() > max_box_k) max_box_k = xw.Z();

        //Burn to grid
        Vec3s _xw(xw.X(), xw.Y(), xw.Z());
        Coord ijk = transform -> worldToIndexNodeCentered(_xw);
        int min_i = ijk.x();
        int min_j = ijk.y();
        int min_k = ijk.z();
        Coord i1_jk(min_i+1, min_j, min_k);
        Coord i_j1_k(min_i, min_j+1, min_k);
        Coord i_j_k1(min_i, min_j, min_k+1);
        Coord i1_j1_k(min_i+1, min_j+1, min_k);
        Coord i_j1_k1(min_i, min_j+1, min_k+1);
        Coord i1_j_k1(min_i+1, min_j, min_k+1);
        Coord i1_j1_k1(min_i+1, min_j+1, min_k+1);

        float w_x = xw.X() / t - floor(xw.X() / t);
        float w_y = xw.Y() / t - floor(xw.Y() / t);
        float w_z = xw.Z() / t - floor(xw.Z() / t);

        float value;
        #pragma omp critical
        {
            accessor.setValue(ijk, accessor.getValue(ijk) + opacity * (1 - w_x) * (1 - w_y) * (1 - w_z));
            accessor.setValue(ijk, accessor.getValue(i1_jk) + opacity * w_x * (1 - w_y) * (1 - w_z));
            accessor.setValue(ijk, accessor.getValue(i_j1_k) + opacity * (1 - w_x) * w_y * (1 - w_z));
            accessor.setValue(ijk, accessor.getValue(i_j_k1) + opacity * (1 - w_x) * (1 - w_y) * w_z);
            accessor.setValue(ijk, accessor.getValue(i1_j1_k) + opacity * w_x * w_y * (1 - w_z));
            accessor.setValue(ijk, accessor.getValue(i_j1_k1) + opacity * (1 - w_x) * w_y * w_z);
            accessor.setValue(ijk, accessor.getValue(i1_j_k1) + opacity * w_x * (1 - w_y) * w_z);
            accessor.setValue(ijk, accessor.getValue(i1_j1_k1) + opacity * w_x * w_y * w_z);
        }
    }
    bbox.bounds[0] = Vector(min_box_i,min_box_j,min_box_k);
    bbox.bounds[1] = Vector(max_box_i,max_box_j,max_box_k);
    double exe_time = omp_get_wtime() - start_time;
    std::cout << "Elapsed Time: " << exe_time << "s" << std::endl;
}