/*
 * ProcTexture.cpp
 *
 *  Created on: Oct 10, 2011
 *      Author: cgibson
 */

#include "texture/procTexture.hpp"

namespace texture{

	ProceduralTexture::ProceduralTexture(int width, int height):
					Texture(width, height)
	{
		script = "outColor = Spectrum(uv.s, uv.t, 1.0, 1.0)";
		state = lua::state::getGlobalLuaState();
	}

	ProceduralTexture::~ProceduralTexture()
	{

	}

	void
	ProceduralTexture::setScript(string luaScript)
	{
		script = luaScript;
	}

	Spectrum
	ProceduralTexture::uvAt(UvCoord uv)
	{
		luabind::globals(state)["uv"] = &uv;
		luaL_dostring(state, script.c_str());
		Spectrum out = luabind::object_cast<Spectrum>(luabind::globals(state)["outColor"]);

		return out;
	}

}
