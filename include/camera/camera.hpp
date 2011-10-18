/*
 * camera.hpp
 *
 *  Created on: Oct 17, 2011
 *      Author: cgibson
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "film.hpp"

class Camera {
public:
	Camera();
	~Camera();

	Film *film;
};

#endif /* CAMERA_HPP_ */
