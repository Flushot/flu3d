#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Mesh.h"
#include "Log/Log.h"
using namespace std;

void Mesh::bake() {
}

void Mesh::render() {
	//Log::debug("Rendering Mesh");
	// TODO: Bake check

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, material.emissive);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
	if (! material.textureFile.empty() ) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, material.textureId);
	}
	else
		glDisable(GL_TEXTURE_2D);

	glBegin(GL_TRIANGLES);
	for (vector<Triangle>::iterator triIt = triangles.begin(); triIt != triangles.end(); ++triIt) {
		Triangle tri = (*triIt);

		glNormal3f(tri.aN.x, tri.aN.y, tri.aN.z);
		glTexCoord2f(tri.s.x, tri.t.x);
		glVertex3f(tri.a.x, tri.a.y, tri.a.z);

		glNormal3f(tri.bN.x, tri.bN.y, tri.bN.z);
		glTexCoord2f(tri.s.y, tri.t.y);
		glVertex3f(tri.b.x, tri.b.y, tri.b.z);

		glNormal3f(tri.cN.x, tri.cN.y, tri.cN.z);
		glTexCoord2f(tri.s.z, tri.t.z);
		glVertex3f(tri.c.x, tri.c.y, tri.c.z);
	}
	glEnd();
}
