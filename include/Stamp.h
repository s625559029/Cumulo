#ifndef __STAMP_H__
#define __STAMP_H__

#include "Types.h"
#include "Volume.h"
#include "Color.h"
#include "Vector.h"
#include "Light.h"
#include "AABB.h"
#include "Noise.h"
#include "PyroclasticSphere.h"
#include "Particle.h"

using namespace lux;
using namespace openvdb;

class Stamp
{
	public:
		Stamp () {}
		~Stamp () {}
		void density_stamping(FloatGrid::Ptr grid, Volume<float>& volume, float t, AABB& bbox);
		void color_stamping(Vec4fGrid::Ptr grid, Volume<Color>& volume, float t, AABB bbox);
		void vector_stamping(Vec3fGrid::Ptr grid, Volume<Vector>& volume, float t, AABB bbox);
		void light_stamping(FloatGrid::Ptr grid, Light light, Volume<float>& volume, float t, AABB bbox);
		void noise_stamping(FloatGrid::Ptr grid, Noise& noise, float pscale, float gamma, float t, AABB& bbox);
		void wisps_stamping(FloatGrid::Ptr grid, int num, Particle& particle, Noise_t& parms1, Noise_t& parms2, float t, AABB& bbox);
};

#endif
