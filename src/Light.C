#include "Light.h"

using namespace std;

float Light::eval(const Vector& x)
{
	float L = 0;
		Vector cur_x = x;
		Vector xs = position;
		Vector nl = (xs - x) / ((xs - x).magnitude());
		float S = 0;
		float q = (x - xs).magnitude();
		while (S <= q) {
			cur_x += delta_s * nl;
			L += delta_s * volume.eval(cur_x);
			S += delta_s;
		}
	return L;
}
