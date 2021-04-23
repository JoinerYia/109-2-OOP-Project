#include "Entity.h"

void Entity::OnShow() {}
void Entity::OnMove() { Offset(_speedX, _speedY); }

void Entity::Offset(int dx, int dy) { _shape.Offset((float)dx, (float)dy); }
void Entity::SetXY(int x, int y) { _shape.Offset((float)(x - GetX()), (float)(y - GetY())); }

int Entity::GetX() { return (int)_shape.GetLeft(); }
int Entity::GetY() { return (int)_shape.GetTop(); }
ShapeF Entity::GetShape() { return _shape; }