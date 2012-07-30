/*
 * Logger.cpp
 *
 *  Created on: Jul 29, 2012
 *      Author: phoehne
 */

#include <iostream>

#include "Logger.h"

namespace AI {

LOG_LEVEL Logger::_level = ERROR;

Logger::Logger() {
	// TODO Auto-generated constructor stub
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

void Logger::Log(const LOG_LEVEL& level, const std::string& message) {
	std::string tag = "";

	if (level >= Logger::_level) {
		switch (level) {
		case VERBOSE:
			tag = "[VERBOSE]";
			break;
		case INFO:
			tag = "[INFO   ]";
			break;
		case DEBUG:
			tag = "[DEBUG  ]";
			break;
		case WARN:
			tag = "[WARN   ]";
			break;
		case ERROR:
			tag = "[ERROR  ]";
			break;
		case SEVERE:
			tag = "[SEVERE ]";
			break;
		}
		std::cout << tag << " " << message << std::endl;
	}
}
void Logger::Info(const std::string& message) {
	Logger::Log(INFO, message);
}

void Logger::Debug(const std::string& message) {
	Logger::Log(DEBUG, message);
}

void Logger::Warn(const std::string& message) {
	Logger::Log(WARN, message);
}

void Logger::Error(const std::string& message) {
	Logger::Log(ERROR, message);
}

void Logger::Severe(const std::string& message) {
	Logger::Log(SEVERE, message);
}

void Logger::SetLevel(const LOG_LEVEL& val) {
	Logger::_level = val;
}

LOG_LEVEL Logger::GetLevel() {
	return Logger::_level;
}

} /* namespace AI */
