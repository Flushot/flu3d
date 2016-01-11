#pragma once

#include "Vector.h"

class Triangle {
public:
	Vector a, b, c;
	Vector s, t; // tex coords
	//float s[3], t[3]; // tex coords
	Vector aN, bN, cN; // normals

	Triangle() {}
	Triangle(Vector a, Vector b, Vector c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}
	Triangle(Vector a, Vector b, Vector c, Vector aN, Vector bN, Vector cN) {
		this->a = a;
		this->b = b;
		this->c = c;
		this->aN = aN;
		this->bN = bN;
		this->cN = cN;
	}
};
