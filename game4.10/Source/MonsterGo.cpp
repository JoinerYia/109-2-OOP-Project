#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "MonsterGo.h"

namespace game_framework
{
	void MonsterGo::Init(int x, int y, int DelayCount)
	{

		_shape = new RectangleF(45, 50);				//重設碰撞箱
		_shape->SetLeftTop((float)x, (float)y);			//重設座標

		_isMovingLeft = true;							//一開始要往左走
		_isMovingRight = _isJumping = false;			//初始化移動方向
		_isPassed = false;								//初始化傳送門穿越狀態
		_isGrounded = true;								//初始化落地狀態
		_Monster_left.SetDelayCount(DelayCount);		//預設值
		_Monster_right.SetDelayCount(DelayCount);		//預設值
		//_Monster_left.SetTopLeft(x, y);

		_maxSpeed = 20;									//初始化最高速度
		_speedX = 0;									//初始化水平速度
		_speedY = 0;									//初始化垂直速度
		_acceleration = 5;								//初始化加速度
		_gravity = 5;									//初始化重力加速度
		_startX = x;									//初始化一開始的 X 座標
		_moveSpace = 150;								//初始化左右移動的距離
	}

	MonsterGo::MonsterGo()									// 設定動畫播放速度為 10(越大越慢)
	{
		Init(0, 0, 10);
	}

	MonsterGo::MonsterGo(int DelayCount)			// 設定動畫播放速度的常數(越大越慢)
	{
		Init(0, 0, DelayCount);
	}

	MonsterGo::MonsterGo(int x, int y)
	{
		Init(x, y, 10);
	}

	MonsterGo::MonsterGo(int x, int y, int DelayCount)
	{
		Init(x, y, DelayCount);
	}

	MonsterGo::~MonsterGo() {	}

	void MonsterGo::LoadBitmapMonster(string file, int n)	// 從路徑 "file(1 ~ n)" 新增 n 張圖形
	{
		for (int i = 1; i <= n; i++)
		{
			//讀取往左動畫圖片
			stringstream fileString1;
			fileString1 << file << "_left.bmp";
			char* fileChar1 = new char[100];
			fileString1 >> fileChar1;
			_Monster_left.AddBitmap(fileChar1, RGB(255, 255, 255));				//設白色為透明
			delete[] fileChar1;

			//讀取往右動畫圖片
			stringstream fileString2;
			fileString2 << file << "_right.bmp";
			char* fileChar2 = new char[100];
			fileString2 >> fileChar2;
			_Monster_right.AddBitmap(fileChar2, RGB(255, 255, 255));			//設白色為透明
			delete[] fileChar2;
		}
	}

	void MonsterGo::OnMove()													// 玩家依頻率更換bitmap
	{
		if (_type == 1 && _isJumping)
		{
			_type = 1;
		}

		if (!(_isMovingLeft || _isMovingRight))
		{
			if (_speedX != 0)
				_speedX += -_speedX / abs(_speedX);
		}
		else if (_isMovingLeft && _isMovingRight)
		{
			_speedX = 0;
		}
		else if (_isMovingLeft)
		{
			if (_speedX > -_maxSpeed)
			{
				_speedX -= _acceleration;
				if (_speedX < -_maxSpeed)
					_speedX = -_maxSpeed;
			}
			_endLeftRight = true;
		}
		if (_isMovingRight)
		{
			if (_speedX < _maxSpeed)
			{
				_speedX += _acceleration;
				if (_speedX > _maxSpeed)
					_speedX = _maxSpeed;
			}
			_endLeftRight = false;
		}

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
		//有往任意方向移動
		if (_isMovingLeft || _isMovingRight || _isJumping || (!_isGrounded))
		{
			//移動的動畫
			_Monster_left.OnMove();
			_Monster_right.OnMove();
		}
		else
		{
			//站著不動的狀態
			_Monster_left.Reset();
			_Monster_right.Reset();
		}

		Offset(_speedX, _speedY);
	}

	void MonsterGo::OnShow()								// 玩家顯示
	{
		int x = GetX(), y = GetY();
		//往左走
		if (_isMovingLeft)
		{
			//顯示往左動畫
			_Monster_left.SetTopLeft(GetX(), GetY());
			_Monster_left.OnShow();
			//不顯示往右動畫
		}
		//往右走
		else if (_isMovingRight)
		{
			//不顯示往左動畫
			//顯示往右動畫
			_Monster_right.SetTopLeft(GetX(), GetY());
			_Monster_right.OnShow();
		}
		//停下或往上下
		{
			//最後往左
			if (_endLeftRight)
			{
				//顯示往左動畫
				_Monster_left.SetTopLeft(GetX(), GetY());
				_Monster_left.OnShow();
			}
			//最後往右
			else
			{
				//顯示往右動畫
				_Monster_right.SetTopLeft(GetX(), GetY());
				_Monster_right.OnShow();
			}
		}
		int moveX = abs(this->GetX() - _startX);
		if (_isMovingLeft)
		{
			if (moveX > _moveSpace)
			{
				// 往左走到一定距離後就往右走
				_isMovingLeft = false;
				_isMovingRight = true;
			}
		}
		else if (_isMovingRight)
		{
			if (moveX > _moveSpace)
			{
				// 往右走到一定距離後就往左走
				_isMovingLeft = true;
				_isMovingRight = false;
			}
		}
	}

	void MonsterGo::SetMovingLeft(bool flag)				// 設定是否正在往左移動
	{
		_isMovingLeft = flag;
	}

	void MonsterGo::SetMovingRight(bool flag)				// 設定是否正在往右移動
	{
		_isMovingRight = flag;
	}

	void MonsterGo::SetJumping(bool flag)					// 設定是否正在跳躍
	{
		_isJumping = flag;
	}

	void MonsterGo::SetGrounded(bool flag)
	{
		_isGrounded = flag;
	}

	void MonsterGo::SetPassed(bool flag)				// 設定是否已經通過傳送門
	{
		if (_isPassed && (!flag) && !_isGrounded)
		{
			ChangeGravity();
		}
		_isPassed = flag;
	}

	void MonsterGo::SetStartX(int x)					// 設定一開始的 X 座標
	{
		_startX = x;
	}

	void MonsterGo::ChangeGravity()								// 反轉重力
	{
		_gravity *= -1;
	}
}