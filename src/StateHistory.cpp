/*
 * StateHistory.cpp
 *
 *  Created on: Jul 28, 2012
 *      Author: phoehne
 */

#include "StateHistory.h"
#include "Logger.h"
#include <sstream>

namespace AI {

StateHistory::StateHistory() {
	// TODO Auto-generated constructor stub

}

StateHistory::~StateHistory() {
	// TODO Auto-generated destructor stub
}

StateHistory::StateHistory(const State& state) : _state(state) {
	;
}

void StateHistory::AddAttempt(const Action& action, const State& resultState) {
	_actionAttempts[action]++;
	_resultDistributions[action][resultState]++;
	if(_actionsTaken.find(action) == _actionsTaken.end()) _actionsTaken.insert(action);
}

std::map<State, double> StateHistory::GetProbabilities(const Action& action) {
	int totalAttemps = _actionAttempts[action];
	std::map<State, double> result;

	std::map<State, int>::const_iterator iter;
	for(iter = _resultDistributions[action].begin(); iter != _resultDistributions[action].end(); iter++) {
		result[iter->first] = double(iter->second)/double(totalAttemps);
	}
	return result;
}

int StateHistory::GetAttempts(const Action& action) {
	return _actionAttempts[action];
}

std::set<Action> StateHistory::ActionsTaken() {
	return _actionsTaken;
}

} /* namespace AI */
