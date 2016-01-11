#pragma once

#include "SceneNode.h"
#include <vector>

class OctreeNode {
private:
	OctreeNode *_parent;
	std::vector<SceneNode *> _sceneNodes;
	OctreeNode *_children[8];

	void killChildren() {
		// NOTE: This node is NOT responsible for deleting SceneNode objects, as it's just referencing them. It will reap its own children though.
	}

public:
	OctreeNode() {
		_parent = NULL;
	}
	OctreeNode(OctreeNode *parent, std::vector<SceneNode *> sceneNodes) {
		_parent = parent;
		setSceneNodes(sceneNodes);
	}
	~OctreeNode() {
		killChildren();
	}

	void setSceneNodes(std::vector<SceneNode *> sceneNodes) {
		// TODO: Test if the node belong in a child node instead
		_sceneNodes = sceneNodes;
	}
	std::vector<SceneNode *> getSceneNodes() const { return _sceneNodes; }
};
