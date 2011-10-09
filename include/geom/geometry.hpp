/*
 * geometry.hpp
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

#include <stdio.h>

#include "types.hpp"

#include "core/node.hpp"
#include "util/ray.hpp"

using core::Node;

namespace geom {

	class GeometryNode : public Node{
	public:
		GeometryNode( vec3 const & loc );
		virtual ~GeometryNode();

		virtual float intersect(util::Ray const & ray) const { printf("ERROR: unimplemented"); exit(UNIMPLEMENTED_FUNC); }
		virtual vec3 getNormal(vec3 const & p) const { return vec3(0,1,0); }

		virtual string str() const { return "[geometry node]"; }
	};

}

#endif /* GEOMETRY_HPP_ */
