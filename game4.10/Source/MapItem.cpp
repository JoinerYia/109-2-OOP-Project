#pragma once

#include "MapItem.h"

void MapItem::Offset(int dx, int dy) {
	_shape.Offset((float)dx, (float)dy);
}

void MapItem::SetXY(int x, int y) {
	_shape.Offset((float)(x - GetX()), (float)(y - GetY()));
}

int MapItem::GetX() const { return (int)_shape.GetLeft(); }
int MapItem::GetY() const { return (int)_shape.GetTop(); }
ShapeF MapItem::GetShapeF() { return _shape; }