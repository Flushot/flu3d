#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "LightNode.h"
#include "Exceptions.h"
#include "Log/Log.h"
#include "Util.h"
using namespace std;

bool LightNode::lightPool[7] = { false, false, false, false, false, false, false };

LightNode::~LightNode() {
	LightNode::lightPool[_lightId] = false;
}

void LightNode::create() {
	// Find first free light in pool
	for (int i = 0; i < 7; ++i) {
		if (! LightNode::lightPool[i]) {
			// Found a free slot
			_lightId = i;
			LightNode::lightPool[_lightId] = true;
			Log::debug("Allocated light " + toStr<int>(_lightId));
			return;
		}
	}

	throw new SceneException("No more lights available");
}

void LightNode::bake() {
	Log::debug("Baking LightNode");
	SceneNode::bake();
}

void LightNode::render() {
	//Log::debug("Rendering LightNode");
	glPushMatrix();
	matrixTransform();

	// Draw a single white triangle denoting light (for debugging)
	glBegin(GL_TRIANGLES);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glVertex3f(-0.1f, 0.1f, 0.0f);
		glVertex3f(0.0f, -0.1f, 0.0f);
		glVertex3f(0.1f, 0.1f, 0.0f);
	glEnd();

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	switch (_lightId) {
		case 0: glEnable(GL_LIGHT0); break;
		case 1: glEnable(GL_LIGHT1); break;
		case 2: glEnable(GL_LIGHT2); break;
		case 3: glEnable(GL_LIGHT3); break;
		case 4: glEnable(GL_LIGHT4); break;
		case 5: glEnable(GL_LIGHT5); break;
		case 6: glEnable(GL_LIGHT6); break;
		case 7: glEnable(GL_LIGHT7); break;
		default:
			throw new SceneException("Invalid light ID");
	}

	GLfloat mat_specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat mat_shininess[] = { 50.0f };
	GLfloat light_position[] = { _translation.x, _translation.y, _translation.z, 1.0f };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	renderChildren();
}
