#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "platform.h"

namespace game_framework
{
	void platform::Init(int x, int y, int DelayCount)
	{

		_shape = new RectangleF(42, 42);				//重設碰撞箱
		_shape->SetLeftTop((float)x, (float)y);			//重設座標
		_yCenter = SIZE_Y / 2 - 125;

		_isRightOrLeft = true;
		_platform_left.SetDelayCount(DelayCount);		//預設值
		_platform_right.SetDelayCount(DelayCount);		//預設值

		_maxSpeed = 5;									//初始化最高速度
		_speedX = 0;									//初始化水平速度
		_speedY = 0;									//初始化垂直速度
		_acceleration = 5;								//初始化加速度
		_gravity = 5;									//初始化重力加速度
		_startX = x;									//初始化一開始的 X 座標
		_moveSpace = 250;								//初始化左右移動的距離
	}

	platform::platform()									// 設定動畫播放速度為 10(越大越慢)
	{
		Init(0, 0, 10);
	}

	platform::platform(int DelayCount)			// 設定動畫播放速度的常數(越大越慢)
	{
		Init(0, 0, DelayCount);
	}

	platform::platform(int x, int y)
	{
		Init(x, y, 10);
	}

	platform::platform(int x, int y, int DelayCount)
	{
		Init(x, y, DelayCount);
	}

	platform::~platform() {	}

	void platform::LoadBitmapEntity()	// 從路徑 "file(1 ~ n)" 新增 n 張圖形
	{
		string file = "./RES/platform/icon_w1l1_";

		//讀取往左動畫圖片
		stringstream fileString1;
		fileString1 << file << "up_left.bmp";
		char* fileChar1 = new char[100];
		fileString1 >> fileChar1;
		_platform_left.AddBitmap(fileChar1, RGB(255, 255, 255));				//設白色為透明
		delete[] fileChar1;

		//讀取往右動畫圖片
		stringstream fileString2;
		fileString2 << file << "up_right.bmp";
		char* fileChar2 = new char[100];
		fileString2 >> fileChar2;
		_platform_right.AddBitmap(fileChar2, RGB(255, 255, 255));			//設白色為透明
		delete[] fileChar2;

	}

	void platform::OnMove()													// 平台依頻率更換bitmap
	{
		int yCenter = _yCenter;
		if (_moveSpace == 0) return;
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

		_platform_left.OnMove();
		_platform_right.OnMove();

		_shape->Offset((float)_speedX, (float)_speedY);
	}

	void platform::OnShow()								// 平台顯示
	{
		int x = (int)_shape->GetLeft(), y = (int)_shape->GetTop();
		//往左走
		if (_isRightOrLeft)
		{
			//顯示往左動畫
			_platform_left.SetTopLeft(x, y);
			_platform_left.OnShow();
			//不顯示往右動畫
		}
		//往右走
		else {
			//不顯示往左動畫
			//顯示往右動畫
			_platform_right.SetTopLeft(x, y);
			_platform_right.OnShow();
		}

		/*CDC* myDC = CDDraw::GetBackCDC();
		myDC->SelectObject(GetStockObject(NULL_BRUSH));
		//myDC->SelectObject(GetStock)
		myDC->Rectangle((int)_shape->GetLeft(), (int)_shape->GetTop(), (int)_shape->GetRight(), (int)_shape->GetBottom());
		CDDraw::ReleaseBackCDC();//*/
	}

	void platform::SetStartX(int x)			// 設定一開始的 X 座標
	{
		_startX = x;
	}

	void platform::SetMoveSpace(int distance)	// 設定向右的移動距離
	{
		_moveSpace = distance;
	}

	int platform::isCollision(Entity entity)
	{
		//if (dHeight < 0)dHeight = -dHeight;
		if (_shape->isShapeFCover(entity.GetShape()))
		{
			int dHeight = (int)(entity.GetShape()->GetBottom() - _shape->GetTop());
			int dx = (int)(entity.GetShape()->GetX() - _shape->GetX());
			if (dx < 0)dx = -dx;
			if (dx > 21)_shape->isShapeCoverWithDepart(entity.GetShape(), 2);
			else if (dHeight > 0) {
				entity.Offset(0, -dHeight + 1);
				return 1;
			}
			else return 0;
		}
		return 0;
	}

}