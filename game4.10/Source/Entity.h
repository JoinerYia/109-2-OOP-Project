#pragma once

#include "Shape.h"

class Entity
{
protected:
	ShapeF _shape;
	int _speedX, _speedY;
	int _maxSpeed, _acceleration, _gravity;
	int _type = 0;
public:

	virtual void OnShow();
	virtual void OnMove();

	void Offset(int dx, int dy);
	void SetXY(int x, int y);

	int GetX();
	int GetY();
	ShapeF& GetShape();
};

