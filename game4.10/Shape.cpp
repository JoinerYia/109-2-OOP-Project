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

#pragma region Shape

void Shape::Init(float x, float y) {
	_x = x;
	_y = y;
}

Shape::Shape() { Init(0, 0); }
Shape::Shape(float x, float y) { Init(x, y); }
Shape::Shape(const Shape &shape) { Init(shape._x, shape._y); }
Shape::~Shape() {}

float Shape::GetX() const { return _x; }
float Shape::GetY() const { return _y; }
void Shape::SetX(float value) { _x = value; }
void Shape::SetY(float value) { _y = value; }

void Shape::Offset(float dx, float dy) {
	_x += dx;
	_y += dy;
}

bool Shape::isPointInside(float x, float y) const {
	return distanceToPoint(_x, _y, x, y) == 0;
}

bool Shape::isLinePass(float m, float c) const {
	return distanceToLine(_x, _y, m, c) == 0;
}

bool Shape::isLinePass(float m, float c, float x1, float x2) const {
	float y1 = m * x1 + c,
		y2 = m * x2 + c;
	if ((!isValueBetween(_x, x1, x2)) || (!isValueBetween(_y, y1, y2))) return false;
	return isLinePass(m, c);
}

bool Shape::isShapeCover(Shape &shape)const {
	/*
	float dx = shape._x - this->_x,
		dy = shape._y - this->_y;
	return this->GetMin(dx, dy) < shape.GetMax(dx, dy) && shape.GetMin(dx, dy) < this->GetMax(dx, dy);
	//*/
	bool checkX = this->GetLeft() < shape.GetRight() && shape.GetLeft() < this->GetRight(),
		checkY = this->GetTop() < shape.GetBottom() && shape.GetTop() < this->GetBottom();
	return checkX && checkY;
}

float Shape::GetMax(float vectorX, float vectorY) const {
	float temp = _x * vectorX + _y * vectorY;
	float len = sqrt(vectorX*vectorX + vectorY * vectorY);
	return temp / len;
}

float Shape::GetMin(float vectorX, float vectorY) const {
	float temp = _x * vectorX + _y * vectorY;
	float len = sqrt(vectorX*vectorX + vectorY * vectorY);
	return temp / len;
}

float Shape::GetLeft() const { return _x; }
float Shape::GetRight() const { return _x; }
float Shape::GetTop() const { return _y; }
float Shape::GetBottom() const { return _y; }

#pragma endregion

#pragma region Circle

void Circle::Init(float x, float y, float radius) {
	_x = x;
	_y = y;
	_radius = radius;
}

Circle::Circle() { Init(0, 0, 0); }
Circle::Circle(float radius) { Init(0, 0, radius); }
Circle::Circle(float x, float y) { Init(x, y, 0); }
Circle::Circle(float x, float y, float radius) { Init(x, y, radius); };
Circle::Circle(const Circle &Circle) { Init(Circle._x, Circle._y, Circle._radius); }

bool Circle::isPointInside(float x, float y) const {
	return distanceToPoint(_x, _y, x, y) <= _radius;
}

bool Circle::isLinePass(float m, float c) const {
	return distanceToLine(_x, _y, m, c) <= _radius;
}

bool Circle::isLinePass(float m, float c, float x1, float x2) const {
	float y1 = m * x1 + c,
		y2 = m * x2 + c;
	if (isPointInside(x1, y1) || isPointInside(x1, y1)) return true;
	if (!isLinePass(m, c)) return false;

	float closestX = -c + _x / m + _y;
	closestX /= m + 1 / m;

	return isValueBetween(closestX, x1, x2);
}

//bool Circle::isShapeCover(Shape &shape) const;

float Circle::GetMax(float vectorX, float vectorY) const {
	float temp = _x * vectorX + _y * vectorY;
	float len = sqrt(vectorX*vectorX + vectorY * vectorY);
	return temp / len + _radius;
}

float Circle::GetMin(float vectorX, float vectorY) const {
	float temp = _x * vectorX + _y * vectorY;
	float len = sqrt(vectorX*vectorX + vectorY * vectorY);
	return temp / len - _radius;
}

float Circle::GetLeft() const { return _x - _radius; }
float Circle::GetRight() const { return _x + _radius; }
float Circle::GetTop() const { return _y - _radius; }
float Circle::GetBottom() const { return _y + _radius; }

#pragma endregion

#pragma region Rectangle

void Rectangle::Init(float x, float y, float width, float height) {
	_x = x;
	_y = y;
	_halfWidth = width / 2;
	_halfHeight = height / 2;
}

Rectangle::Rectangle() { Init(0, 0, 0, 0); }
Rectangle::Rectangle(float width, float height) { Init(0, 0, width, height); }
Rectangle::Rectangle(float x, float y, float width, float height) { Init(x, y, width, height); }
Rectangle::Rectangle(const Rectangle &rectangle) { Init(rectangle._x, rectangle._y, rectangle._halfWidth * 2, rectangle._halfHeight * 2); }

bool Rectangle::isPointInside(float x, float y) const {
	return abs(x - _x) <= _halfWidth && abs(y - _y) <= _halfWidth;
}

bool Rectangle::isLinePass(float m, float c) const {
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

bool Rectangle::isLinePass(float m, float c, float x1, float x2) const {
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

//bool Circle::isShapeCover(Shape &shape) const;

float Rectangle::GetMax(float vectorX, float vectorY) const {
	float max = GetLeft() * vectorX + GetTop() * vectorY, temp;

	temp = GetRight() * vectorX + GetTop() * vectorY;
	if (max < temp) max = temp;

	temp = GetLeft() * vectorX + GetBottom() * vectorY;
	if (max < temp) max = temp;

	temp = GetRight() * vectorX + GetBottom() * vectorY;
	if (max < temp) max = temp;

	return max / sqrt(vectorX * vectorX + vectorY * vectorY);
}

float Rectangle::GetMin(float vectorX, float vectorY) const {
	float min = GetLeft() * vectorX + GetTop() * vectorY, temp;

	temp = GetRight() * vectorX + GetTop() * vectorY;
	if (min > temp) min = temp;

	temp = GetLeft() * vectorX + GetBottom() * vectorY;
	if (min > temp) min = temp;

	temp = GetRight() * vectorX + GetBottom() * vectorY;
	if (min > temp) min = temp;

	return min / sqrt(vectorX * vectorX + vectorY * vectorY);
}

float Rectangle::GetLeft() const { return _x - _halfWidth; }
float Rectangle::GetRight() const { return _x + _halfWidth; }
float Rectangle::GetTop() const { return _y - _halfHeight; }
float Rectangle::GetBottom() const { return _y + _halfHeight; }

#pragma endregion
