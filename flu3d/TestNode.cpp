#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "TestNode.h"
#include "Exceptions.h"
#include "Log/Log.h"

TestNode::~TestNode() {
}

void TestNode::create() {
	// Create the entity
	_faces.push_back(
		Triangle(
			/* vectors */
			Vector(0.0f, 1.0f, 0.0f, Color(1.0f, 0.0f, 0.0f, 1.0f)),
			Vector(-1.0f, -1.0f, 0.0f, Color(0.0f, 1.0f, 0.0f, 0.6f)),
			Vector(1.0f, -1.0f, 0.0f, Color(0.0f, 0.0f, 1.0f, 1.0f)),
			/* normals */
			Vector(0.0f, 1.0f, 1.0f),
			Vector(-1.0f, -1.0f, 1.0f),
			Vector(1.0f, -1.0f, 1.0f)
		)
	);
}

void TestNode::bake() {
	Log::debug("Baking TestNode");
	SceneNode::bake();
}

void TestNode::render() {
	//Log::debug("Rendering TestNode");
	glPushMatrix();
	matrixTransform();

	glBegin(GL_TRIANGLES);
	for (std::vector<Triangle>::iterator it = _faces.begin(); it != _faces.end(); ++it) {
		Triangle tri = (*it);
		glNormal3f(tri.aN.x, tri.aN.y, tri.aN.z);
		renderVectorColor(tri.a);
		glVertex3f(tri.a.x, tri.a.y, tri.a.z);

		glNormal3f(tri.bN.x, tri.bN.y, tri.bN.z);
		renderVectorColor(tri.b);
		glVertex3f(tri.b.x, tri.b.y, tri.b.z);

		glNormal3f(tri.cN.x, tri.cN.y, tri.cN.z);
		renderVectorColor(tri.c);
		glVertex3f(tri.c.x, tri.c.y, tri.c.z);
	}
	glEnd();

	renderChildren();
}
