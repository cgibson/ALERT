/*
 * exrWrite.cpp
 *
 *  Created on: Oct 8, 2011
 *      Author: cgibson
 */

#include <ImfRgbaFile.h>
#include <ImfRgba.h>

using Imf::Rgba;
using Imf::RgbaOutputFile;

void
writeRgba1 (const char fileName[],
	const Rgba *pixels,
	int width,
	int height)
{
	RgbaOutputFile file (fileName, width, height, Imf::WRITE_RGBA); // 1
	file.setFrameBuffer (pixels, 1, width); // 2
	file.writePixels (height); // 3
}

int main()
{
	int width; int height;

	width = height = 512;

	Rgba *pixels = new Rgba[width * height];

	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			pixels[y * width + x].r = ((float)x / width);
			pixels[y * width + x].g = ((float)y / height);
			pixels[y * width + x].b = 0.f;
			pixels[y * width + x].a = 1.f;
		}
	}

	writeRgba1("test.exr", pixels, width, height);

	delete pixels;

	return 0;
}
