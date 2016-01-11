#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "SceneNode.h"
#include "Log/Log.h"
using namespace std;

SceneNode::SceneNode(char *name, Vector translation, Vector rotation, float scale) {
	_parent = NULL;
	_name = name;
	_translation = translation;
	_initRotation = rotation;
	_scale = scale;
}
SceneNode::~SceneNode() {
	killChildren();
}

void SceneNode::killChildren() {
	for (vector<SceneNode *>::iterator it = _children.begin(); it != _children.end(); ++it) {
		SceneNode *child = (*it);
		if (child != NULL)
			delete child;
	}

	_children.clear();
}

void SceneNode::renderVectorColor(Vector v) {
	if (v.hasColor()) {
		Color color = v.getColor();
		glColor4f(color.r, color.g, color.b, color.a);
	}
}

void SceneNode::matrixTransform() {
	glRotatef(_initRotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(_initRotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(_initRotation.z, 0.0f, 0.0f, 1.0f);
	glTranslatef(_translation.x, _translation.y, _translation.z);
	glScalef(_scale, _scale, _scale);
	glRotatef(_rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(_rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(_rotation.z, 0.0f, 0.0f, 1.0f);
}

void SceneNode::setChildren(vector<SceneNode *> children) {
	killChildren();
	_children = children;
}
SceneNode *SceneNode::addChild(SceneNode *child) {
	child->setParent(this);
	_children.push_back(child);
	return child;
}
void SceneNode::removeChild(SceneNode *child) {
	for (vector<SceneNode *>::iterator it = _children.begin(); it != _children.end(); ++it) {
		SceneNode *pChild = (*it);
		if (child == pChild) {
			// Found the bastard
			_children.erase(it);
			delete pChild;
		}
	}
}
SceneNode *SceneNode::findChild(const char *name) {
	// Check node itself
	if ( strcmp(getName(), name) == 0 )
		return this;

	// Breadth-first search children
	vector<SceneNode *> children = getChildren();
	for (vector<SceneNode *>::iterator it = _children.begin(); it != _children.end(); ++it) {
		SceneNode *child = (*it)->findChild(name);
		if (child != NULL) {
			// Result found in child
			return child;
		}
	}

	// No results found
	return NULL;
}

void SceneNode::bake() {
	for (std::vector<SceneNode *>::iterator it = _children.begin(); it != _children.end(); ++it)
		(*it)->bake();
}

void SceneNode::renderChildren() {
	//Log::debug("Rendering SceneNode children");
	for (vector<SceneNode *>::iterator it = _children.begin(); it != _children.end(); ++it)
		(*it)->render();

	glPopMatrix();
}
