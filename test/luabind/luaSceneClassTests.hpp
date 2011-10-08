#include <boost/test/unit_test.hpp>

#include "lua/bindings.hpp"

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
	lua::bindings::bindClasses(myLuaState);

	// Now use this class in a lua script
	luaL_dostring(
		myLuaState,
		"v = vec3(1.0, 2.0, 3.0)\n"
		"s = sphere(v, 5.0)\n"
		"s:str()\n"
		"p = vec3(0,0,0)\n"
		"w = vec3(0,0,-1)\n"
		"r = ray(p, w)\n"
		"r:str()\n"
	);

	lua_close(myLuaState);
}

BOOST_AUTO_TEST_SUITE_END()
