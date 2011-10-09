#include "lua/helper.hpp"

#include <iostream>

namespace lua{
namespace bindings{
namespace helper{

	void printNode(Node const & node)
	{
		std::cout << node.str();
	}

	void printSphere(Sphere const & sphere)
	{
		std::cout << sphere.str();
	}

	void printRay(Ray const & ray)
	{
		std::cout << ray.str();
	}

}
}
}
