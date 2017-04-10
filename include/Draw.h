/*
 * Draw.h
 *
 *  Created on: Mar 8, 2017
 *      Author: ysun3
 */

#ifndef DRAW_H_
#define DRAW_H_

#include "Configuration.h"
#include "Volume.h"
#include "Color.h"
#include "Image.h"
#include "AABB.h"
#include "OIIOFiles.h"
#include "omp.h"

using namespace lux;

//Draw function-----------------------------------------------------------
void Draw(int k, Volume<Color>& color, Volume<float>& volume, Volume<Color>& light, AABB bbox, string output_path, string type)
{
	 int j;
     Image image;
     image.reset(width,height);
     Renderer renderer;

     Camera camera;
	 camera.setNearPlane(near);
	 camera.setFarPlane(far);

    double start_time = omp_get_wtime();
    cout << "Rendering..." << endl;
    camera.setEyeViewUp(c0, c, up0);

    # pragma omp parallel for collapse(2)
    for(j=0;j<height-1;j++)
    {
        for(int i=0;i<width-1;i++)
        {
            float u = i/float(width-1);
            float v = j/float(height-1);
			Vector np = camera.view(u,v);
			Color L(0,0,0,0);
			if(bbox.intersect(camera.eye(), np, camera.nearPlane(), camera.farPlane())) {
                float Smin, Smax;
                bbox.intersectPoint(Smin, Smax, camera, np);
                L = renderer.render(color, camera.eye(), np, Smin, Smax, volume, K, delta_s,
                                    light);
            }
			image.value(i,j,0)=L.X();
			image.value(i,j,1)=L.Y();
			image.value(i,j,2)=L.Z();
			image.value(i,j,3)=L.W();
		}
    }

    double exe_time = omp_get_wtime() - start_time;
    std::cout << "Elapsed Time: " << exe_time << "s" << std::endl;
    char file_name[1024];
    //sprintf(file_name, "%s/ysun3_%s_hw2.%04d.exr", output_path.c_str(), type.c_str(), k);
    sprintf(file_name, "%s/ysun3_hw4.%04d.exr", output_path.c_str(), k);
    writeOIIOImage(file_name,image);
    cout<<"output "<<k<<" complete"<<endl;
}

#endif /* DRAW_H_ */
