#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Player.h"

namespace game_framework
{
	/*
	Ctest::Ctest()
	{
		testX = testY = 0;	//重設座標
	}

	void Ctest::OnMove()
	{
		if(testX <= SIZE_Y)		//若還未超過底下的邊緣時
		{
			testX += 3;
			testY += 3;
		}
		else
		{
			testX = testY = 0;	//重設座標
		}
	}

	void Ctest::LoadBitmap()
	{
		test.LoadBitmap(IDB_TIGER, RGB(255, 255, 255));
	}

	void Ctest::OnShow()
	{
		test.SetTopLeft(testX, testY);
		test.ShowBitmap();
	}
	*/

	void Player::Init(int x, int y, int type, int DelayCount)
	{
		_type = type;
		if(_type == 2)
			_shape = new RectangleF(45, 60);
		else _shape = new RectangleF(45, 50);				//重設碰撞箱
		_shape->SetLeftTop((float)x, (float)y);				//重設座標
		_xSpawnPoint = x;
		_ySpawnPoint = y;

		_isMovingLeft = _isMovingRight = _isJumping = false;//初始化移動方向
		_isPassed = false;								//初始化傳送門穿越狀態
		_isGrounded = true;								//初始化落地狀態
		_delayTime = DelayCount;
		_player_left.SetDelayCount(DelayCount);			//預設值
		_player_right.SetDelayCount(DelayCount);		//預設值
		_player_left_neg.SetDelayCount(DelayCount);			//預設值
		_player_right_neg.SetDelayCount(DelayCount);		//預設值
		//_player_left.SetTopLeft(x, y);

		_maxSpeed = 15;									//初始化最高速度
		_speedX = 0;									//初始化水平速度
		_speedY = 0;									//初始化垂直速度
		_acceleration = 5;								//初始化加速度
		_gravity = 3;									//初始化重力加速度
	}

	Player::Player()									// 設定動畫播放速度為 10(越大越慢)
	{
		Init(0, 0, 0, 10);
	}

	Player::Player(int type)							// 設定動畫播放速度的常數(越大越慢)
	{
		Init(0, 0, type, 3);
	}

	Player::Player(int type, int DelayCount)			// 設定動畫播放速度的常數(越大越慢)
	{
		Init(0, 0, type, DelayCount);
	}

	Player::Player(int x, int y, int type)							// 設定動畫播放速度的常數(越大越慢)
	{
		Init(x, y, type, 3);
	}

	Player::Player(int x, int y, int type, int DelayCount)			// 設定動畫播放速度的常數(越大越慢)
	{
		Init(x, y, type, DelayCount);
	}

	Player::~Player() {	}

	void Player::LoadBitmapPlayer(string file, int n)	// 從路徑 "file(1 ~ n)" 新增 n 張圖形
	{
		for (int i = 1; i <= n; i++)
		{
			//讀取往左動畫圖片
			stringstream fileString1;
			fileString1 << file << i << "_left.bmp";
			char* fileChar1 = new char[100];
			fileString1 >> fileChar1;
			_player_left.AddBitmap(fileChar1, RGB(255, 255, 255));				//設白色為透明
			delete[] fileChar1;

			//讀取往右動畫圖片
			stringstream fileString2;
			fileString2 << file << i << "_right.bmp";
			char* fileChar2 = new char[100];
			fileString2 >> fileChar2;
			_player_right.AddBitmap(fileChar2, RGB(255, 255, 255));				//設白色為透明
			delete[] fileChar2;

			//讀取往左動畫圖片
			stringstream fileString3;
			fileString3 << file << i << "_neg_left.bmp";
			char* fileChar3 = new char[100];
			fileString3 >> fileChar3;
			_player_left_neg.AddBitmap(fileChar3, RGB(255, 255, 255));				//設白色為透明
			delete[] fileChar3;
			
			//讀取往右動畫圖片
			stringstream fileString4;
			fileString4 << file << i << "_neg_right.bmp";
			char* fileChar4 = new char[100];
			fileString4 >> fileChar4;
			_player_right_neg.AddBitmap(fileChar4, RGB(255, 255, 255));				//設白色為透明
			delete[] fileChar4;

		}
	}

