/*
 * exrWrite.cpp
 *
 *  Created on: Oct 8, 2011
 *      Author: cgibson
 */

#include "texture/exrTexture.hpp"
#include "texture/procTexture.hpp"

#include "types.hpp"

using texture::ProceduralTexture;
using texture::ExrTexture;

int main()
{
	int width, height;
	width = height = 512;

	ProceduralTexture procTex = ProceduralTexture(width,height);
	ExrTexture exrTex = ExrTexture(width,height);

	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			UvCoord uv = UvCoord((float)x / width, (float)y / height);

			exrTex(y * width + x) = procTex.uvAt(uv);
		}
	}

	exrTex.write("proc.exr");

	return 0;
}
