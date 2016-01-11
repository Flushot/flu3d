#pragma once

#include "Entity.h"
#include "Exceptions.h"

class AudioEntity : public Entity {
protected:
	char *_fileName;
	bool _isLoop; // Is this a looping audio sample?

public:
	AudioEntity();
	AudioEntity(char *name) : Entity(name) {}
	AudioEntity(char *name, Vector translation, Vector rotation, float scale) :
		Entity(name, translation, rotation, scale) {}
	~AudioEntity();

	void loadFile(const char *fileName);
	void render();
};
