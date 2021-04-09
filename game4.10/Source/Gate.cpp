#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Gate.h"

namespace game_framework
{
	Gate::Gate()										// 設定動畫播放速度為 10(越大越慢)
	{
		_shape = RectangleF(210, 60);					//重設座標
		_Gate.SetDelayCount(10);
	}

	Gate::Gate(int DelayCount)							// 設定動畫播放速度的常數(越大越慢)
	{
		_shape = RectangleF(210, 60);					//重設座標
		_Gate.SetDelayCount(DelayCount);
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

	void Gate::SetXY(int x, int y)						// 設定門左上角座標
	{
		_shape.Offset((float)(x - GetX()), (float)(y - GetY()));
	}

	int Gate::GetX()									// 取得門 X 座標
	{
		return (int)_shape.GetLeft();
	}

	int Gate::GetY()									// 取得門 Y 座標
	{
		return (int)_shape.GetTop();
	}
}