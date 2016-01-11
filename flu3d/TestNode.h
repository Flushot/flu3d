#pragma once

#include "SceneNode.h"

class TestNode : public SceneNode {
protected:
	std::vector<Triangle> _faces;

	void create();

public:
	TestNode(char *name = NULL, Vector translation = Vector(), Vector rotation = Vector(), float scale = 1.0f) :
		SceneNode(name, translation, rotation, scale) {
		create();
	}
	~TestNode();

	void bake();
	void render();
};
