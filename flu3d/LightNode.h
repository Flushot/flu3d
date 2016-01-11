#pragma once

#include "SceneNode.h"
#include <map>

// Just a testing entity. This is a static object.
class LightNode : public SceneNode {
protected:
	static bool lightPool[7];
	int _lightId;

	void create();

public:
	LightNode(char *name = NULL, Vector translation = Vector(), Vector rotation = Vector(), float scale = 1.0f) :
		SceneNode(name, translation, rotation, scale) {
		_lightId = 0;
		create();
	}
	~LightNode();

	void bake();
	void render();
};
