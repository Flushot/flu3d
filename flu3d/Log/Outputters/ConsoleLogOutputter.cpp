#include "ConsoleLogOutputter.h"
#include <iostream>
using namespace std;

void ConsoleLogOutputter::write(const string &type, const string &message) {
	cout << "[" << type << "] " << message << endl;
}

void ConsoleLogOutputter::flush() {
	cout << std::flush;
}

