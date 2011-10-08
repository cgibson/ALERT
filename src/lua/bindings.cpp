/*
 * bindings.cpp
 *
 *  Created on: Oct 7, 2011
 *      Author: cgibson
 */

#include "lua/bindings.hpp"


namespace lua{
namespace bindings{

	void bindClasses(lua_State *myLuaState)
	{
		// Export our class with LuaBind
		luabind::module(myLuaState) [

			// Vec3 Binding
			luabind::class_<glm::vec3>("vec3")
				.def(luabind::constructor<float, float, float>())
				.def_readwrite("x", &glm::vec3::x)
				.def_readwrite("y", &glm::vec3::y)
				.def_readwrite("z", &glm::vec3::z),

			// Ray Binding
			luabind::class_<Ray>("ray")
				.def(luabind::constructor<glm::vec3, glm::vec3>())
				.def_readwrite("str", &Ray::str)
				.def_readwrite("p", &Ray::p)
				.def_readwrite("w", &Ray::w)
				.def_readwrite("tMin", &Ray::tMin)
				.def_readwrite("tMax", &Ray::tMax),

			// Sphere Binding
		   luabind::class_<Sphere>("sphere")
				.def(luabind::constructor<glm::vec3, float>())
				.def_readwrite("radius", &Sphere::radius)
				.def("str", &Sphere::str)
		];
	}

}
}
