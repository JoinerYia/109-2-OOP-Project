#include "Floor.h"


void Floor::Init(float x, float y, float width, float height) {
	_shape = RectangleF(x + width / 2, y + height / 2, width, height);
}

Floor::Floor() { Init(0, 0, 0, 0); }
Floor::Floor(float width, float height) { Init(0, 0, width, height); }
Floor::Floor(float x, float y, float width, float height) { Init(x, y, width, height); }
Floor::~Floor() {}

void Floor::Offset(float dx, float dy) { _shape.Offset(dx, dy); }
void Floor::SetLeftTop(float x, float y) { _shape.Offset(x - _shape.GetLeft(), y - _shape.GetTop()); }
bool Floor::isCollision(ShapeF &shape) const { return _shape.isShapeFCover(shape); }