/*
 * sphere.hpp
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "types.hpp"

#include "geom/geometry.hpp"

class Sphere : public GeometryNode{

public:
	Sphere(float radius, glm::vec3 const & center);

	float intersect(Ray const & ray){ return -1; };

	float radius;

};

#endif /* SPHERE_HPP_ */
