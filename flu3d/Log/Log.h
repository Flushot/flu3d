#pragma once

#include <string>
#include <vector>

// Include all outputters
#include "Outputters/ODSLogOutputter.h"
#include "Outputters/ConsoleLogOutputter.h"

class Log {
private:
	static Log *_instance;
	std::vector<ILogOutputter *> _outputters;

protected:
	Log();
	//Log(const Log &);
	//Log &operator= (const Log &);
	void displayMessage(std::string type, std::string message);
	void mapOutputter(ILogOutputter *outputter);
	void flushAll();

public:
	~Log();
	static Log *getInstance();

	static void error(const std::string &message);
	static void warn(const std::string &message);
	static void info(const std::string &message);
	static void debug(const std::string &message);

	static void addOutputter(ILogOutputter *outputter);
	static void flush();
};
