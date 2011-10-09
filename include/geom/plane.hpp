/*
 * plane.hpp
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "types.hpp"
#include "geom/geometry.hpp"

namespace geom {

	class Plane : public GeometryNode{

	public:
		Plane(glm::vec3 const & center, glm::vec3 const & normal);

		virtual float intersect(util::Ray const & ray) const { return -1; };
		virtual vec3 getNormal(vec3 const & p) const { return normal; }
		virtual string str() const;

		glm::vec3 normal;

	};

}

#endif /* PLANE_HPP_ */
