#pragma once

#include "../ILogOutputter.h"
#include <string>

class ConsoleLogOutputter : public ILogOutputter {
public:
	void write(const std::string &type, const std::string &message);
	void flush();
};
