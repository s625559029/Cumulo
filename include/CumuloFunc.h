#include <openvdb/openvdb.h>
#include "Draw.h"
#include "vdb_ObjReader.h"
#include "Pyroclastic.h"
#include "VAdvect.h"
#include "VNoise.h"
#include "IdentityVector.h"
#include "Warp.h"

void WriteVectorGrid(int start, int end, string output_path)
{
    AABB bbox(Vector(-1.5,-1.5,-1.5), Vector(1.5,1.5,1.5));
    float min_delta = bbox.bounds[1].X() - bbox.bounds[0].X();

    float delta_t = 0.1;

    Noise_t parms;
    parms.frequency = 5;
    parms.amplitude = 1;
    FractalSum<PerlinNoiseGustavson> FSPN;
    FSPN.setParameters(parms);
    VNoise vnoise(FSPN);

    VAdvect * vAdvect;

    IdentityVector iVector;
    Vec3fGrid::Ptr G, grid;
    Volume<Vector> * X;

    Stamp stamper;

    char grid_name[1024];
    char file_name[1024];

    for(int i=start;i<end;i++)
    {
        if(i==0)
        {
            vAdvect = new VAdvect(iVector, vnoise, delta_t);
            G = Vec3fGrid::create(Vec3s(0,0,0));
            stamper.vector_stamping(G, *vAdvect, 0.005 * min_delta, bbox);

        } else
        {
            //Read G into X
            sprintf(file_name, "%s/Grids/grid_Cumulo_%d.vdb", output_path.c_str(), i-1);
            openvdb::io::File fileR(file_name);

            fileR.open();

            openvdb::GridBase::Ptr base;
            sprintf(grid_name, "grid_Cumulo_%d", i-1);
            base = fileR.readGrid(grid_name);

            fileR.close();

            grid = openvdb::gridPtrCast<Vec3fGrid>(base);

            X = new Gridded_Vector(grid);
            vAdvect = new VAdvect(*X, vnoise, delta_t);
            G = Vec3fGrid::create(Vec3f(0,0,0));
            stamper.vector_stamping(G, *vAdvect, 0.007 * min_delta, bbox);

            grid->clear();
            base->clear();
        }

        //Write G into disk
        G->setGridClass(openvdb::GRID_LEVEL_SET);
        sprintf(grid_name, "grid_Cumulo_%d", i);
        G->setName(grid_name);
        sprintf(file_name, "%s/Grids/grid_Cumulo_%d.vdb", output_path.c_str(), i);
        openvdb::io::File file(file_name);

        openvdb::GridPtrVec grids;
        grids.push_back(G);

        file.write(grids);
        file.close();

        grids.pop_back();

        G->clear();
    }
}

