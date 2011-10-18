/*
 * light.hpp
 *
 *  Created on: Oct 8, 2011
 *      Author: cgibson
 */

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include "types.hpp"
#include "geom/shape.hpp"

namespace light {


	class Light : public Node{

	public:
		Light(glm::vec3 const & center, Spectrum const & color);

		virtual float intersect(util::Ray const & ray) const { return -1; };
		virtual string str() const;

		Spectrum color;

	};

}

#endif /* LIGHT_HPP_ */
