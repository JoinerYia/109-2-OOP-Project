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
		testX = testY = 0;	//���]�y��
	}

	void Ctest::OnMove()
	{
		if(testX <= SIZE_Y)		//�Y�٥��W�L���U����t��
		{
			testX += 3;
			testY += 3;
		}
		else
		{
			testX = testY = 0;	//���]�y��
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
		_pointX = _pointY = 0;	//���]�y��
		_isMovingDown = _isMovingLeft = _isMovingRight = _isMovingUp = false;	//��l�Ʋ��ʤ�V
	}

	Player::Player(int DelayCount)
	{
		_pointX = _pointY = 0;	//���]�y��
		_isMovingDown = _isMovingLeft = _isMovingRight = _isMovingUp = false;	//��l�Ʋ��ʤ�V
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
			_player.AddBitmap(fileChar, RGB(255, 255, 255));		//�]�զ⬰�z��
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
		//�����S����
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
		/*	if(testX <= SIZE_Y)		//�Y�٥��W�L���U����t��
		{
			testX += 5;
			testY += 5;
		}
		else
		{
			testX = testY = 0;	//���]�y��
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
	CGameMap::CGameMap() : testX(20), testY(40), MW(48), MH(48)	//�����a�ϥ��W���y�ФΨC�i�ϼe��
	{
		//�a�ϰ}�C���
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
		blue.LoadBitmap(IDB_BLUE);	//Ū�Ŧ�Ϥ�
		green.LoadBitmap(IDB_GREEN);//Ū���Ϥ�
	}

	void CGameMap::OnShow()
	{
		for (int i = 0; i < 5; i++)		//���k��ܤ��i��
			for (int j = 0; j < 4; j++)	//���U��ܥ|�i��
			{
				switch (map[j][i])
				{
					case 0:
						break;
					case 1:
						blue.SetTopLeft(testX + (MW * i), testY + (MH * j));	//�]�w�y��
						blue.ShowBitmap();			//���
						break;
					case 2:
						green.SetTopLeft(testX + (MW * i), testY + (MH * j));	//�]�w�y��
						green.ShowBitmap();			//���
						break;
					default:
						ASSERT(0);	//�}�C���`
				}
			}
	}
	*/
}