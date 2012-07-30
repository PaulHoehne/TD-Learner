/*
 * StateHistory.h
 *
 *  Created on: Jul 28, 2012
 *      Author: phoehne
 */

#include <set>
#include <map>
#include "State.h"
#include "Action.h"

#ifndef STATEHISTORY_H_
#define STATEHISTORY_H_

namespace AI {

class StateHistory {
	State _state;

	std::map<Action, int> _actionAttempts;
	std::map<Action, std::map<State, int> > _resultDistributions;
	std::set<Action> _actionsTaken;

public:
	StateHistory();
	StateHistory(const State& state);
	virtual ~StateHistory();

	virtual void AddAttempt(const Action& action, const State& resultState);
	virtual std::map<State, double> GetProbabilities(const Action& action);
	virtual int GetAttempts(const Action& action);
	virtual std::set<Action> ActionsTaken();
};

} /* namespace AI */
#endif /* STATEHISTORY_H_ */
