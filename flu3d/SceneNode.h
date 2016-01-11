#pragma once

//#include "OctreeNode.h"
#include "Vector.h"
#include "Triangle.h"
#include <vector>

/*
SceneNode will automatically deallocate its descendents upon destruction
*/

class SceneNode {
protected:
	char *_name;
	SceneNode *_parent;
	std::vector<SceneNode *> _children;
	//OctreeNode *_octreeNode;

	// Matrix transformable
	Vector _translation;
	Vector _rotation, _initRotation;
	float _scale;

	SceneNode(char *name = NULL, Vector translation = Vector(), Vector rotation = Vector(), float scale = 1.0f);

	void killChildren();
	void renderChildren();
	void renderVectorColor(Vector v);
	void matrixTransform();

public:
	~SceneNode();

	char *getName() const { return _name; }
	void setName(char *name) { _name = name; }

	bool hasParent() const { return _parent != NULL; }
	SceneNode *getParent() const { return _parent; }
	void setParent(SceneNode *parent) { _parent = parent; }

	bool hasChildren() const { return !_children.empty(); }
	std::vector<SceneNode *> getChildren() const { return _children; }
	void setChildren(std::vector<SceneNode *> children);
	SceneNode *addChild(SceneNode *child);
	void removeChild(SceneNode *child);
	SceneNode *findChild(const char *name);

	/*
	bool hasOctreeNode() const { return _octreeNode != NULL; }
	OctreeNode *getOctreeNode() const { return _octreeNode; }
	void setOctreeNode(OctreeNode *octreeNode) { _octreeNode = octreeNode; }
	*/

	// Matrix transforms
	Vector getTranslation() const { return _translation; }
	void setTranslation(const Vector &translation) { _translation = translation; }

	Vector getRotation() const { return _rotation; }
	void setRotation(const Vector &rotation) { _rotation = rotation; }

	float getScale() const { return _scale; }
	void setScale(float scale) { _scale = scale; }

	virtual void bake();
	virtual void render() = 0;
};

#include "TestNode.h"
#include "TriMeshNode.h"
#include "LightNode.h"
#include "SoundNode.h"
#include "CameraNode.h"
#include "NullNode.h"
