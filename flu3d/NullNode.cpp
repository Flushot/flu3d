#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "NullNode.h"
#include "Exceptions.h"
#include "Log/Log.h"
using namespace std;

NullNode::~NullNode() {
}

void NullNode::bake() {
	Log::debug("Baking NullNode");
}

void NullNode::render() {
	//Log::debug("Rendering NullNode");
	glPushMatrix();
	matrixTransform();
	renderChildren();
}