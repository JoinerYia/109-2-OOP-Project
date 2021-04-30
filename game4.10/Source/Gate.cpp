#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Gate.h"

namespace game_framework
{
	void Gate::Init(int x, int y, int width, int height, int DelayCount)
	{
		_type = 0;
		_shape = RectangleF((float)width, (float)height);				//重設碰撞箱
		_shape.SetLeftTop((float)x, (float)y);			//重設座標
		_Gate.SetDelayCount(DelayCount);				//預設值
	}

	Gate::Gate()										// 設定動畫播放速度為 10(越大越慢)
	{
		Init(0, 0, 210, 60, 10);
	}

	Gate::Gate(int DelayCount)							// 設定動畫播放速度的常數(越大越慢)
	{
		Init(0, 0, 210, 60, DelayCount);
	}

	Gate::~Gate() {	}

	void Gate::LoadBitmapGate(string file, int n)		// 從路徑 "file(1 ~ n)" 新增 n 張圖形
	{
		for (int i = 1; i <= n; i++)
		{
			//讀取動畫圖片
			stringstream fileString1;
			fileString1 << file << i << ".bmp";
			char* fileChar1 = new char[100];
			fileString1 >> fileChar1;
			_Gate.AddBitmap(fileChar1, RGB(255, 255, 255));				//設白色為透明
		}
	}

	void Gate::OnMove()									// 門依頻率更換bitmap
	{
		_Gate.OnMove();
	}

	void Gate::OnShow()									// 門顯示
	{
		//顯示動畫
		_Gate.SetTopLeft(GetX(), GetY());
		_Gate.OnShow();
	}

	bool Gate::isCollision(Entity entity)
	{
		return _shape.isShapeFCover(entity.GetShape());
	}
}