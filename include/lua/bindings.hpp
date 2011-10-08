/*
 * bindings.hpp
 *
 *  Created on: Oct 7, 2011
 *      Author: cgibson
 */

#ifndef BINDINGS_HPP_
#define BINDINGS_HPP_

extern "C"
{
    #include <lua.h>
}
#include <luabind/luabind.hpp>

#include "geom/sphere.hpp"

namespace lua{
namespace bindings{

	void bindClasses(lua_State *myLuaState);

}
}


#endif /* BINDINGS_HPP_ */
