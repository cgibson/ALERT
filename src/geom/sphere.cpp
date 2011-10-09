/*
 * test.cpp
 *
 *  Created on: Oct 1, 2011
 *      Author: cgibson
 */

#include <stdio.h>

#include "geom/sphere.hpp"

#include <iostream>
#include <string>
#include <sstream>

using geom::Sphere;

Sphere::Sphere(vec3 const & center, float radius):
	radius(radius),
	GeometryNode(center)
{

}

string
Sphere::str() const
{
	std::stringstream ss;
	ss << "[sphere]\tloc: <" << loc.x << "," << loc.y << "," << loc.z << ">" << std::endl;
	ss << "        \tradius: (" << radius << ")";
	ss << std::endl;
	return ss.str();
}
