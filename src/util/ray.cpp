/*
 * Ray.cpp
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#include "util/ray.hpp"

#define T_MAX_DEFAULT 9999999.f
#define T_MIN_DEFAULT 0.00001f

using namespace util;

Ray::Ray(vec3 start, vec3 direction):
	p(start),
	w(direction),
	tMin(T_MIN_DEFAULT),
	tMax(T_MAX_DEFAULT)
{

}

string
Ray::str() const
{
	std::stringstream ss;
	ss << "[ray]\t\tp: <" << p.x << "," << p.y << "," << p.z << "> " << std::endl;
	ss << "     \t\tw: <" << w.x << "," << w.y << "," << w.z << ">";
	ss << std::endl;
	return ss.str();
}
