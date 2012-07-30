/*
 * World.cpp
 *
 *  Created on: Jul 28, 2012
 *      Author: phoehne
 */

#include <sstream>
#include "World.h"
#include "Logger.h"

namespace AI {

World::World() {
	std::vector<std::string> row;
	row.resize(4, "");

	_world.resize(3, row);
	_defaultReward = -0.04;
	_width = 4;
	_height = 3;
}

World::~World() {
	// TODO Auto-generated destructor stub
}

World::World(const int& rows, const int& cols) {
	std::vector<std::string> row;
	row.resize(cols, "");

	_world.resize(rows, row);
	_defaultReward = -0.04;
	_width = cols;
	_height = rows;
}

State World::operator()(const State& state, const Action& action) const {
	State newState;

	switch(action.Direction()) {
	case NORTH:
		newState = State(state.Row() - 1, state.Column());
		break;
	case EAST:
		newState = State(state.Row(), state.Column() + 1);
		break;
	case SOUTH:
		newState = State(state.Row() + 1, state.Column());
		break;
	case WEST:
		newState = State(state.Row(), state.Column() - 1);
		break;
	}

	if(newState.Row() < 0 || newState.Row() >= _height || newState.Column() < 0 || newState.Column() >= _width)
		return state;
	if(_world[newState.Row()][newState.Column()] == "Wall")
		return state;
	return newState;
}

void World::AddWall(const State& state) {
	_world[state.Row()][state.Column()] = "Wall";
}

void World::AddReward(const State& state, const double& reward, const std::string& tag) {
	_world[state.Row()][state.Column()] = tag;
	_rewards[state] = std::pair<std::string, double>(tag, reward);
}

void World::SetDefaultReward(const double& reward) {
	_defaultReward = reward;
}

double World::Reward(const State& state) const {
	if(_rewards.find(state) != _rewards.end()) {
		return _rewards.at(state).second;
	}
	return _defaultReward;
}

std::string World::RewardTag(const State& state) const {
	return _world[state.Row()][state.Column()];
}

std::set<Action> World::AllowedActions(const State& state) const {
	std::set<Action> result;

	result.insert(Action(NORTH));
	result.insert(Action(SOUTH));
	result.insert(Action(EAST));
	result.insert(Action(WEST));

	return result;
}

State World::StartState() const {
	return State(_height - 1, 0);
}

int World::Height() const {
	return _height;
}

int World::Width() const {
	return _width;
}

} /* namespace AI */
