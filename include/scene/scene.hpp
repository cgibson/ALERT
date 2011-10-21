/*
 * scene.hpp
 *
 *  Created on: Oct 17, 2011
 *      Author: cgibson
 */

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "util/ray.hpp"

class Scene {
public:
	Scene() {}
	~Scene() {}

	virtual bool intersect(util::Ray const & ray, Intersect *intersect) = 0;
};

#endif /* SCENE_HPP_ */
