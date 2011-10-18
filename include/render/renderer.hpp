/*
 * renderer.hpp
 *
 *  Created on: Oct 17, 2011
 *      Author: cgibson
 */

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

class Renderer {
public:
	Renderer() {}
	virtual ~Renderer() {}

	virtual Spectrum Transmittance(const Scene *scene, const Ray & ray) = 0;
	virtual Spectrum Li(const Scene *scene, const Ray & ray) = 0;
};

#endif /* RENDERER_HPP_ */
