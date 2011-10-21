/*
 * simpleRenderer.cpp
 *
 *  Created on: Oct 20, 2011
 *      Author: cgibson
 */

#include "render/simpleRenderer.hpp"

SimpleRenderer::SimpleRenderer() {

}

SimpleRenderer::~SimpleRenderer() {

}

Spectrum
SimpleRenderer::Li(const Scene *scene, const util::Ray & ray)
{
	return Spectrum(1,0,1,1);
}

Spectrum
SimpleRenderer::Transmittance(const Scene *scene, const util::Ray & ray)
{
	return Spectrum(1,0,1,1);
}
