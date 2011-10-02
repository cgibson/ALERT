/*
 * test.cpp
 *
 *  Created on: Oct 1, 2011
 *      Author: cgibson
 */

#include <stdio.h>

#include "geom/sphere.hpp"

#include "sanitize_glm.hpp"

Sphere::Sphere(double radius, vec3 const & center)
{
	this->radius = radius;
	this->center = center;
}
