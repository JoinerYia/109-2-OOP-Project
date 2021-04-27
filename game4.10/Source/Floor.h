#pragma once
#include "MapItem.h"
#include "Shape.h"

namespace game_framework
{
	class Floor : public MapItem
	{

	private:

		void Init(float x, float y, float width, float height);

	public:
		Floor();
		Floor(float width, float height);
		Floor(float x, float y, float width, float height);
		~Floor();

		//Offset 移動地板座標
		//SetXY 設定地板座標
		bool isCollision(ShapeF& shape);		//判斷是否碰到地板
		void OnShow();								// 地板顯示
	};
}