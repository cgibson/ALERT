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

extern "C"
{
    #include <lua.h>

}

//#include "lua.hpp"

#include <luabind/luabind.hpp>

using core::Node;
using geom::Sphere;
using util::Ray;

namespace lua{

namespace state{

		extern lua_State*	getGlobalLuaState();
		extern lua_State*	createLocalLuaState();
		extern void 		loadLuaScript(lua_State *state, string script);
		extern void 		setGlobal(string resourceName, void *resource);
		extern void*		getGlobal(string resourceName);
}

namespace bindings{
namespace helper{

		extern void 		printNode(Node const &);
		extern void 		printRay(Ray const &);
		extern void 		printSphere(Sphere const &);

}
}

}

#endif /* HELPER_HPP_ */
