/*
 * simpleRenderer.hpp
 *
 *  Created on: Oct 20, 2011
 *      Author: cgibson
 */

#ifndef SIMPLERENDERER_HPP_
#define SIMPLERENDERER_HPP_

#include "render/renderer.hpp"

class SimpleRenderer : public Renderer {

	SimpleRenderer();
	virtual ~SimpleRenderer();

	Spectrum Transmittance(const Scene *scene, const util::Ray & ray);
	Spectrum Li(const Scene *scene, const util::Ray & ray);

};

#endif /* SIMPLERENDERER_HPP_ */
