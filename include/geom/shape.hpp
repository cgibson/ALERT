/*
 * geometry.hpp
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include <stdio.h>

#include "types.hpp"

#include "core/node.hpp"
#include "util/ray.hpp"

using core::Node;

namespace geom {

	class Shape : public Node{
	public:
		Shape( vec3 const & loc );
		virtual ~Shape();

		virtual float intersect(util::Ray const & ray) const { printf("ERROR: unimplemented"); exit(UNIMPLEMENTED_FUNC); }
		virtual vec3 getNormal(vec3 const & p) const { return vec3(0,1,0); }

		virtual string str() const { return "[geometry node]"; }
	};

}

#endif /* SHAPE_HPP_ */
