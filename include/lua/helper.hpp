/*
 * helper.hpp
 *
 *  Created on: Oct 8, 2011
 *      Author: cgibson
 */

#ifndef HELPER_HPP_
#define HELPER_HPP_

#include "core/node.hpp"
#include "geom/sphere.hpp"
#include "util/ray.hpp"

using core::Node;
using geom::Sphere;
using util::Ray;

namespace lua{
namespace bindings{
namespace helper{

	extern void printNode(Node const &);
	extern void printRay(Ray const &);
	extern void printSphere(Sphere const &);

}
}
}

#endif /* HELPER_HPP_ */
