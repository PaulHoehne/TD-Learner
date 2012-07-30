/*
 * State.cpp
 *
 *  Created on: Jul 28, 2012
 *      Author: phoehne
 */

#include "State.h"

namespace AI {

State::State() {
	_row = _column = 0;
}

State::State(const int& row, const int& column) {
	_row = row;
	_column = column;
}

State::~State() {
	// TODO Auto-generated destructor stub
}

int State::Row() const {
	return _row;
}

int State::Column() const {
	return _column;
}

void State::SetRow(const int& row) {
	_row = row;
}

void State::SetColumn(const int& column) {
	_column = column;
}

bool State::operator<(const State& other) const {
	return (this->_row < other._row ) || (this->_row == other._row && this->_column < other._column);
}

std::ostream& operator<<(std::ostream& os, const State& state) {
	os << "(" << state._row <<", " << state._column << ")";
	return os;
}

} /* namespace AI */
