/*
 * Trace.h
 *
 *  Created on: Jul 29, 2012
 *      Author: phoehne
 */

#include <vector>
#include "State.h"
#include "Action.h"

#ifndef TRACE_H_
#define TRACE_H_

namespace AI {

class Trace {
public:
	class TraceLine {
		State _fromState;
		Action _actionTaken;
		State _toState;

	public:
		TraceLine() { ; }
		TraceLine(const State& state, const Action& action, const State& dest) {
			_fromState = state;
			_actionTaken = action;
			_toState = dest;
		}

		State FromState() const { return _fromState; }
		State ToState() const { return _toState; }
		Action ActionTaken() const { return _actionTaken; }
	};
private:
	std::vector<TraceLine> _trace;

public:


	Trace();
	virtual ~Trace();

	void AddTrace(const State& startState, const Action& action, const State& toState);
	std::vector<TraceLine> Traces();
};

} /* namespace AI */
#endif /* TRACE_H_ */
