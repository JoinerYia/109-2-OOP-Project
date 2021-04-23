#include "Shape.h"



float distanceToPoint(float x1, float y1, float x2, float y2) {
	float dx = x2 - x1, dy = y2 - y1;
	return sqrt(dx*dx + dy * dy);
}

float distanceToLine(float x, float y, float m, float c) {
	float distance = m * x - y + c;
	distance /= (m*m + 1);
	if (distance < 0) distance = -1;
	return distance;
}

bool isValueBetween(float value, float limit1, float limit2) {
	return (value - limit1)*(value - limit2) < 0;
}

float abs(float number) {
	if (number < 0)
		return -number;
	else return number;
}

#pragma region ShapeF

void ShapeF::Init(float x, float y) {
	_x = x;
	_y = y;
}

ShapeF::ShapeF() { Init(0, 0); }
ShapeF::ShapeF(float x, float y) { Init(x, y); }
ShapeF::ShapeF(const ShapeF &shape) { Init(shape._x, shape._y); }
ShapeF::~ShapeF() {}

float ShapeF::GetX() const { return _x; }
float ShapeF::GetY() const { return _y; }
void ShapeF::SetX(float value) { _x = value; }
void ShapeF::SetY(float value) { _y = value; }

void ShapeF::Offset(float dx, float dy) {
	_x += dx;
	_y += dy;
}

bool ShapeF::isPointInside(float x, float y) const {
	return distanceToPoint(_x, _y, x, y) == 0;
}

bool ShapeF::isLinePass(float m, float c) const {
	return distanceToLine(_x, _y, m, c) == 0;
}

bool ShapeF::isLinePass(float m, float c, float x1, float x2) const {
	float y1 = m * x1 + c,
		y2 = m * x2 + c;
	if ((!isValueBetween(_x, x1, x2)) || (!isValueBetween(_y, y1, y2))) return false;
	return isLinePass(m, c);
}

bool ShapeF::isShapeFCover(ShapeF &shape)const {
	/*
	float dx = shape._x - this->_x,
		dy = shape._y - this->_y;
	return this->GetMin(dx, dy) < shape.GetMax(dx, dy) && shape.GetMin(dx, dy) < this->GetMax(dx, dy);
	//*/
	bool checkX = this->GetLeft() < shape.GetRight() && shape.GetLeft() < this->GetRight(),
		checkY = this->GetTop() < shape.GetBottom() && shape.GetTop() < this->GetBottom();
	return checkX && checkY;
}

bool ShapeF::isShapeCoverWithDepart(ShapeF shape, int mode) {
	bool checkX = this->GetLeft() < shape.GetRight() && shape.GetLeft() < this->GetRight(),
		checkY = this->GetTop() < shape.GetBottom() && shape.GetTop() < this->GetBottom(),
		check = checkX && checkY;

	if (check)
	{
		float dx, dy;

		if (abs(shape.GetRight() - this->GetLeft()) < abs(shape.GetLeft() - this->GetRight()))
			dx = shape.GetRight() - this->GetLeft();
		else dx = shape.GetLeft() - this->GetRight();

		if (abs(shape.GetBottom() - this->GetTop()) < abs(shape.GetTop() - this->GetBottom()))
			dy = shape.GetBottom() - this->GetTop();
		else dy = shape.GetTop() - this->GetBottom();

		dx -= dx / abs(dx);
		dy -= dy / abs(dy);

		switch (mode)
		{
		case 1:
			if (abs(dx) < abs(dy))
				this->Offset(dx, 0);
			else this->Offset(0, dy);
			break;
		case 2:
			if (abs(dx) < abs(dy))
				shape.Offset(-dx, 0);
			else shape.Offset(0, -dy);
			break;
		case 3:
			if (abs(dx) < abs(dy))
			{
				this->Offset(dx / 2, 0);
				shape.Offset(-dx / 2, 0);
			}
			else
			{
				this->Offset(0, dy / 2);
				shape.Offset(0, -dy / 2);
			}
			break;
		default:
			break;
		}
	}

	return check;
}

float ShapeF::GetMax(float vectorX, float vectorY) const {
	float temp = _x * vectorX + _y * vectorY;
	float len = sqrt(vectorX*vectorX + vectorY * vectorY);
	return temp / len;
}

float ShapeF::GetMin(float vectorX, float vectorY) const {
	float temp = _x * vectorX + _y * vectorY;
	float len = sqrt(vectorX*vectorX + vectorY * vectorY);
	return temp / len;
}

float ShapeF::GetLeft() const { return _x; }
float ShapeF::GetRight() const { return _x; }
float ShapeF::GetTop() const { return _y; }
float ShapeF::GetBottom() const { return _y; }

#pragma endregion

#pragma region CircleF

void CircleF::Init(float x, float y, float radius) {
	_x = x;
	_y = y;
	_radius = radius;
}

CircleF::CircleF() { Init(0, 0, 0); }
CircleF::CircleF(float radius) { Init(0, 0, radius); }
CircleF::CircleF(float x, float y) { Init(x, y, 0); }
CircleF::CircleF(float x, float y, float radius) { Init(x, y, radius); };
CircleF::CircleF(const CircleF &circle) { Init(circle._x, circle._y, circle._radius); }

float CircleF::GetRadius() const { return _radius; }

bool CircleF::isPointInside(float x, float y) const {
	return distanceToPoint(_x, _y, x, y) <= _radius;
}

bool CircleF::isLinePass(float m, float c) const {
	return distanceToLine(_x, _y, m, c) <= _radius;
}

