#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "MonsterJump.h"

namespace game_framework
{
	void MonsterJump::Init(int x, int y, int DelayCount)
	{
		_shape.SetLeftTop((float)x, (float)y);			//重設座標

		_isJumping = false;//初始化移動方向
		_isGrounded = true;								//初始化落地狀態
		_monster.SetDelayCount(DelayCount);			//預設值
		//_MonsterJump.SetTopLeft(x, y);

		_maxSpeed = 20;									//初始化最高速度
		_speedX = 0;									//初始化水平速度
		_speedY = 0;									//初始化垂直速度
		_acceleration = 5;								//初始化加速度
		_gravity = 5;									//初始化重力加速度
	}

	MonsterJump::MonsterJump()									// 設定動畫播放速度為 10(越大越慢)
	{
		Init(0, 0, 0, 10);
	}

	MonsterJump::MonsterJump(int type)							// 設定動畫播放速度的常數(越大越慢)
	{
		Init(0, 0, type, 3);
	}

	MonsterJump::MonsterJump(int type, int DelayCount)			// 設定動畫播放速度的常數(越大越慢)
	{
		Init(0, 0, type, DelayCount);
	}

	MonsterJump::~MonsterJump() {	}

	void MonsterJump::OnMove()														// 玩家依頻率更換bitmap
	{
		if (!_isGrounded)
		{
			if (!_isPassed)
				_speedY += _gravity;
			else if (_speedY == 0)
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
		//移動的動畫
		_monster.OnMove();

		Offset(_speedX, _speedY);
	}

	void MonsterJump::OnShow()								// 玩家顯示
	{
		int x = GetX(), y = GetY();
		_monster.SetTopLeft(GetX(), GetY());
		_monster.OnShow();
	}

	void MonsterJump::SetJumping(bool flag)					// 設定是否正在跳躍
	{
		_isJumping = flag;
	}

	void MonsterJump::ChangeGravity()								// 反轉重力
	{
		_gravity *= -1;
	}
}