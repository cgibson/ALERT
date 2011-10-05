extern "C"
{
    #include <lua.h>
}

#include <iostream>
#include <stdio.h>
#include <luabind/luabind.hpp>

using namespace std;

class NumberPrinter {
public:
	NumberPrinter(int number) :
	m_number(number) {}
 
	void print() {
		cout << m_number << endl;
	}
 
private:
	int m_number;
};
 
int main() {
	// Create a new lua state
	lua_State *myLuaState = lua_open();
 
	// Connect LuaBind to this lua state
	luabind::open(myLuaState);
 
	// Export our class with LuaBind
	luabind::module(myLuaState) [
		luabind::class_<NumberPrinter>("NumberPrinter")
			.def(luabind::constructor<int>())
			.def("print", &NumberPrinter::print)
	];
 
	// Now use this class in a lua script
	luaL_dostring(
		myLuaState,
		"Print2000 = NumberPrinter(2000)\n"
		"Print2000:print()\n"
	);
 
	lua_close(myLuaState);
}
