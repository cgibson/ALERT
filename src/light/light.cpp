/*
 * test.cpp
 *
 *  Created on: Oct 1, 2011
 *      Author: cgibson
 */

#include <stdio.h>

#include "light/light.hpp"

#include <iostream>
#include <string>
#include <sstream>

using light::Light;

Light::Light(vec3 const & center, Spectrum const & color):
	color(color),
	Node(center)
{

}

string
Light::str() const
{
	std::stringstream ss;
	ss << "[light]\tloc: <" << loc.x << "," << loc.y << "," << loc.z << ">" << std::endl;
	ss << "       \tcolor: <" << color.r << "," << color.g << "," << color.b << "," << color.a << ">" << std::endl;
	ss << std::endl;
	//printf("%s", ss.str().c_str());
	return ss.str();
}
