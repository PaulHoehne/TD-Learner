/*
 * Action.h
 *
 *  Created on: Jul 28, 2012
 *      Author: phoehne
 */
#include <string>
#include <ostream>

#ifndef ACTION_H_
#define ACTION_H_

namespace AI {

enum DIRECTION {
	NORTH, SOUTH, EAST, WEST
};
const std::string North = "North";
const std::string South = "South";
const std::string East = "East";
const std::string West = "West";

class Action {
	DIRECTION _direction;
public:
	Action();
	Action(const DIRECTION& direction);
	virtual ~Action();

	virtual DIRECTION Direction() const;

	bool operator<(const Action& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Action& action);
};

} /* namespace AI */
#endif /* ACTION_H_ */
