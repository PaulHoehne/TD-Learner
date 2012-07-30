/*
 * Learner.h
 *
 *  Created on: Jul 28, 2012
 *      Author: phoehne
 */

#include <map>
#include <vector>
#include <set>
#include <string>

#include "World.h"
#include "State.h"
#include "Action.h"
#include "StateHistory.h"

#ifndef LEARNER_H_
#define LEARNER_H_

namespace AI {

class Learner {
	std::map<State, StateHistory> _histories;

	std::map<State, double> _utilities;
	double _curiosity;
	int _totalStatesVisted;
	double _learningRate;
	double _discount;

	std::set<Action> ActionsTaken(const State& state);
	std::set<Action> ActionsNotTaken(const World& world, const State& state);
	std::map<Action, double> BestActions(const World& world, const State& state);
	double ExpectedValueForAction(const State& state, const Action& action);
	Action RandomAction(const World& world, const State& state);
	std::map<Action, int> ActionDistribution(const World& world, const State& state);
	Action ChooseAction(const std::map<Action, double>& best, const std::map<Action, int>& counts);
	double CalculateUtility(const World& world, const State& currentState, const State& nextState);
public:
	Learner();
	virtual ~Learner();

	void Learn(const World& world, const std::set<std::string>& terminals);
	void PrintUtilities(const World& world);
};

} /* namespace AI */
#endif /* LEARNER_H_ */