	void Player::OnMove()														// 玩家依頻率更換bitmap
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
			if (_shape->isLinePass(9999, 0))_speedX = 0;
			_endLeftRight = true;
		}
		else if (_isMovingRight)
		{
			if (_speedX < _maxSpeed)
			{
				_speedX += _acceleration;
				if (_speedX > _maxSpeed)
					_speedX = _maxSpeed;
			}
			if (_shape->isLinePass(9999, -9999 * SIZE_X))_speedX = 0;
			_endLeftRight = false;
		}

		if (!_isGrounded)
		{
			if (!_isPassed)
				_speedY += _gravity;
			else if (_speedY == 0)
				_speedY += 15 * _gravity / abs(_gravity);
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
					_speedY = -30;
				else _speedY = 30;
			}
		}
		//有往任意方向移動
		if (_isMovingLeft || _isMovingRight || _isJumping || (!_isGrounded))
		{
			if (_gravity > 0) {
				//移動的動畫
				_player_left.OnMove();
				_player_right.OnMove();
			}
			else {
				_player_left_neg.OnMove();
				_player_right_neg.OnMove();
			}
		}
		else
		{
			if (_gravity > 0) {
				//站著不動的狀態
				_player_left.Reset();
				_player_right.Reset();
			}
			else {
				_player_left_neg.Reset();
				_player_right_neg.Reset();
			}
		}

		Offset(_speedX, _speedY);
	}

	void Player::OnShow()								// 玩家顯示
	{
		int x = GetX(), y = GetY();
		if (_gravity > 0) {
			//往左走
			if (_isMovingLeft)
			{
				//顯示往左動畫
				_player_left.SetTopLeft(GetX(), GetY());
				_player_left.OnShow();
				//不顯示往右動畫
			}
			//往右走
			else if (_isMovingRight)
			{
				//不顯示往左動畫
				//顯示往右動畫
				_player_right.SetTopLeft(GetX(), GetY());
				_player_right.OnShow();
			}
			//停下或往上下
			else
			{
				//最後往左
				if (_endLeftRight)
				{
					//顯示往左動畫
					_player_left.SetTopLeft(GetX(), GetY());
					_player_left.OnShow();
				}
				//最後往右
				else
				{
					//顯示往右動畫
					_player_right.SetTopLeft(GetX(), GetY());
					_player_right.OnShow();
				}
			}
		}
		else {
			//往左走
			if (_isMovingLeft)
			{
				//顯示往左動畫
				_player_left_neg.SetTopLeft(GetX(), GetY());
				_player_left_neg.OnShow();
				//不顯示往右動畫
			}
			//往右走
			else if (_isMovingRight)
			{
				//不顯示往左動畫
				//顯示往右動畫
				_player_right_neg.SetTopLeft(GetX(), GetY());
				_player_right_neg.OnShow();
			}
			//停下或往上下
			else
			{
				//最後往左
				if (_endLeftRight)
				{
					//顯示往左動畫
					_player_left_neg.SetTopLeft(GetX(), GetY());
					_player_left_neg.OnShow();
				}
				//最後往右
				else
				{
					//顯示往右動畫
					_player_right_neg.SetTopLeft(GetX(), GetY());
					_player_right_neg.OnShow();
				}
			}
		}
	}

	void Player::SetMovingLeft(bool flag)				// 設定是否正在往左移動
	{
		_isMovingLeft = flag;
	}

	void Player::SetMovingRight(bool flag)				// 設定是否正在往右移動
	{
		_isMovingRight = flag;
	}

	void Player::SetJumping(bool flag)					// 設定是否正在跳躍
	{
		_isJumping = flag;
	}

	void Player::SetGrounded(bool flag)
	{
		_isGrounded = flag;
	}

	void Player::SetPassed(bool flag)				// 設定是否已經通過傳送門
	{
		if (_isPassed && (!flag) && !_isGrounded)
		{
			ChangeGravity();
		}
		_isPassed = flag;
	}

	void Player::SetSpawnPoint(int x, int y)
	{
		_xSpawnPoint = x;
		_ySpawnPoint = x;
	}

	void Player::ChangeGravity()								// 反轉重力
	{
		_gravity *= -1;
	}

	void Player::Spawn()
	{
		Init(_xSpawnPoint, _ySpawnPoint, _type, _delayTime);
	}

	/*
	CGameMap::CGameMap() : testX(20), testY(40), MW(48), MH(48)	//給予地圖左上角座標及每張圖寬高
	{
		//地圖陣列初值
		int map_init[4][5] =
		{
			{0, 0, 1, 0, 0},
			{0, 1, 2, 1, 0},
			{1, 2, 1, 2, 1},
			{2, 1, 2, 1, 2}
		};
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 5; j++)
				map[i][j] = map_init[i][j];
	}

	void CGameMap::LoadBitmap()
	{
		blue.LoadBitmap(IDB_BLUE);	//讀藍色圖片
		green.LoadBitmap(IDB_GREEN);//讀綠色圖片
	}

	void CGameMap::OnShow()
	{
		for (int i = 0; i < 5; i++)		//往右顯示五張圖
			for (int j = 0; j < 4; j++)	//往下顯示四張圖
			{
				switch (map[j][i])
				{
					case 0:
						break;
					case 1:
						blue.SetTopLeft(testX + (MW * i), testY + (MH * j));	//設定座標
						blue.ShowBitmap();			//顯示
						break;
					case 2:
						green.SetTopLeft(testX + (MW * i), testY + (MH * j));	//設定座標
						green.ShowBitmap();			//顯示
						break;
					default:
						ASSERT(0);	//陣列異常
				}
			}
	}
	*/
}