/*
 * Ray.h
 *
 *  Created on: Oct 2, 2011
 *      Author: cgibson
 */

#ifndef RAY_HPP_
#define RAY_HPP_

#include "types.hpp"

namespace util {

	class Ray {
	public:
		Ray(vec3 start, vec3 direction);
		virtual ~Ray(){};

		string str() const;

		vec3 operator() (float t) const { return p + (w * t); }

		vec3 p;
		vec3 w;

		float tMin;
		float tMax;
	};

}

#endif /* RAY_HPP_ */
