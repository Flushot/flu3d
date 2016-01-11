#pragma once

#include <cassert>
#include "Log.h"
using namespace std;

Log::Log() {
}
Log::~Log() {
}

Log *Log::_instance = NULL;
Log *Log::getInstance() {
	if (_instance == NULL)
		_instance = new Log();
	return _instance;
};

void Log::displayMessage(const string type, const string message) {
	assert(!_outputters.empty() && "No log outputters defined");
	for (vector<ILogOutputter *>::iterator it = _outputters.begin(); it != _outputters.end(); ++it)
		(*it)->write(type, message);
}

void Log::flushAll() {
	assert(!_outputters.empty() && "No log outputters defined");
	for (vector<ILogOutputter *>::iterator it = _outputters.begin(); it != _outputters.end(); ++it)
		(*it)->flush();
}

void Log::mapOutputter(ILogOutputter *outputter) {
	_outputters.push_back(outputter);
}

void Log::error(const string &message) {
	Log::getInstance()->displayMessage("ERROR", message);
}
void Log::warn(const string &message) {
	Log::getInstance()->displayMessage("WARN", message);
}
void Log::info(const string &message) {
	Log::getInstance()->displayMessage("INFO", message);
}
void Log::debug(const string &message) {
	Log::getInstance()->displayMessage("DEBUG", message);
}

void Log::addOutputter(ILogOutputter *outputter) {
	Log::getInstance()->mapOutputter(outputter);
}

void Log::flush() {
	Log::getInstance()->flushAll();
}
