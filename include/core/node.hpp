/*
 * Node.h
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#ifndef NODE_HPP_
#define NODE_HPP_

#include "types.hpp"
#include "util/ray.hpp"

namespace core {

	class Node {
	public:
		Node( vec3 const & loc );
		virtual ~Node();
		virtual float intersect( util::Ray const & ray ) const { printf("ERROR: unimplemented"); exit(UNIMPLEMENTED_FUNC); }
		virtual string str() const{ return "[node]"; }
		vec3 loc;
	};

}

#endif /* NODE_HPP_ */
