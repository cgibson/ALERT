/*
 * app.cpp
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#include <stdio.h>

#include "geom/sphere.hpp"

#include "types.hpp"

int main()
{
    geom::Sphere s(glm::vec3(0), 0.5);

	printf("Hello, node.\n");

	return 0;
}
