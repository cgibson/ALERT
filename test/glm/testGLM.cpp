/*
 * test.cpp
 *
 *  Created on: Oct 1, 2011
 *      Author: cgibson
 */

#include <stdio.h>

#include "types.hpp"

int main()
{

	printf("Hello, World\n");

	vec3 const & test = glm::vec3(1.0,2.0,3.0);

	printf("Here is a vector: %f,%f,%f\n", test.x, test.y, test.z);

	vec3 eye(0,5,5);
	vec3 look(0);
	vec3 up(0,1,0);

	mat4 mvp = glm::lookAt(eye, look, up);

	printf("%.2f, %.2f, %.2f, %.2f\n", mvp[0][0], mvp[0][1], mvp[0][2], mvp[0][3]);
	printf("%.2f, %.2f, %.2f, %.2f\n", mvp[1][0], mvp[1][1], mvp[1][2], mvp[1][3]);
	printf("%.2f, %.2f, %.2f, %.2f\n", mvp[2][0], mvp[2][1], mvp[2][2], mvp[2][3]);
	printf("%.2f, %.2f, %.2f, %.2f\n", mvp[3][0], mvp[3][1], mvp[3][2], mvp[3][3]);

	return 0;
}
