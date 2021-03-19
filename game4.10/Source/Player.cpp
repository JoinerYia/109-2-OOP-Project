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

	Player::Player()
	{
		_pointX = _pointY = 0;	//重設座標
		_isMovingDown = _isMovingLeft = _isMovingRight = _isMovingUp = false;	//初始化移動方向
	}

	Player::Player(int DelayCount)
	{
		_pointX = _pointY = 0;	//重設座標
		_isMovingDown = _isMovingLeft = _isMovingRight = _isMovingUp = false;	//初始化移動方向
		_player.SetDelayCount(DelayCount);
	}

	Player::~Player()
	{
	}

	void Player::LoadBitmapPlayer(string file, int n)
	{
		for (int i = 1; i <= n; i++)
		{
			stringstream fileString;
			fileString << file << i << ".bmp";
			char* fileChar = new char[100];
			fileString >> fileChar;
			_player.AddBitmap(fileChar, RGB(255, 255, 255));		//設白色為透明
		}
	}

	void Player::OnMove()
	{
		const int STEP_SIZE = 5;
		if (_isMovingLeft)
			_pointX -= STEP_SIZE;
		if (_isMovingRight)
			_pointX += STEP_SIZE;
		if (_isMovingUp)
			_pointY -= STEP_SIZE;
		if (_isMovingDown)
			_pointY += STEP_SIZE;
		//完全沒移動
		if (_isMovingDown == _isMovingLeft && _isMovingLeft == _isMovingRight && _isMovingRight == _isMovingUp && _isMovingUp == false)
			;
		else
			_player.OnMove();
	}

	void Player::OnShow()
	{
		_player.SetTopLeft(_pointX, _pointY);
		_player.OnShow();
	}

	void Player::SetMovingDown(bool flag)
	{
		_isMovingDown = flag;
	}

	void Player::SetMovingLeft(bool flag)
	{
		_isMovingLeft = flag;
	}

	void Player::SetMovingRight(bool flag)
	{
		_isMovingRight = flag;
	}

	void Player::SetMovingUp(bool flag)
	{
		_isMovingUp = flag;
	}

	void Player::SetXY(int x, int y)
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
		_pointX = x;
		_pointY = y;
	}

	int Player::GetX()
	{
		return _pointX;
	}

	int Player::GetY()
	{
		return _pointY;
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