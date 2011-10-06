#include <boost/test/unit_test.hpp>

extern "C"
{
    #include <lua.h>
}

#include <iostream>
#include <stdio.h>
#include <luabind/luabind.hpp>

using namespace std;

void print_hello(int number) {
	cout << "hello world " << number << endl;
}

/******************************************************************************/
/* LuaBind Class Binding Tests                                                */
/******************************************************************************/

BOOST_AUTO_TEST_SUITE(LuaFuncBinding)
BOOST_AUTO_TEST_CASE(luaTestCPPFunc)
{
	printf("\nTESTING LUA FUNCTION BINDING\n");
	// Create a new lua state
	lua_State *myLuaState = lua_open();

	// Connect LuaBind to this lua state
	luabind::open(myLuaState);

	// Add our function to the state's global scope
	luabind::module(myLuaState) [
		luabind::def("print_hello", print_hello)
	];

	// Now call our function in a lua script
	luaL_dostring(
		myLuaState,
		"print_hello(123)\n"
	);

	lua_close(myLuaState);
}
BOOST_AUTO_TEST_SUITE_END()
