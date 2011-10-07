#include <boost/test/unit_test.hpp>

extern "C"
{
    #include <lua.h>
}

#include <iostream>
#include <stdio.h>
#include <luabind/luabind.hpp>

#include "geom/sphere.hpp"

using namespace std;

/******************************************************************************/
/* LuaBind Scene Class Binding Tests                                          */
/******************************************************************************/
BOOST_AUTO_TEST_SUITE(LuaSceneClassBinding)
BOOST_AUTO_TEST_CASE(luaTestSceneClass)
{
	printf("\nTESTING LUA SCENE CLASS BINDING\n");
	// Create a new lua state
	lua_State *myLuaState = lua_open();

	// Connect LuaBind to this lua state
	luabind::open(myLuaState);

	// Export our class with LuaBind
	luabind::module(myLuaState) [
		luabind::class_<glm::vec3>("vec3")
			.def(luabind::constructor<float, float, float>())
			.def_readwrite("x", &glm::vec3::x)
			.def_readwrite("y", &glm::vec3::y)
			.def_readwrite("z", &glm::vec3::z),
	   luabind::class_<Sphere>("sphere")
			.def(luabind::constructor<glm::vec3, float>())
			.def_readwrite("radius", &Sphere::radius)
			.def("str", &Sphere::str)
	];

	// Now use this class in a lua script
	luaL_dostring(
		myLuaState,
		"v = vec3(1.0, 2.0, 3.0)\n"
		"s = sphere(v, 5.0)\n"
		"s:str()\n"
		"s:test()"
	);

	lua_close(myLuaState);
}

BOOST_AUTO_TEST_SUITE_END()
