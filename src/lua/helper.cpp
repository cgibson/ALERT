#include "lua/helper.hpp"

#include "lua/bindings.hpp"

#include <iostream>

namespace lua{

namespace state{

	static lua_State *luaState = NULL;

	void initializeGlobalLuaState()
	{
		luaState = lua_open();
		luabind::open(luaState);
		lua::bindings::bindClasses(luaState);
		//int ret = luaJIT_setmode(luaState, 0, LUAJIT_MODE_ALLFUNC);
	}

	lua_State *createLocalLuaState()
	{
		lua_State *lstate = lua_open();
		luabind::open(lstate);
		lua::bindings::bindClasses(lstate);

		return lstate;
	}

	void loadLuaScript(lua_State *state, string script)
	{
		luaL_dostring(state, script.c_str());
	}

	lua_State *getGlobalLuaState()
	{
		if (luaState == NULL) {
			initializeGlobalLuaState();
		}
		return luaState;
	}

	void setGlobal(string resourceName, void *resource)
	{
		luabind::globals(luaState)[resourceName] = resource;
	}

	void *getGlobal(string resourceName)
	{
		return luabind::globals(luaState)[resourceName];
	}

}


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
