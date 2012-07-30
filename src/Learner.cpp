/*
 * Learner.cpp
 *
 *  Created on: Jul 28, 2012
 *      Author: phoehne
 */

#include "Learner.h"
#include "Logger.h"
#include "Trace.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

namespace AI {

Learner::Learner() {
	_curiosity = 0.1;
	_totalStatesVisted = 0;
	_discount = 0.90;
	_learningRate = 0.10;
}

Learner::~Learner() {
	// TODO Auto-generated destructor stub
}

std::set<Action> Learner::ActionsTaken(const State& state) {
	return _histories[state].ActionsTaken();
}

std::set<Action> Learner::ActionsNotTaken(const World& world, const State& state) {
	std::set<Action> actionsTaken = ActionsTaken(state);
	std::set<Action> possibleActions = world.AllowedActions(state);

	std::set<Action>::iterator iter;
	for(iter = actionsTaken.begin(); iter != actionsTaken.end(); iter++) {
		possibleActions.erase(*iter);
	}

	return possibleActions;
}

double Learner::ExpectedValueForAction(const State& state, const Action& action) {
	std::map<State, double> distribution = _histories[state].GetProbabilities(action);
	std::map<State, double>::const_iterator iter;
	std::stringstream oss;

	std::map<State, double>::iterator result_iter;
	double expectedValue = 0.0;

	for(result_iter = distribution.begin(); result_iter != distribution.end(); result_iter++) {
		expectedValue += result_iter->second * _utilities[result_iter->first];
	}
	return expectedValue;
}

std::map<Action, double> Learner::BestActions(const World& world, const State& state) {
	std::set<Action> actionsTaken = ActionsTaken(state);
	std::map<Action, double> bestActions;
	double bestExpectedValue = -9.99E-99;

	std::set<Action>::iterator iter;
	for(iter = actionsTaken.begin(); iter != actionsTaken.end(); iter++) {
		double expectedValue = ExpectedValueForAction(state, *iter);

		if(expectedValue > bestExpectedValue) {
			bestExpectedValue = expectedValue;
			bestActions.clear();
			bestActions[*iter] = expectedValue;
		} else if(expectedValue == bestExpectedValue) {
			bestActions[*iter] = expectedValue;
		}
	}
	return bestActions;
}

std::map<Action, int> Learner::ActionDistribution(const World& world, const State& state) {
	std::map<Action, int> result;
	std::set<Action> availableActions = world.AllowedActions(state);

	std::set<Action>::iterator iter;
	for(iter = availableActions.begin(); iter != availableActions.end(); iter++) {
		result[*iter] = _histories[state].GetAttempts(*iter);
	}
	return result;
}

Action Learner::RandomAction(const World& world, const State& state) {
	std::set<Action> possibleActions = world.AllowedActions(state);
	std::vector<Action> actions;
	std::set<Action>::iterator iter;

	for(iter = possibleActions.begin(); iter != possibleActions.end(); iter++) {
		actions.push_back(*iter);
	}

	return actions[random() % possibleActions.size()];
}

Action Learner::ChooseAction(const std::map<Action, double>& best, const std::map<Action, int>& counts) {
	double randVal = double(random())/double(RAND_MAX);
	Action result;

	if(randVal < _curiosity || best.empty()) {
		Action mostUntried;
		int worstFrequency = 0x7FFFFFFF;

		std::map<Action, int>::const_iterator iter;
		for(iter = counts.begin(); iter != counts.end(); iter++) {
			if(iter->second < worstFrequency) {
				mostUntried = iter->first;
				worstFrequency = iter->second;
			}
		}
		result = mostUntried;
	} else {
		if(best.size() > 1) {
			int which = random() % best.size();
			std::map<Action, double>::const_iterator iter;
			for(iter = best.begin(); iter != best.end(); iter++) {
				if(!which) {
					result = iter->first;
					break;
				}
			}
		} else {
			result = best.begin()->first;
		}
	}

	return result;
}

double Learner::CalculateUtility(const World& world, const State& currentState, const State& nextState) {
	double currentUtility = _utilities[currentState];
	double nextUtility = _utilities[nextState];
	double currentReward = world.Reward(currentState);

	return currentUtility + _learningRate * (currentReward + _discount * nextUtility - currentUtility);
}


void Learner::Learn(const World& world, const std::set<std::string>& terminals) {
	int iteration = 0;
	double averageUtility = 0.0;
	double oldAverageUtility = 0.0;
	double totalUtility = 0.0;
	std::ostringstream oss;

	while(true) { // learning loop
		State currentState = world.StartState();
		double totalUtilityForTrace = 0.0;
		iteration++;

		Trace trace;

		while(true) { // each iteration

			if(terminals.find(world.RewardTag(currentState)) == terminals.end()) {
				std::map<Action, double> bestActions = BestActions(world, currentState);
				std::map<Action, int> attempts = ActionDistribution(world, currentState);


				Action action = ChooseAction(bestActions, attempts);
				State nextState = world(currentState, action);
				trace.AddTrace(currentState, action, nextState);

				_histories[currentState].AddAttempt(action, nextState);
				_utilities[currentState] = CalculateUtility(world, currentState, nextState);

				totalUtilityForTrace += _utilities[currentState];
				currentState = nextState;
			} else {
				_utilities[currentState] = world.Reward(currentState);
				totalUtility += totalUtilityForTrace;
				break;
			}
		}
		//if(_curiosity > 0.05) { _curiosity *= 0.95; }

		if(iteration % 1000 == 0) {
			std::cout << "------------------------------------------------------" << std::endl;
			std::cout << "Iteration " << iteration << std::endl;
			PrintUtilities(world);
		}

		averageUtility = totalUtility / iteration;
		if(iteration > 25 && (::fabs((averageUtility - oldAverageUtility)/oldAverageUtility) < 0.01)) {
			std::cout << "Training complete after " << iteration << " iterations with:" << std::endl;
			std::cout << "Curiosity = " << _curiosity << std::endl;
			std::cout << "Average Utility = " << averageUtility << std::endl;
			break;
		}
		oldAverageUtility = averageUtility;
	}
}

void Learner::PrintUtilities(const World& world) {
	std::cout << std::setprecision(3);
	std::cout << std::setiosflags(std::ios::fixed);

	for(int i = 0; i < world.Height(); i++) {
		for(int j = 0; j < world.Width(); j++) {
			State s(i, j);
			std::cout << std::setw(8) << _utilities[s];
		}
		std::cout << std::endl;
	}
}

} /* namespace AI */
