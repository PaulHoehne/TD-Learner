/*
 * World.h
 *
 *  Created on: Jul 28, 2012
 *      Author: phoehne
 */

#include <string>
#include <vector>
#include <map>
#include <set>
#include "State.h"
#include "Action.h"

#ifndef WORLD_H_
#define WORLD_H_

namespace AI {

class World {
	std::vector<std::vector<std::string> > _world;
	std::map<State, std::pair<std::string, double> > _rewards;
	double _defaultReward;
	int _width, _height;
public:
	World();
	World(const int& rows, const int& cols);
	virtual ~World();

	virtual State operator()(const State& state, const Action& action) const;
	virtual void AddWall(const State& state);
	virtual void AddReward(const State& state, const double& reward, const std::string& tag = "Reward");
	virtual void SetDefaultReward(const double& reward);
	virtual double Reward(const State& state) const;
	virtual std::string RewardTag(const State& state) const;

	virtual std::set<Action> AllowedActions(const State& state) const;
	virtual State StartState() const;
	virtual int Width() const;
	virtual int Height() const;
};

} /* namespace AI */
#endif /* WORLD_H_ */
