#pragma once

#include "Material.h"
#include "Triangle.h"
#include <vector>

class Mesh {
public:
	Material material;
	std::vector<Triangle> triangles;

	void bake();
	void render();
};
