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
		script = "function main (uv)\n"
				 "  return Spectrum(uv.s, uv.t, 1.0, 1.0)\n"
				 "end\n";

		state = lua::state::createLocalLuaState();

		lua::state::loadLuaScript(state, script);
	}

	ProceduralTexture::~ProceduralTexture()
	{
		//free(state);
	}

	void
	ProceduralTexture::setScript(string luaScript)
	{
		script = luaScript;
	}

	Spectrum
	ProceduralTexture::uvAt(UvCoord uv)
	{
		Spectrum out = luabind::call_function<Spectrum>(state, "main", uv);

		return out;
	}

}
