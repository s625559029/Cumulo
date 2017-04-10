#ifndef __AABB_H__
#define __AABB_H__

#include "Vector.h"
#include "Camera.h"

class AABB
{
	public:
		AABB() {}
		AABB(const Vector& min, const Vector& max) 
		{
			bounds[0] = min;
			bounds[1] = max;
		}
		~AABB() {}

		void translate(const Vector P)
		{
			bounds[0] += P;
			bounds[1] += P;
		}

		bool intersect(const Vector c0, const Vector nl, float snear, float sfar)
		{
			float tmin, tmax, tymin, tymax, tzmin, tzmax;
			if(nl.X() >= 0)
			{
				tmin = (bounds[0].X() - c0.X()) / nl.X();
				tmax = (bounds[1].X() - c0.X()) / nl.X();
			}		
			else
			{
				tmin = (bounds[1].X() - c0.X()) / nl.X();
				tmax = (bounds[0].X() - c0.X()) / nl.X();
			}
			if(nl.Y() >= 0)
			{
				tymin = (bounds[0].Y() - c0.Y()) / nl.Y();
				tymax = (bounds[1].Y() - c0.Y()) / nl.Y();
			}
			else
			{
				tymin = (bounds[1].Y() - c0.Y()) / nl.Y();
				tymax = (bounds[0].Y() - c0.Y()) / nl.Y();
			}
			if((tmin > tymax) || (tymin > tmax)) return false;
			if(tymin > tmin) tmin = tymin;
			if(tymax < tmax) tmax = tymax;
			if(nl.Z() >= 0)
			{
				tzmin = (bounds[0].Z() - c0.Z()) / nl.Z();
				tzmax = (bounds[1].Z() - c0.Z()) / nl.Z();
			}
			else
			{
				tzmin = (bounds[1].Z() - c0.Z()) / nl.Z();
				tzmax = (bounds[0].Z() - c0.Z()) / nl.Z();
			}
			if((tmin > tzmax) || (tzmin > tmax)) return false;
			if(tzmin > tmin) tmin = tzmin;
			if(tzmax < tmax) tmax = tzmax;
			return ((tmin < sfar) && (tmax > snear));
		}

		void intersectPoint(float& Smin, float& Smax, Camera camera, Vector np)
		{
			float min_x, min_y, min_z, max_x, max_y, max_z;
			float x0, x1, y0, y1, z0, z1;
			if(np.X() == 0)
			{
				min_x = camera.nearPlane();
				max_x = camera.farPlane();
			}
			else {
				x0 = (bounds[0].X() - camera.eye().X()) / np.X();
				x1 = (bounds[1].X() - camera.eye().X()) / np.X();
			}
			if(np.Y() == 0)
			{
				min_y = camera.nearPlane();
				max_y = camera.farPlane();
			}
			else {
				y0 = (bounds[0].Y() - camera.eye().Y()) / np.Y();
				y1 = (bounds[1].Y() - camera.eye().Y()) / np.Y();
			}
			if(np.Z() == 0)
			{
				min_z = camera.nearPlane();
				max_z = camera.farPlane();
			}
			else {
				z0 = (bounds[0].Z() - camera.eye().Z()) / np.Z();
				z1 = (bounds[1].Z() - camera.eye().Z()) / np.Z();
			}

			if(x0 < x1){min_x = x0; max_x = x1;}
			else {min_x = x1; max_x = x0;}
			if(y0 < y1){min_y = y0; max_y = y1;}
			else {min_y = y1; max_y = y0;}
			if(z0 < z1){min_z = z0; max_z = z1;}
			else {min_z = z1; max_z = z0;}
			Smin = max(min_z, max(min_x, min_y));
			Smax = min(max_z, min(max_x, max_y));
		}

		Vector bounds[2];
};

#endif

