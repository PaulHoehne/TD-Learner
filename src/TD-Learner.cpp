//============================================================================
// Name        : TD-Learner.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <set>

#include "Logger.h"
#include "Learner.h"
#include "World.h"
#include "State.h"

using namespace std;

int main() {
	AI::Learner learner;
	AI::World world(6, 8);
	std::set<std::string> terminals;

	world.AddReward(AI::State(2, 7), 1.0, "Exit");
	world.AddReward(AI::State(3, 7), -1.0, "Wumpus");
	world.AddWall(AI::State(0, 3));
	world.AddWall(AI::State(1, 3));
	world.AddWall(AI::State(2, 3));
	world.AddWall(AI::State(3, 3));
	world.AddWall(AI::State(2, 2));
	world.AddWall(AI::State(2, 1));
	world.AddWall(AI::State(3, 4));
	world.AddWall(AI::State(3, 5));

	terminals.insert("Exit");
	terminals.insert("Wumpus");

	AI::Logger::SetLevel(AI::DEBUG);

	AI::Logger::Debug("Starting the lerning process");
	learner.Learn(world, terminals);
	AI::Logger::Debug("Learning is complete.");

	learner.PrintUtilities(world);
}
