#pragma once

#include "../ILogOutputter.h"
#include <string>

class ODSLogOutputter : public ILogOutputter {
	void write(const std::string &type, const std::string &message);
	void flush();
};
