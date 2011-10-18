/*
 * scene.hpp
 *
 *  Created on: Oct 17, 2011
 *      Author: cgibson
 */

#ifndef SCENE_HPP_
#define SCENE_HPP_

class Scene {
public:
	Scene() {}
	~Scene() {}

	virtual bool intersect(Ray const & ray, Intersection *intersect) = 0;
};

#endif /* SCENE_HPP_ */
