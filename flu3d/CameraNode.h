#pragma once

#include "SceneNode.h"

class CameraNode : public SceneNode {
protected:
	void create();

public:
	CameraNode(char *name = NULL, Vector translation = Vector(), Vector rotation = Vector(), float scale = 1.0f) :
		SceneNode(name, translation, rotation, scale) {
		create();
	}
	~CameraNode();

	void bake();
	void render();
};
