#pragma once

class Color {
public:
	float r, g, b, a;

	Color() {
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 0.0f;
	}
	Color(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 0.0f;
	}
	Color(float r, float g, float b, float a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};
