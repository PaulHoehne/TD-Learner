/*
 * Action.cpp
 *
 *  Created on: Jul 28, 2012
 *      Author: phoehne
 */

#include "Action.h"

namespace AI {

Action::Action() {
	_direction = NORTH;
}

Action::Action(const DIRECTION& direction) {
	_direction = direction;
}

Action::~Action() {
	// TODO Auto-generated destructor stub
}

DIRECTION Action::Direction() const {
	return _direction;
}

bool Action::operator<(const Action& other) const {
	return this->_direction < other._direction;
}

std::ostream& operator<<(std::ostream& os, const Action& action) {
	switch(action._direction) {
	case NORTH:
		os << North;
		break;
	case SOUTH:
		os << South;
		break;
	case EAST:
		os << East;
		break;
	case WEST:
		os << West;
		break;
	default:
		os << "ERROR INVALID DIRECTION";
		break;
	}
	return os;
}

} /* namespace AI */
