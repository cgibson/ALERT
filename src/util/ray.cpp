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
