/*
 * test.cpp
 *
 *  Created on: Oct 1, 2011
 *      Author: cgibson
 */

#include <stdio.h>

#include "geom/sphere.hpp"

#define GLM_FORCE_INLINE
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <sstream>

Sphere::Sphere(vec3 const & center, float radius):
	radius(radius),
	GeometryNode(center)
{

}

string
Sphere::str()
{
	//printf("sphere: loc:<%.2f, %.2f, %.2f> rad:%.2f", loc.x, loc.y, loc.z, radius);
	std::stringstream ss;
	ss << "sphere: loc:<" << loc.x << "," << loc.y << "," << loc.z << "> radius:(" << radius << ")";
	ss << std::endl;
	printf("%s", ss.str().c_str());
	return ss.str();
}
