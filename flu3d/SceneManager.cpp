#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "SceneManager.h"
#include "Exceptions.h"
#include "Log/Log.h"
using namespace std;

SceneManager::SceneManager() {
	_fileName = NULL;
	_sceneRoot = NULL;
	_octreeRoot = NULL;
}
SceneManager::~SceneManager() {
	delete _octreeRoot;
	delete _sceneRoot;
}

void SceneManager::loadFile(const char *fileName) {
	// TODO
}
void SceneManager::saveFile() {
	saveFile(_fileName);
}
void SceneManager::saveFile(const char *fileName) {
	if (fileName == NULL)
		throw new SceneFileException("File name not specified");
}

SceneNode *SceneManager::setRoot(SceneNode *node) {
	if (_sceneRoot != NULL)
		delete _sceneRoot;
	
	SceneNode *parent = node->getParent();
	if (parent != NULL) {
		delete parent;
		node->setParent(NULL);
	}

	_sceneRoot = node;

	return node;
}

SceneNode *SceneManager::insertBefore(SceneNode *before, SceneNode *node) {
	if (before == NULL) {
		if (_sceneRoot == NULL)
			return setRoot(node);

		before = _sceneRoot;
	}

	SceneNode *temp = before->getParent();
	temp->removeChild(before);
	temp->addChild(node);
	before->setParent(node);

	return node;
}
SceneNode *SceneManager::insertAfter(SceneNode *after, SceneNode *node) {
	if (after == NULL)
		return setRoot(node);

	after->addChild(node);

	return node;
}

void SceneManager::bake() {
	if (_sceneRoot != NULL)
		_sceneRoot->bake();

	// TODO: Calculate octree
}

void SceneManager::render() {
	// Breadth-first render
	//Log::debug("Rendering Scene");

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*
	gluLookAt(
		0.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 1.0f, 
		0.0f, 0.0f, 0.0f);
	*/

	// HACK: For some reason, starting with the identity matrix makes 0,0,0 left of true center.
	//glTranslatef(1.5f, 0.0f, 0.0f);

	if (_sceneRoot != NULL)
		_sceneRoot->render();
}
