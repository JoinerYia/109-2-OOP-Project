#pragma once

#include "Shape.h"

namespace game_framework
{
	class Floor
	{

	private:

		RectangleF _shape;							// 地板的中心座標及大小
		void Init(float x, float y, float width, float height);

	public:
		Floor();
		Floor(float width, float height);
		Floor(float x, float y, float width, float height);
		~Floor();

		void Offset(float dx, float dy);
		void SetLeftTop(float x, float y);
		bool isCollision(ShapeF& shape) const;
		void OnShow();								// 地板顯示
	};
}