/*
 * plane.cpp
 *
 *  Created on: Oct 1, 2011
 *      Author: cgibson
 */

#include <stdio.h>

#include "geom/plane.hpp"

#include <iostream>
#include <string>
#include <sstream>

using geom::Plane;

Plane::Plane(glm::vec3 const & center, glm::vec3 const & normal):
	normal(normal),
	GeometryNode(center)
{

}

string
Plane::str() const
{
	//printf("sphere: loc:<%.2f, %.2f, %.2f> rad:%.2f", loc.x, loc.y, loc.z, radius);
	std::stringstream ss;
	ss << "[plane]\tloc: <" << loc.x << "," << loc.y << "," << loc.z << ">" << std::endl;
	ss << "       \tnormal: <" << normal.x << "," << normal.y << "," << normal.z << ">";
	ss << std::endl;
	//printf("%s", ss.str().c_str());
	return ss.str();
}
