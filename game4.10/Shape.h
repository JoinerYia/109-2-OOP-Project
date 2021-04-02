#pragma once
#include <cmath>

class Shape
{

private:
	void Init(float x, float y);

protected:
	float _x, _y;

public:
	Shape();
	Shape(float x, float y);
	Shape(const Shape &shape);
	~Shape();

	float GetX() const;
	float GetY() const;
	void SetX(float value);
	void SetY(float value);

	void Offset(float dx, float dy);

	virtual bool isPointInside(float x, float y) const;
	virtual bool isLinePass(float m, float c) const;
	virtual bool isLinePass(float m, float c, float x1, float x2) const;
	virtual bool isShapeCover(Shape &shape) const;

	virtual float GetMax(float vectorX, float vectorY) const;
	virtual float GetMin(float vectorX, float vectorY) const;

	virtual float GetLeft() const;
	virtual float GetRight() const;
	virtual float GetTop() const;
	virtual float GetBottom() const;
};

class Circle :public Shape
{

private:
	float _radius;

	void Init(float x, float y, float radius);

public:
	Circle();
	Circle(float radius);
	Circle(float x, float y);
	Circle(float x, float y, float radius);
	Circle(const Circle &Circle);

	bool isPointInside(float x, float y) const override;
	bool isLinePass(float m, float c) const override;
	bool isLinePass(float m, float c, float x1, float x2) const override;
//	bool isShapeCover(Shape &shape) const override;

	float GetMax(float vectorX, float vectorY) const override;
	float GetMin(float vectorX, float vectorY) const override;

	float GetLeft() const override;
	float GetRight() const override;
	float GetTop() const override;
	float GetBottom() const override;
};

class Rectangle :public Shape
{

private:
	float _halfWidth, _halfHeight;

	void Init(float x, float y, float width, float height);

public:
	Rectangle();
	Rectangle(float width, float height);
	Rectangle(float x, float y, float width, float height);
	Rectangle(const Rectangle &Rectangle);


	bool isPointInside(float x, float y) const override;
	bool isLinePass(float m, float c) const override;
	bool isLinePass(float m, float c, float x1, float x2) const override;
//	bool isShapeCover(Shape &shape) const override;

	float GetMax(float vectorX, float vectorY) const override;
	float GetMin(float vectorX, float vectorY) const override;

	float GetLeft() const override;
	float GetRight() const override;
	float GetTop() const override;
	float GetBottom() const override;
};
