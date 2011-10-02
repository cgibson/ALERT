/*
 * sphere.hpp
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "sanitize_glm.hpp"

class Sphere {

public:
	Sphere(double radius, vec3 const & center);

	double radius;
	vec3 center;

};

#endif /* SPHERE_HPP_ */
