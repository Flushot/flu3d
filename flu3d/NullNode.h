#pragma once

#include "SceneNode.h"

class NullNode : public SceneNode {
public:
	NullNode(char *name = NULL, Vector translation = Vector(), Vector rotation = Vector(), float scale = 1.0f) :
		SceneNode(name, translation, rotation, scale) {}
	~NullNode();

	void bake();
	void render();
};
