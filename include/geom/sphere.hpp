/*
 * sphere.hpp
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include <string>

#include "types.hpp"
#include "geom/geometry.hpp"

using std::string;

class Sphere : public GeometryNode{

public:
	Sphere(glm::vec3 const & center, float radius);

	float intersect(Ray const & ray){ return -1; };
	string str();

	float radius;

};

#endif /* SPHERE_HPP_ */
