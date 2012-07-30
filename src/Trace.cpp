/*
 * Trace.cpp
 *
 *  Created on: Jul 29, 2012
 *      Author: phoehne
 */

#include "Trace.h"

namespace AI {

Trace::Trace() {
	// TODO Auto-generated constructor stub

}

Trace::~Trace() {
	// TODO Auto-generated destructor stub
}

void Trace::AddTrace(const State& startState, const Action& action, const State& toState) {
	_trace.push_back(TraceLine(startState, action, toState));
}
std::vector<Trace::TraceLine> Trace::Traces() {
	return _trace;
}

} /* namespace AI */