void drawCumulo(int start, int end, string output_path, string type)
{
    openvdb::initialize();

    //Bunny route
    string file_route = "/home/ysun3/8190/hw4/models/cleanbunny.obj";

    //Vector for bunny
    vector <Vec3s> vdb_points;
    vector <Vec3I> vdb_triangles;

    //Read bunny
    vdb_ObjReader vdb_reader(file_route, vdb_points, vdb_triangles);
    vdb_reader.read_Obj();

    Stamp stamper;

    char grid_name[1024];
    char file_name[1024];

    //AABB for bunny
    float min_x, min_y, min_z, max_x, max_y, max_z;
    min_x = 1000;
    min_y = 1000;
    min_z = 1000;
    max_x = -1000;
    max_y = -1000;
    max_z = -1000;
    for (std::vector<Vec3s>::iterator iter = vdb_points.begin() ; iter != vdb_points.end(); ++iter)
    {
        if((*iter).x() < min_x) min_x = (*iter).x();
        if((*iter).x() > max_x) max_x = (*iter).x();
        if((*iter).y() < min_y) min_y = (*iter).y();
        if((*iter).y() > max_y) max_y = (*iter).y();
        if((*iter).z() < min_z) min_z = (*iter).z();
        if((*iter).z() > max_z) max_z = (*iter).z();
    }

    AABB bbox(Vector(min_x,min_y,min_z), Vector(max_x,max_y,max_z));

    float delta_x = bbox.bounds[1].X() - bbox.bounds[0].X();
    float delta_y = bbox.bounds[1].Y() - bbox.bounds[0].Y();
    float delta_z = bbox.bounds[1].Z() - bbox.bounds[0].Z();

    float min_delta = min(delta_z, min(delta_x, delta_y));
    //Grid for bunny
    int narrow_band = 80;
    Transform::Ptr vdb_transform = math::Transform::createLinearTransform(0.005);/*math::Transform::createLinearTransform()*/
    FloatGrid::Ptr vdb_grid = openvdb::tools::meshToLevelSet<FloatGrid>(*vdb_transform, vdb_points, vdb_triangles, narrow_band);

    //Gridded for bunny
    VDB_Gridded gridded_bunny(vdb_grid);

    //Create PyroBunny
    Noise_t parms;
    parms.frequency = 5;
    parms.amplitude = 0.1;
    FractalSum<PerlinNoiseGustavson> FSPN;
    FSPN.setParameters(parms);
    Pyroclastic PyroBunny(vdb_grid, gridded_bunny, FSPN);

    Clamp clamp_pb(PyroBunny, 50);

    //Advect the pyrobunny
    sprintf(file_name, "%s/Grids/grid_Cumulo_%d.vdb", output_path.c_str(), 0);
    openvdb::io::File fileR(file_name);

    fileR.open();

    openvdb::GridBase::Ptr base;
    sprintf(grid_name, "grid_Cumulo_%d", 0);
    base = fileR.readGrid(grid_name);

    fileR.close();

    Vec3fGrid::Ptr v3grid = openvdb::gridPtrCast<Vec3fGrid>(base);
    Gridded_Vector gridded_v3(v3grid);
    Warp warp_pb(clamp_pb, gridded_v3);

    FloatGrid::Ptr pBunny_grid = FloatGrid::create(0);
    stamper.density_stamping(pBunny_grid, warp_pb, 0.007 * min_delta, bbox);
    Gridded gridded_pb(pBunny_grid);

    //End of pyrobunny



    VolumeColor co_pBunny(gridded_pb,Color(1,1,1,1));

    float l_grid_t = 0.015 * min_delta;     //should use 0.02 * min_delta
    float l_delta_s = l_grid_t / 2.0864;   //for test use 0.03 * min_delta

    //Create lights
    Light light1(Color(5, 5, 5, 1), Vector(0,5,0), gridded_pb, l_delta_s);
    FloatGrid::Ptr light1_grid = FloatGrid::create(0);
    stamper.light_stamping(light1_grid, light1, gridded_pb, l_grid_t, bbox); //0.007
    Gridded_Light gridded_Light1(light1_grid, light1.getColor(), K);

    Light light2(Color(5, 5, 5, 1), Vector(0,-5,0), gridded_pb, l_delta_s);
    FloatGrid::Ptr light2_grid = FloatGrid::create(0);
    stamper.light_stamping(light2_grid, light2, gridded_pb, l_grid_t, bbox);// 0.007
    Gridded_Light gridded_Light2(light2_grid, light2.getColor(), K);

    Light light3(Color(5, 5, 5, 1), Vector(0,0,-5), gridded_pb, l_delta_s);
    FloatGrid::Ptr light3_grid = FloatGrid::create(0);
    stamper.light_stamping(light3_grid, light3, gridded_pb, l_grid_t, bbox);  // 0.007
    Gridded_Light gridded_Light3(light3_grid, light3.getColor(), K);

    vector<Gridded_Light> lights;
    lights.push_back(gridded_Light1);
    lights.push_back(gridded_Light2);
    lights.push_back(gridded_Light3);
    LightSet lightSet(lights);

    //Draw volume
    Draw(0, co_pBunny, gridded_pb, lightSet, bbox, output_path, type);

}