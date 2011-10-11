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

	glm::vec2 *locations = new glm::vec2[4];
	float *intensity = new float[4];
	float radius = 64;

	locations[0] = glm::vec2(128,128);
	intensity[0] = 1.0;

	locations[1] = glm::vec2(384,128);
	intensity[1] = 2.0;

	locations[2] = glm::vec2(128,384);
	intensity[2] = 3.0;

	locations[3] = glm::vec2(384,384);
	intensity[3] = 4.0;

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
