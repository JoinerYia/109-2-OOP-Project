#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Floor.h"

namespace game_framework
{
	void Floor::Init(int x, int y, int width, int height) {
		_shape = RectangleF((float)(x + width / 2), (float)(y + height / 2), (float)width, (float)height);
		_x = x;
		_y = y;
		_width = width;
		_height = height;
	}

	Floor::Floor() { Init(0, 0, 0, 0); }
	Floor::Floor(int width, int height) { Init(0, 0, width, height); }
	Floor::Floor(int x, int y, int width, int height) { Init(x, y, width, height); }
	Floor::~Floor() {}

	void Floor::LoadBitmapPlayer(char* file)
	{
		//GenerateBitmap generateBmp = GenerateBitmap();
		//generateBmp.CreateBitmapFile(file, _width, _height);
		//_floor.LoadBitmapA(file);
		//_floor.SetTopLeft(_x, _y);
	}
	bool Floor::isCollision(ShapeF& shape) {
		float x1 = shape.GetLeft(), y1 = shape.GetTop(),
			x2 = shape.GetRight(), y2 = shape.GetBottom();
		return _shape.isShapeCoverWithDepart(shape, 2);
	}
	void Floor::OnShow()				// ¦aªOÅã¥Ü
	{
		CDC* myDC = CDDraw::GetBackCDC();
		myDC->SelectObject(GetStockObject(BLACK_BRUSH));
		//myDC->SelectObject(GetStock)
		myDC->Rectangle((int)_shape.GetLeft(), (int)_shape.GetTop(), (int)_shape.GetRight(), (int)_shape.GetBottom());
		CDDraw::ReleaseBackCDC();
	}

	void Floor::Offset(int dx, int dy) {
		_shape.Offset((float)dx, (float)dy);
	}

	void Floor::SetXY(int x, int y) {
		_shape.Offset((float)(x - GetX()), (float)(y - GetY()));
	}

	int Floor::GetX() const { return (int)_shape.GetLeft(); }
	int Floor::GetY() const { return (int)_shape.GetTop(); }
	ShapeF Floor::GetShapeF() { return _shape; }
}