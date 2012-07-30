/*
 * State.h
 *
 *  Created on: Jul 28, 2012
 *      Author: phoehne
 */

#include <ostream>
#ifndef STATE_H_
#define STATE_H_

namespace AI {

class State {
	int _row;
	int _column;
public:
	State();
	State(const int& row, const int& column);
	virtual ~State();

	virtual int Row() const;
	virtual int Column() const;

	virtual void SetRow(const int& row);
	virtual void SetColumn(const int& column);

	bool operator<(const State& other) const;

	friend std::ostream& operator<<(std::ostream& os, const State& state);
};

} /* namespace AI */
#endif /* STATE_H_ */
