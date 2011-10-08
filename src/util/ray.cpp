/*
 * Ray.cpp
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#include "util/ray.hpp"

#define T_MAX_DEFAULT 9999999.f
#define T_MIN_DEFAULT 0.00001f

Ray::Ray(vec3 start, vec3 direction):
	p(start),
	w(direction),
	tMin(T_MIN_DEFAULT),
	tMax(T_MAX_DEFAULT)
{

}

string
Ray::str()
{
	//printf("sphere: loc:<%.2f, %.2f, %.2f> rad:%.2f", loc.x, loc.y, loc.z, radius);
	std::stringstream ss;
	ss << "ray: p:<" << p.x << "," << p.y << "," << p.z << "> ";
	ss << "w:<" << w.x << "," << w.y << "," << w.z << ">";
	ss << std::endl;
	printf("%s", ss.str().c_str());
	return ss.str();
}
