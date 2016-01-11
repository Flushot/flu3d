#pragma once

#include <exception>

class BaseException : public std::exception {
public:
	char *message;
	int code;

	BaseException() {}
	BaseException(char *message) {
		this->message = message;
	}
	BaseException(char *message, int code) {
		this->code = code;
		this->message = message;
	}
};

class NotImplementedException : public BaseException {
public:
	NotImplementedException() {}
	NotImplementedException(char *message) : BaseException(message) {}
	NotImplementedException(char *message, int code) : BaseException(message, code) {}
};

// Base engine exception
class EngineException : public BaseException {
public:
	EngineException() {}
	EngineException(char *message) : BaseException(message) {}
	EngineException(char *message, int code) : BaseException(message, code) {}
};

class EngineInitializationException : public EngineException {
public:
	EngineInitializationException() {}
	EngineInitializationException(char *message) : EngineException(message) {}
	EngineInitializationException(char *message, int code) : EngineException(message, code) {}
};

class EngineRenderException : public EngineException {
public:
	EngineRenderException() {}
	EngineRenderException(char *message) : EngineException(message) {}
	EngineRenderException(char *message, int code) : EngineException(message, code) {}
};

// Base scene exception
class SceneException : public BaseException {
public:
	SceneException() {}
	SceneException(char *message) : BaseException(message) {}
	SceneException(char *message, int code) : BaseException(message, code) {}
};

class SceneFileException : public SceneException {
public:
	SceneFileException() {}
	SceneFileException(char *message) : SceneException(message) {}
	SceneFileException(char *message, int code) : SceneException(message, code) {}
};
