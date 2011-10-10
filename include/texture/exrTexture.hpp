/*
 * exrTexture.hpp
 *
 *  Created on: Oct 9, 2011
 *      Author: cgibson
 */

#ifndef EXRTEXTURE_HPP_
#define EXRTEXTURE_HPP_

#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <ImfRgbaFile.h>
#include <ImfRgba.h>
#include <ImfArray.h>
#include <ImathBox.h>

#include <string>

#include "types.hpp"

#include "texture/texture.hpp"

using std::string;

using Imf::Rgba;
using Imf::RgbaOutputFile;
using Imf::RgbaInputFile;
using Imf::Array2D;
using Imath::Box2i;

namespace texture {

	extern void writeRgba (const char fileName[],
				const Rgba *pixels,
				int width,
				int height);

	extern void readRgba1 (const char fileName[],
				Array2D<Rgba> &pixels,
				int &width,
				int &height);

	class ExrTexture : public Texture {
	public:
		ExrTexture(int width, int height);
		~ExrTexture();

		void read(string const & filename);
		void write(string const & filename);
		Spectrum & operator() (int index);
		Spectrum uvAt(UvCoord coord){ return Spectrum(1);}

	private:
		Spectrum *data;
	};

}

#endif /* EXRTEXTURE_HPP_ */
