/*
 * texture.hpp
 *
 *  Created on: Oct 9, 2011
 *      Author: cgibson
 */

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include "types.hpp"

namespace texture{

	class Texture {
	public:
		Texture(int width, int height);
		virtual ~Texture();
		virtual glm::vec4 uvAt(UvCoord) = 0;

	protected:
		int width, height;
	};

}

#endif /* TEXTURE_HPP_ */
