#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE LuaBind

#include <boost/test/unit_test.hpp>

extern "C"
{
    #include <lua.h>
}

#include <iostream>
#include <stdio.h>
#include <luabind/luabind.hpp>

// TESTS
#include "luaFuncTests.hpp"
#include "luaClassTests.hpp"
#include "luaSceneClassTests.hpp"
