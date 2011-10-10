/*
 * exrtexture.cpp
 *
 *  Created on: Oct 9, 2011
 *      Author: cgibson
 */

#include "texture/exrTexture.hpp"

namespace texture {

	// Code gathered from OpenEXR documentation at:
	// http://www.openexr.com/ReadingAndWritingImageFiles.pdf
	void
	writeRgba (const char fileName[],
		const Rgba *pixels,
		int width,
		int height)
	{
		RgbaOutputFile file (fileName, width, height, Imf::WRITE_RGBA); // 1
		file.setFrameBuffer (pixels, 1, width); // 2
		file.writePixels (height); // 3
	}

	// Code gathered from OpenEXR documentation at:
	// http://www.openexr.com/ReadingAndWritingImageFiles.pdf
	void
	readRgba1 (const char fileName[],
		Array2D<Rgba> &pixels,
		int &width,
		int &height)
	{
		RgbaInputFile file (fileName);
		Box2i dw = file.dataWindow();
		width = dw.max.x - dw.min.x + 1;
		height = dw.max.y - dw.min.y + 1;
		pixels.resizeErase (height, width);
		file.setFrameBuffer (&pixels[0][0] - dw.min.x - dw.min.y * width, 1, width);
		file.readPixels (dw.min.y, dw.max.y);
	}


	ExrTexture::ExrTexture(int width, int height):Texture(width, height)
	{
		data = new Spectrum[width * height];
	}

	ExrTexture::~ExrTexture()
	{
		delete data;
	}

	void
	ExrTexture::read(string const & file)
	{

	}

	void
	ExrTexture::write(string const & file)
	{
		Rgba *dataRgba = new Rgba[width * height];

		for(int i = 0; i < width * height; i++) {
			Spectrum c = data[i];
			dataRgba[i] = Rgba(c.r, c.g, c.b, c.a);
		}
		writeRgba(file.c_str(), dataRgba, width, height);
		delete dataRgba;
	}

	Spectrum &
	ExrTexture::operator() (int index)
	{
		return data[index];
	}

}
