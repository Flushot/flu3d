#pragma once

#include <vector>

class Rectangle {
public:
	Vector topLeft, topRight, bottomLeft, bottomRight;
	Rectangle() {}
	Rectangle(Vector topLeft, Vector topRight, Vector bottomLeft, Vector bottomRight) {
		this->topLeft = topLeft;
		this->topRight = topRight;
		this->bottomLeft = bottomLeft;
		this->bottomRight = bottomRight;
	}

	vector<Triangle> getFaces() const {
		vector<Triangle> faces;
		faces.push_back(new Triangle(topLeft, topRight, bottomLeft));
		faces.push_back(new Triangle(bottomLeft, topRight, bottomLeft));
		return faces;
	}
};
