#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "MonsterJump.h"

namespace game_framework
{
	void MonsterJump::Init(int x, int y)
	{
		_shape = new CircleF(31);						// 重設碰撞箱
		_shape->SetLeftTop((float)x, (float)y);			// 重設座標
		_yCenter = SIZE_Y / 2;

		_isGrounded = true;								// 初始化落地狀態
		//_Monster_left.SetTopLeft(x, y);

		_maxSpeed = 20;									// 初始化最高速度
		_speedX = 0;									// 初始化水平速度
		_speedY = 0;									// 初始化垂直速度
		_acceleration = 5;								// 初始化加速度
		_gravity = 3;									// 初始化重力加速度
	}

	MonsterJump::MonsterJump()							// 預設設定
	{
		Init(0, 0);
	}

	MonsterJump::MonsterJump(int x, int y)	// 設定怪物類別
	{
		Init(x, y);
	}

	MonsterJump::~MonsterJump() {	}

	void MonsterJump::LoadBitmapMonster(string file)	// 從路徑 "file" 新增圖形
	{
		//讀取圖片
		stringstream fileString1, fileString2;
		fileString1 << file << ".bmp";
		char* fileChar1 = new char[100];
		fileString1 >> fileChar1;
		_Monster.LoadBitmapA(fileChar1, RGB(255, 255, 255));				//設白色為透明
		fileString2 << file << "_ball.bmp";
		char* fileChar2 = new char[100];
		fileString2 >> fileChar2;
		_MonsterBall.LoadBitmapA(fileChar2, RGB(0, 0, 0));					//設黑色為透明
		delete[] fileChar1;
		delete[] fileChar2;
	}

	void MonsterJump::OnMove()												// 設定怪物座標
	{
		_isGrounded = GetY() > SIZE_Y / 2 - 15;
		if (_isGrounded)
		{
			//_speedY = 5;
			if (_gravity > 0)
				_speedY = -50;
			else _speedY = 50;
		}
		else
		{
			_speedY += _gravity;
		}
		//移動的動畫
		_Monster.SetTopLeft(_shape->GetX(), _shape->GetY());
		_MonsterBall.SetTopLeft(_shape->GetX(), SIZE_Y - _shape->GetY() + _MonsterBall.Height());

		_shape->Offset((float)_speedX, (float)_speedY);
	}

	void MonsterJump::OnShow()								// 怪物顯示
	{
		int x = _shape->GetX(), y = _shape->GetY();
		//顯示圖片
		_Monster.SetTopLeft(x, y);
		_Monster.ShowBitmap();
		_MonsterBall.SetTopLeft(x, SIZE_Y - y + _MonsterBall.Height());
		_MonsterBall.ShowBitmap();
	}

	void MonsterJump::SetGrounded(bool flag)
	{
		_isGrounded = flag;
	}
}