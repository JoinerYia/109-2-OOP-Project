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

	Player::Player()									// 設定動畫播放速度為 10(越大越慢)
	{
		_shape = RectangleF(45, 50);	//重設座標
		_isMovingDown = _isMovingLeft = _isMovingRight = _isMovingUp = false;	//初始化移動方向
		_player_left.SetDelayCount(10);
		_player_right.SetDelayCount(10);
	}

	Player::Player(int DelayCount)						// 設定動畫播放速度的常數(越大越慢)
	{
		_shape = RectangleF(45, 50);	//重設座標
		_isMovingDown = _isMovingLeft = _isMovingRight = _isMovingUp = false;	//初始化移動方向
		_player_left.SetDelayCount(DelayCount);
		_player_right.SetDelayCount(DelayCount);
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
			_player_left.AddBitmap(fileChar1, RGB(255, 255, 255));		//設白色為透明

			//讀取往右動畫圖片
			stringstream fileString2;
			fileString2 << file << i << "_right.bmp";
			char* fileChar2 = new char[100];
			fileString2 >> fileChar2;
			_player_right.AddBitmap(fileChar2, RGB(255, 255, 255));		//設白色為透明
		}
	}

	void Player::OnMove()								// 玩家依頻率更換bitmap
	{
		const int STEP_SIZE = 5;
		if (_isMovingLeft)
		{
			Offset(-STEP_SIZE, 0);
			_endLeftRight = true;
		}
		if (_isMovingRight)
		{
			Offset(STEP_SIZE, 0);
			_endLeftRight = false;
		}
		if (_isMovingUp)
			Offset(0, -STEP_SIZE);
		if (_isMovingDown)
			Offset(0, STEP_SIZE);
		//有往任意方向移動
		if ((_isMovingDown || _isMovingLeft || _isMovingRight || _isMovingUp) == true)
		{
			_player_left.OnMove();
			_player_right.OnMove();
		}
		else
		{
			_player_left.Reset();
			_player_right.Reset();
		}
	}

	void Player::OnShow()								// 玩家顯示
	{
		//往左走
		if (_isMovingLeft)
		{
			//顯示往左動畫
			_player_left.SetTopLeft(GetX(), GetY());
			_player_left.OnShow();
			//不顯示往右動畫
			//_player_right.SetTopLeft(-_pointX, -_pointY);
		}
		//往右走
		else if (_isMovingRight)
		{
			//不顯示往左動畫
			//_player_left.SetTopLeft(-_pointX, -_pointY);
			//顯示往右動畫
			_player_right.SetTopLeft(GetX(), GetY());
			_player_right.OnShow();
		}
		//停下或往上下
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

	void Player::SetMovingDown(bool flag)				// 設定是否正在往下移動
	{
		_isMovingDown = flag;
	}

	void Player::SetMovingLeft(bool flag)				// 設定是否正在往左移動
	{
		_isMovingLeft = flag;
	}

	void Player::SetMovingRight(bool flag)				// 設定是否正在往右移動
	{
		_isMovingRight = flag;
	}

	void Player::SetMovingUp(bool flag)				// 設定是否正在往上移動
	{
		_isMovingUp = flag;
	}

	void Player::Offset(int dx, int dy) {
		_shape.Offset((float)dx, (float)dy);
	}

	void Player::SetXY(int x, int y)					// 設定玩家左上角座標
	{
		/*	if(testX <= SIZE_Y)		//若還未超過底下的邊緣時
		{
			testX += 5;
			testY += 5;
		}
		else
		{
			testX = testY = 0;	//重設座標
		}*/
		_shape.Offset((float)(x - GetX()), (float)(y - GetY()));
	}

	int Player::GetX()									// 取得玩家 X 座標
	{
		return (int)_shape.GetLeft();
	}

	int Player::GetY()									// 取得玩家 Y 座標
	{
		return (int)_shape.GetTop();
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