#pragma once

#include <string>
#include <sstream>
#include "MapItem.h"
#include "Entity.h"

namespace game_framework
{
	// 門物件
	class Gate : public MapItem
	{
	public:
		Gate();										// 設定動畫播放速度為 10(越大越慢)
		Gate(int DelayCount);						// 設定動畫播放速度的常數(越大越慢)
		~Gate();
		void LoadBitmapGate(string file, int n);	// 從路徑 "file(1 ~ n)" 新增 n 張圖形
		void OnMove();								// 門依頻率更換bitmap
		void OnShow();								// 門顯示
		bool isCollision(Entity entity);			// 判斷
		// Offset(int dx, dint y);					// 移動門座標
		// SetXY(int x, int y);						// 設定門左上角座標
		// GetX();									// 取得門 X 座標
		// GetY();									// 取得門 Y 座標
	private:
		//				_shape;						// 門的中心座標及大小
		CAnimation		_Gate;						// 門動畫
		void Init(int x, int y, int width, int height, int DelayCount);//初始化設定
	};
}