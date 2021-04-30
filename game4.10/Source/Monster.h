#pragma once

#include <string>
#include <sstream>
#include "Shape.h"
#include "Entity.h"

namespace game_framework
{
	// 玩家物件
	class Monster
	{
	protected:
		void LoadBitmapMonster(string file, int n);	// 從路徑 "file(1 ~ n)" 新增 n 張圖形
		void Offset(int dx, int dy);
		void SetXY(int x, int y);
		int GetX();
		int GetY();
		virtual void OnMove();						// 玩家依頻率更換bitmap
		virtual void OnShow();						// 玩家顯示

		RectangleF		 _shape;					// 玩家的中心座標及大小
		CMovingBitmap	_monster;					// 玩家動畫
	};
}