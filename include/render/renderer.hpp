/*
 * renderer.hpp
 *
 *  Created on: Oct 17, 2011
 *      Author: cgibson
 */

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "types.hpp"
#include "camera/camera.hpp"
#include "scene/scene.hpp"
#include "util/ray.hpp"

class Renderer {
public:
	Renderer() {}
	virtual ~Renderer() {}

	virtual Spectrum Transmittance(const Scene *scene, const util::Ray & ray) = 0;
	virtual Spectrum Li(const Scene *scene, const util::Ray & ray) = 0;

private:
	Camera *camera;
};

#endif /* RENDERER_HPP_ */
