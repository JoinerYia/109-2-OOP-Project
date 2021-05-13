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

		_shape = new RectangleF(63, 31);				//重設碰撞箱
		_shape->SetLeftTop((float)x, (float)y);			//重設座標
		_yCenter = SIZE_Y / 2 - 125;
		_shadow = new RectangleF(63, 31);

		_isRightOrLeft = true;
		_Monster_left.SetDelayCount(DelayCount);		//預設值
		_Monster_right.SetDelayCount(DelayCount);		//預設值
		_Monster_shadow.SetDelayCount(DelayCount);		//預設值

		_maxSpeed = 5;									//初始化最高速度
		_speedX = 0;									//初始化水平速度
		_speedY = 0;									//初始化垂直速度
		_acceleration = 5;								//初始化加速度
		_gravity = 5;									//初始化重力加速度
		_startX = x;									//初始化一開始的 X 座標
		_moveSpace = 250;								//初始化左右移動的距離
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

	void MonsterGo::LoadBitmapEntity()	// 從路徑 "file(1 ~ n)" 新增 n 張圖形
	{
		string file = "./RES/monster/monster_1_";
		
		//讀取往左動畫圖片
		stringstream fileString1;
		fileString1 << file << "up_left.bmp";
		char* fileChar1 = new char[100];
		fileString1 >> fileChar1;
		_Monster_left.AddBitmap(fileChar1, RGB(255, 255, 255));				//設白色為透明
		delete[] fileChar1;

		//讀取往右動畫圖片
		stringstream fileString2;
		fileString2 << file << "up_right.bmp";
		char* fileChar2 = new char[100];
		fileString2 >> fileChar2;
		_Monster_right.AddBitmap(fileChar2, RGB(255, 255, 255));			//設白色為透明
		delete[] fileChar2;

		//讀取對應球動畫圖片
		stringstream fileString3;
		fileString3 << file << "ball_down.bmp";
		char* fileChar3 = new char[100];
		fileString3 >> fileChar3;
		_Monster_shadow.AddBitmap(fileChar3, RGB(0, 0, 0));					//設黑色為透明
		delete[] fileChar3;
		 

		_shadow->SetLeftTop((float)_shape->GetLeft(), (float)SIZE_Y - _shape->GetBottom());
		_Monster_shadow.SetTopLeft((int)_shadow->GetLeft(), (int)_shadow->GetTop());
	}

	void MonsterGo::OnMove()													// 玩家依頻率更換bitmap
	{
		int yCenter = _yCenter;
		if (_isRightOrLeft)
		{
			if (_speedX > -_maxSpeed)
			{
				_speedX -= _acceleration;
				if (_speedX < -_maxSpeed)
					_speedX = -_maxSpeed;
			}
			if (this->GetX() < _startX)
			{
				// 往左走到一定距離後就往右走
				_isRightOrLeft = false;
			}
		}
		else {
			if (_speedX < _maxSpeed)
			{
				_speedX += _acceleration;
				if (_speedX > _maxSpeed)
					_speedX = _maxSpeed;
			}
			if (this->GetX() > _startX + _moveSpace)
			{
				// 往右走到一定距離後就往左走
				_isRightOrLeft = true;
			}
		}

		_Monster_left.OnMove();
		_Monster_right.OnMove();

		_shape->Offset((float)_speedX, (float)_speedY);
		_shadow->SetLeftTop(_shape->GetLeft(), SIZE_Y - _shape->GetBottom());
	}

	void MonsterGo::OnShow()								// 玩家顯示
	{
		int x = (int)_shape->GetLeft(), y = (int)_shape->GetTop();
		//往左走
		if (_isRightOrLeft)
		{
			//顯示往左動畫
			_Monster_left.SetTopLeft(x, y);
			_Monster_left.OnShow();
			//不顯示往右動畫
		}
		//往右走
		else {
			//不顯示往左動畫
			//顯示往右動畫
			_Monster_right.SetTopLeft(x, y);
			_Monster_right.OnShow();
		}
		_Monster_shadow.SetTopLeft((int)_shadow->GetLeft(), (int)_shadow->GetTop());
		_Monster_shadow.OnShow();
	}

	void MonsterGo::SetStartX(int x)			// 設定一開始的 X 座標
	{
		_startX = x;
	}

	void MonsterGo::SetMoveSpace(int distance)	// 設定向右的移動距離
	{
		_moveSpace = distance;
	}

	int MonsterGo::isCollision(Entity entity)
	{
		int result = 0;
		if (_shadow->isShapeFCover(entity.GetShape()))result += 2;
		if (_shape->isShapeFCover(entity.GetShape()))result += 1;
		return result;
	}

}