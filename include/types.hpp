/*
 * types.hpp
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#ifndef TYPES_HPP_
#define TYPES_HPP_

#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <sstream>
#include <stdio.h>

using std::string;
using std::stringstream;

using glm::vec3;
using glm::vec4;
using glm::mat4;

typedef glm::vec4 Spectrum;
typedef glm::vec2 UvCoord;
typedef struct{float x; float y;} Dimension;

#define UNIMPLEMENTED_FUNC -1

#endif /* TYPES_HPP_ */
