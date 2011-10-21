/*
 * camera.cpp
 *
 *  Created on: Oct 17, 2011
 *      Author: cgibson
 */

#include "camera/camera.hpp"

Camera::Camera()
{

}

Camera::~Camera()
{
	delete film;
}
