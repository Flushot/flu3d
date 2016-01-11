#include <windows.h>

#include "InputManager.h"

InputManager::InputManager() {
}

InputManager::~InputManager() {
}

InputManager *InputManager::_instance = NULL;
InputManager *InputManager::getInstance() {
	if (_instance == NULL)
		_instance = new InputManager();
	return _instance;
};
