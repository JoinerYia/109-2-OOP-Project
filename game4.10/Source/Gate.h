#pragma once

#include <string>
#include <sstream>
#include "Shape.h"

namespace game_framework
{
	// 門物件
	class Gate
	{
	public:
		Gate();										// 設定動畫播放速度為 10(越大越慢)
		Gate(int DelayCount);						// 設定動畫播放速度的常數(越大越慢)
		~Gate();
		void LoadBitmapGate(string file, int n);	// 從路徑 "file(1 ~ n)" 新增 n 張圖形
		void OnMove();								// 門依頻率更換bitmap
		void OnShow();								// 門顯示
		void SetXY(int x, int y);					// 設定門左上角座標
		int GetX();									// 取得門 X 座標
		int GetY();									// 取得門 Y 座標
	private:
		RectangleF		 _shape;					// 門的中心座標及大小
		CAnimation		_Gate;						// 門動畫
	};
}