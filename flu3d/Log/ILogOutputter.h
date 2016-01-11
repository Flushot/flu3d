#pragma once

#include <string>

class ILogOutputter {
public:
	virtual void write(const std::string &type, const std::string &message) = 0;
	virtual void flush() = 0;
};
