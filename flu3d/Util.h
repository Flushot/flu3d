#pragma once

#include <string>
#include <sstream>

template <class T>
std::string toStr(T val) {
	ostringstream os;
	os << val;
	return os.str();
}
