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

#include "node.hpp"
#include "util/ray.hpp"

class GeometryNode : public Node{
public:
	GeometryNode( vec3 loc );
	virtual ~GeometryNode();

	virtual float intersect(Ray const & ray){ printf("ERROR: unimplemented"); exit(UNIMPLEMENTED_FUNC); };
	virtual vec3 getNormal(vec3 const & p){ return vec3(0,1,0); }
};

#endif /* GEOMETRY_HPP_ */
