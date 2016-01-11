#pragma once

#include "Color.h"

class Vector {
private:
	bool _hasColor;
	Color _color;

public:
	float x, y, z;
	int boneId; // skel model bone id

	Vector() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		_hasColor = false;
	}

	// 3d vector
	Vector(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
		_hasColor = false;
	}
	Vector(float x, float y, float z, const Color &color) {
		this->x = x;
		this->y = y;
		this->z = z;
		setColor(color);
	}

	// 2d vector
	/*
	Vector(float x, float y) {
		Vector(x, y, 0.0f);
		_hasColor = false;
	}
	Vector(float x, float y, const Color &color) {
		Vector(x, y);
		setColor(color);
	}
	*/

	void clearColor() {
		_hasColor = false;
	}
	bool hasColor() const { return _hasColor; }
	Color getColor() const { return _color; }
	void setColor(const Color &color) {
		_color = color;
		_hasColor = true;
	}

	/*
	Vector &operator +(const Vector &v) {
		return Vector(x + v.x, y + v.y, z + v.z);
	}
	*/
};