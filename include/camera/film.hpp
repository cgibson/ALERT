/*
 * Film.hpp
 *
 *  Created on: Oct 17, 2011
 *      Author: cgibson
 */

#ifndef FILM_HPP_
#define FILM_HPP_

#include "types.hpp"

class Film {
public:
	Film() {};
	virtual ~Film() {}

	Dimension resolution;
};

#endif /* FILM_HPP_ */
