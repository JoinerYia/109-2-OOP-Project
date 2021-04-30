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

	Floor::Floor() { Init(0, 0, 10, 10); }
	Floor::Floor(int width, int height) { Init(0, 0, width, height); }
	Floor::Floor(int x, int y, int width, int height) { Init(x, y, width, height); }
	Floor::~Floor() {}

	void Floor::LoadBitmapMonster(char* file)
	{
		//GenerateBitmap generateBmp = GenerateBitmap();
		//generateBmp.CreateBitmapFile(file, _width, _height);
		_floor.LoadBitmapA(file);
		_floor.SetTopLeft(_x, _y);
	}
	bool Floor::isCollision(ShapeF& shape) { return _shape.isShapeCoverWithDepart(shape, 2); }
	void Floor::OnShow()				// ¦aªOÅã¥Ü
	{
		//_floor.ShowBitmap();
	}
}