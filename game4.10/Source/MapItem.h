#pragma once

#include "Shape.h"

class MapItem
{
protected:
	ShapeF _shape;
	int _type = 0;

public:
	void Offset(int dx, int dy);
	void SetXY(int x, int y);

	int GetX() const;
	int GetY() const;
	ShapeF GetShapeF();
};

