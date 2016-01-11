#pragma once

#include "SceneNode.h"

class ParticleGenNode : public SceneNode {
public:
	ParticleGenNode(char *name = NULL, Vector translation = Vector(), Vector rotation = Vector(), float scale = 1.0f) :
		SceneNode(name, translation, rotation, scale) {}
	~NullNode();

	void bake();
	void render();
};
