#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "SoundNode.h"
#include "Exceptions.h"
#include "Log/Log.h"
using namespace std;

SoundNode::~SoundNode() {
}

void SoundNode::loadFile(const char *fileName) {
}

void SoundNode::bake() {
	Log::debug("Baking SoundNode");
	SceneNode::bake();
}

void SoundNode::render() {
	//Log::debug("Rendering SoundNode");
	glPushMatrix();
	matrixTransform();

	// TODO: Show visual indicator of sound
	// TODO: Implement this

	renderChildren();
}
