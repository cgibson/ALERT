/*
 * sphere.hpp
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "types.hpp"
#include "geom/shape.hpp"

namespace geom {

class Sphere : public Shape{

	public:
		Sphere(glm::vec3 const & center, float radius);

		virtual float intersect(util::Ray const & ray) const { return -1; };
		virtual vec3 getNormal(vec3 const & p) const { return vec3(0,1,0); }
		virtual string str() const;

		float radius;

	};

}

#endif /* SPHERE_HPP_ */
