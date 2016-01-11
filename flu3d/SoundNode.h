#pragma once

#include "SceneNode.h"

class SoundNode : public SceneNode {
protected:

public:
	SoundNode(char *name = NULL, Vector translation = Vector(), Vector rotation = Vector(), float scale = 1.0f) :
		SceneNode(name, translation, rotation, scale) {}
	~SoundNode();

	void loadFile(const char *fileName);

	void bake();
	void render();
};
