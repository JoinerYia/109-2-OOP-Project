#pragma once
#include <cmath>

class ShapeF
{

private:
	void Init(float x, float y);

protected:
	float _x, _y;

public:
	ShapeF();
	ShapeF(float x, float y);
	ShapeF(const ShapeF &shape);
	~ShapeF();

	float GetX() const;
	float GetY() const;
	void SetX(float value);
	void SetY(float value);

	void Offset(float dx, float dy);

	virtual bool isPointInside(float x, float y) const;
	virtual bool isLinePass(float m, float c) const;
	virtual bool isLinePass(float m, float c, float x1, float x2) const;
	bool isShapeFCover(ShapeF &shape) const;
	bool isShapeCoverWithDepart(ShapeF shape, int mode);

	virtual float GetMax(float vectorX, float vectorY) const;
	virtual float GetMin(float vectorX, float vectorY) const;

	virtual float GetLeft() const;
	virtual float GetRight() const;
	virtual float GetTop() const;
	virtual float GetBottom() const;
};

class CircleF :public ShapeF
{

private:
	float _radius;

	void Init(float x, float y, float radius);

public:
	CircleF();
	CircleF(float radius);
	CircleF(float x, float y);
	CircleF(float x, float y, float radius);
	CircleF(const CircleF &circle);

	float GetRadius() const;

	bool isPointInside(float x, float y) const override;
	bool isLinePass(float m, float c) const override;
	bool isLinePass(float m, float c, float x1, float x2) const override;
	//	bool isShapeFCover(ShapeF &shape) const override;

	float GetMax(float vectorX, float vectorY) const override;
	float GetMin(float vectorX, float vectorY) const override;

	float GetLeft() const override;
	float GetRight() const override;
	float GetTop() const override;
	float GetBottom() const override;
};

class RectangleF :public ShapeF
{

private:
	float _halfWidth, _halfHeight;

	void Init(float x, float y, float width, float height);

public:
	RectangleF();
	RectangleF(float width, float height);
	RectangleF(float x, float y, float width, float height);
	RectangleF(const RectangleF &rectangle);

	float GetWidth() const;
	float GetHeight() const;

	bool isPointInside(float x, float y) const override;
	bool isLinePass(float m, float c) const override;
	bool isLinePass(float m, float c, float x1, float x2) const override;
	//	bool isShapeFCover(ShapeF &shape) const override;

	float GetMax(float vectorX, float vectorY) const override;
	float GetMin(float vectorX, float vectorY) const override;

	float GetLeft() const override;
	float GetRight() const override;
	float GetTop() const override;
	float GetBottom() const override;
};
