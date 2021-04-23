#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Floor.h"

namespace game_framework
{
	void Floor::Init(float x, float y, float width, float height) {
		_shape = RectangleF(x + width / 2, y + height / 2, width, height);
	}

	Floor::Floor() { Init(0, 0, 0, 0); }
	Floor::Floor(float width, float height) { Init(0, 0, width, height); }
	Floor::Floor(float x, float y, float width, float height) { Init(x, y, width, height); }
	Floor::~Floor() {}

	bool Floor::isCollision(ShapeF& shape) { return _shape.isShapeCoverWithDepart(shape, 2); }
	void Floor::OnShow()				// ¦aªOÅã¥Ü
	{

	}
}