#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "MonsterJump.h"

namespace game_framework
{
	void MonsterJump::Init(int x, int y, int type)
	{
		_type = type;
		if (_type == 2)
			_shape = RectangleF(45, 60);
		else _shape = RectangleF(45, 50);				// 重設碰撞箱
		_shape.SetLeftTop((float)x, (float)y);			// 重設座標

		_isJumping = true;								// 預設一直跳躍
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
		Init(0, 0, 0);
	}

	MonsterJump::MonsterJump(int type)					// 設定怪物類別
	{
		Init(0, 0, type);
	}

	MonsterJump::~MonsterJump() {	}

	void MonsterJump::LoadBitmapMonster(string file)	// 從路徑 "file" 新增圖形
	{
		//讀取圖片
		stringstream fileString1;
		fileString1 << file << ".bmp";
		char* fileChar1 = new char[100];
		fileString1 >> fileChar1;
		_Monster.LoadBitmapA(fileChar1, RGB(255, 255, 255));				//設白色為透明
		delete[] fileChar1;
	}

	void MonsterJump::OnMove()												// 設定怪物座標
	{
		if (_type == 1 && _isJumping)
		{
			_type = 1;
		}
		
		if (!_isGrounded)
		{
			_speedY += _gravity;
			if (_speedY == 0)
				_speedY += 25 * _gravity / abs(_gravity);
		}
		else
		{
			_speedY = 0;
		}

		if (_isJumping)
		{
			if (_isGrounded)
			{
				//_speedY = 5;
				if (_gravity > 0)
					_speedY = -50;
				else _speedY = 50;
			}
		}
		//有往任意方向移動
		if (_isJumping || (!_isGrounded))
		{
			//移動的動畫
			_Monster.SetTopLeft(GetX(), GetY());
		}
		else
		{
			//站著不動的狀態
		}

		Offset(_speedX, _speedY);
	}

	void MonsterJump::OnShow()								// 怪物顯示
	{
		int x = GetX(), y = GetY();
		//顯示圖片
		_Monster.SetTopLeft(x, y);
		_Monster.ShowBitmap();
	}

	void MonsterJump::SetJumping(bool flag)					// 設定是否正在跳躍
	{
		_isJumping = flag;
	}

	void MonsterJump::SetGrounded(bool flag)
	{
		_isGrounded = flag;
	}

	void MonsterJump::ChangeGravity()								// 反轉重力
	{
		_gravity *= -1;
	}
}