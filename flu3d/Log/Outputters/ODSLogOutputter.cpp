#pragma once

#include <windows.h>
#include "ODSLogOutputter.h"
using namespace std;

void ODSLogOutputter::write(const string &type, const string &message) {
	string output = "[" + type + "] " + message + "\n";
	OutputDebugStringA(output.c_str());
}

void ODSLogOutputter::flush() {
	// No flush implementation for ODS; Do nothing.
}
