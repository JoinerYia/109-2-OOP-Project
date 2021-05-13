#pragma once

#include "Shape.h"

class Entity
{
protected:
	ShapeF* _shape;
	int _speedX = 0, _speedY = 0;
	int _maxSpeed = 0, _acceleration = 0, _gravity = 0;
	int _type = 0;
public:

	virtual void LoadBitmapEntity();
	virtual void OnShow();
	virtual void OnMove();

	void Offset(int dx, int dy);
	void SetXY(int x, int y);
	virtual int isCollision(Entity entity);

	int GetX();
	int GetY();
	ShapeF* GetShape();
};

