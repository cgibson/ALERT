/*
 * ProcTexture.hpp
 *
 *  Created on: Oct 10, 2011
 *      Author: cgibson
 */

#ifndef PROCTEXTURE_HPP_
#define PROCTEXTURE_HPP_

#include "lua/helper.hpp"
#include "types.hpp"
#include "texture/texture.hpp"

namespace texture{

class ProceduralTexture : public Texture {

public:
	ProceduralTexture(int width, int height);
	virtual ~ProceduralTexture();
	virtual void setScript(string luaScript);
	virtual Spectrum uvAt(UvCoord);

private:
	string script;
	lua_State *state;
};

}

#endif /* PROCTEXTURE_HPP_ */
