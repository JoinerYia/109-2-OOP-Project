#pragma once

#include "Shape.h"

class Floor
{

private:

	RectangleF _shape;
	void Init(float x, float y, float width, float height);

public:
	Floor();
	Floor(float width, float height);
	Floor(float x, float y, float width, float height);
	~Floor();

	void Offset(float dx, float dy);
	void SetLeftTop(float x, float y);
	bool isCollision(ShapeF &shape) const;

};