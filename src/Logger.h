/*
 * Logger.h
 *
 *  Created on: Jul 29, 2012
 *      Author: phoehne
 */

#include <string>

#ifndef LOGGER_H_
#define LOGGER_H_

namespace AI {

enum LOG_LEVEL {
	VERBOSE = 1,
	INFO,
	DEBUG,
	WARN,
	ERROR,
	SEVERE
};

class Logger {
	Logger();
	virtual ~Logger();
	static LOG_LEVEL _level;
public:
	static void Log(const LOG_LEVEL& level, const std::string& message);
	static void Info(const std::string& message);
	static void Debug(const std::string& message);
	static void Warn(const std::string& message);
	static void Error(const std::string& message);
	static void Severe(const std::string& message);

	static void SetLevel(const LOG_LEVEL& val);
	static LOG_LEVEL GetLevel(void);
};

} /* namespace AI */
#endif /* LOGGER_H_ */
