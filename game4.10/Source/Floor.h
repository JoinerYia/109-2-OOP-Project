#pragma once
#include "MapItem.h"
#include "Shape.h"
#include "GenerateBitmap.h"

namespace game_framework
{
	class Floor : public MapItem
	{

	private:
		CMovingBitmap _floor;					//地板
		int _x;
		int _y;
		int _width;
		int _height;
		void Init(int x, int y, int width, int height);

	public:
		Floor();
		Floor(int width, int height);
		Floor(int x, int y, int width, int height);
		~Floor();

		void LoadBitmapMonster(char* file);	// 從路徑 file 新增圖形
		//Offset 移動地板座標
		//SetXY 設定地板座標
		bool isCollision(ShapeF& shape);		//判斷是否碰到地板
		void OnShow();							// 地板顯示
	};
}