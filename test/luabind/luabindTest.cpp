/*
 * luabindTest.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: cgibson
 */

extern "C"
{
    #include <lua.h>
}

#include <iostream>
#include <luabind/luabind.hpp>

void greet()
{
    std::cout << "hello world!\n";
}

extern "C" int init(lua_State* L)
{
    using namespace luabind;

    open(L);

    module(L)
    [
        def("greet", &greet)
    ];

    return 0;
}
