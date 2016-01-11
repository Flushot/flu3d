#pragma once

class InputManager {
protected:
	static InputManager *_instance;

public:
	InputManager();
	~InputManager();
	InputManager *getInstance();
};