bool CircleF::isLinePass(float m, float c, float x1, float x2) const {
	float y1 = m * x1 + c,
		y2 = m * x2 + c;
	if (isPointInside(x1, y1) || isPointInside(x1, y1)) return true;
	if (!isLinePass(m, c)) return false;

	float closestX = -c + _x / m + _y;
	closestX /= m + 1 / m;

	return isValueBetween(closestX, x1, x2);
}

//bool CircleF::isShapeFCover(ShapeF &shape) const;

float CircleF::GetMax(float vectorX, float vectorY) const {
	float temp = _x * vectorX + _y * vectorY;
	float len = sqrt(vectorX*vectorX + vectorY * vectorY);
	return temp / len + _radius;
}

float CircleF::GetMin(float vectorX, float vectorY) const {
	float temp = _x * vectorX + _y * vectorY;
	float len = sqrt(vectorX*vectorX + vectorY * vectorY);
	return temp / len - _radius;
}

float CircleF::GetLeft() const { return _x - _radius; }
float CircleF::GetRight() const { return _x + _radius; }
float CircleF::GetTop() const { return _y - _radius; }
float CircleF::GetBottom() const { return _y + _radius; }

#pragma endregion

#pragma region RectangleF

void RectangleF::Init(float x, float y, float width, float height) {
	_x = x;
	_y = y;
	_halfWidth = width / 2;
	_halfHeight = height / 2;
}

RectangleF::RectangleF() { Init(0, 0, 0, 0); }
RectangleF::RectangleF(float width, float height) { Init(0, 0, width, height); }
RectangleF::RectangleF(float x, float y, float width, float height) { Init(x, y, width, height); }
RectangleF::RectangleF(const RectangleF &rectangle) { Init(rectangle._x, rectangle._y, rectangle._halfWidth * 2, rectangle._halfHeight * 2); }

float RectangleF::GetWidth() const { return _halfWidth * 2; }
float RectangleF::GetHeight() const { return _halfHeight * 2; }

bool RectangleF::isPointInside(float x, float y) const {
	return abs(x - _x) <= _halfWidth && abs(y - _y) <= _halfWidth;
}

bool RectangleF::isLinePass(float m, float c) const {
	//mx-y+c=0
	float xUpper, xLower, yLeft, yRight;

	xUpper = (_y - _halfHeight - c) / m;
	if (isValueBetween(xUpper, _x - _halfWidth, _x + _halfWidth)) return true;
	xLower = (_y + _halfHeight - c) / m;
	if (isValueBetween(xLower, _x - _halfWidth, _x + _halfWidth)) return true;

	yLeft = m * (_x - _halfWidth) + c;
	if (isValueBetween(yLeft, _y - _halfHeight, _y + _halfHeight)) return true;
	yRight = m * (_x + _halfWidth) + c;
	if (isValueBetween(yRight, _y - _halfHeight, _y + _halfHeight)) return true;

	return false;
}

bool RectangleF::isLinePass(float m, float c, float x1, float x2) const {
	float y1 = m * x1 + c, y2 = m * x2 + c;
	if (isPointInside(x1, y1) || isPointInside(x2, y2)) return true;

	float xUpper, xLower, yLeft, yRight;

	xUpper = (_y - _halfHeight - c) / m;
	if (isValueBetween(xUpper, _x - _halfWidth, _x + _halfWidth) &&
		isValueBetween(xUpper, x1, x2)) return true;
	xLower = (_y + _halfHeight - c) / m;
	if (isValueBetween(xLower, _x - _halfWidth, _x + _halfWidth) &&
		isValueBetween(xLower, x1, x2)) return true;

	yLeft = m * (_x - _halfWidth) + c;
	if (isValueBetween(yLeft, _y - _halfHeight, _y + _halfHeight) &&
		isValueBetween(yLeft, y1, y2)) return true;
	yRight = m * (_x + _halfWidth) + c;
	if (isValueBetween(yRight, _y - _halfHeight, _y + _halfHeight) &&
		isValueBetween(yRight, y1, y2)) return true;

	return false;
}

//bool CircleF::isShapeFCover(ShapeF &ShapeF) const;

float RectangleF::GetMax(float vectorX, float vectorY) const {
	float max = GetLeft() * vectorX + GetTop() * vectorY, temp;

	temp = GetRight() * vectorX + GetTop() * vectorY;
	if (max < temp) max = temp;

	temp = GetLeft() * vectorX + GetBottom() * vectorY;
	if (max < temp) max = temp;

	temp = GetRight() * vectorX + GetBottom() * vectorY;
	if (max < temp) max = temp;

	return max / sqrt(vectorX * vectorX + vectorY * vectorY);
}

float RectangleF::GetMin(float vectorX, float vectorY) const {
	float min = GetLeft() * vectorX + GetTop() * vectorY, temp;

	temp = GetRight() * vectorX + GetTop() * vectorY;
	if (min > temp) min = temp;

	temp = GetLeft() * vectorX + GetBottom() * vectorY;
	if (min > temp) min = temp;

	temp = GetRight() * vectorX + GetBottom() * vectorY;
	if (min > temp) min = temp;

	return min / sqrt(vectorX * vectorX + vectorY * vectorY);
}

float RectangleF::GetLeft() const { return _x - _halfWidth; }
float RectangleF::GetRight() const { return _x + _halfWidth; }
float RectangleF::GetTop() const { return _y - _halfHeight; }
float RectangleF::GetBottom() const { return _y + _halfHeight; }

#pragma endregion


