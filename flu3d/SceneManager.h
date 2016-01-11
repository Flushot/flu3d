#pragma once

#include "SceneNode.h"
#include "OctreeNode.h"

/*
Octree Scene Manager
*/

class SceneManager {
private:
	char *_fileName;
	SceneNode *_sceneRoot;
	OctreeNode *_octreeRoot;

public:
	SceneManager();
	~SceneManager();

	void loadFile(const char *fileName);
	void saveFile();
	void saveFile(const char *fileName);

	SceneNode *getRoot() const { return _sceneRoot; }
	SceneNode *setRoot(SceneNode *node);

	SceneNode *insertBefore(SceneNode *before, SceneNode *node);
	SceneNode *insertAfter(SceneNode *after, SceneNode *node);

	void bake();
	void render();
};
