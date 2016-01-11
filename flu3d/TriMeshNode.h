#pragma once

#include "SceneNode.h"
#include "Material.h"
#include "Mesh.h"

class TriMeshNode : public SceneNode {
protected:
	std::vector<Mesh *> _meshes;

	void reloadTextures();

public:
	TriMeshNode(char *name = NULL, Vector translation = Vector(), Vector rotation = Vector(), float scale = 1.0f) :
		SceneNode(name, translation, rotation, scale) {}
	~TriMeshNode();

	void applyFixed(const Material &material, const char *textureFile);
	void loadFile(const char *fileName, bool useFixed = false);
	void setFixedMaterial(const Material &material);

	void bake();
	void render();
};
