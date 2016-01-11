#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "CameraNode.h"
#include "Exceptions.h"
#include "Log/Log.h"
using namespace std;

CameraNode::~CameraNode() {
}

void CameraNode::create() {
	// Create the entity
}

void CameraNode::bake() {
	Log::debug("Baking CameraNode");
	SceneNode::bake();
}

void CameraNode::render() {
	//Log::debug("Rendering CameraNode");
	glPushMatrix();
	matrixTransform();

	// Draw a single green triangle denoting camera (for debugging)
	glBegin(GL_TRIANGLES);
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glVertex3f(-0.1f, 0.1f, 0.0f);
		glVertex3f(0.0f, -0.1f, 0.0f);
		glVertex3f(0.1f, 0.1f, 0.0f);
	glEnd();

	renderChildren();
}