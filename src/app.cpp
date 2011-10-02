/*
 * app.cpp
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#include <stdio.h>

#include "geom/sphere.hpp"

#include "sanitize_glm.hpp"

int main()
{

	Sphere s(0.5, vec3(0));

	printf("Hello, sphere.\n");

	return 0;
}
