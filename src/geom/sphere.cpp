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


Sphere::Sphere(float radius, vec3 const & center):
	radius(radius),
	GeometryNode(center)
{

}
