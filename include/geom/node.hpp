/*
 * Node.h
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#ifndef NODE_HPP_
#define NODE_HPP_

#include "types.hpp"

class Node {
public:
	Node( vec3 loc );
	virtual ~Node();

	vec3 loc;
};

#endif /* NODE_HPP_ */
