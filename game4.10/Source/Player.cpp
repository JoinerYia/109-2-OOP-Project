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

	Player::Player()									// �]�w�ʵe����t�׬� 10(�V�j�V�C)
	{
		_shape = RectangleF(45, 50);	//���]�y��
		_isMovingDown = _isMovingLeft = _isMovingRight = _isMovingUp = false;	//��l�Ʋ��ʤ�V
		_player_left.SetDelayCount(10);
		_player_right.SetDelayCount(10);
	}

	Player::Player(int DelayCount)						// �]�w�ʵe����t�ת��`��(�V�j�V�C)
	{
		_shape = RectangleF(45, 50);	//���]�y��
		_isMovingDown = _isMovingLeft = _isMovingRight = _isMovingUp = false;	//��l�Ʋ��ʤ�V
		_player_left.SetDelayCount(DelayCount);
		_player_right.SetDelayCount(DelayCount);
	}

	Player::~Player() {	}

	void Player::LoadBitmapPlayer(string file, int n)	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
	{
		for (int i = 1; i <= n; i++)
		{
			//Ū�������ʵe�Ϥ�
			stringstream fileString1;
			fileString1 << file << i << "_left.bmp";
			char* fileChar1 = new char[100];
			fileString1 >> fileChar1;
			_player_left.AddBitmap(fileChar1, RGB(255, 255, 255));		//�]�զ⬰�z��

			//Ū�����k�ʵe�Ϥ�
			stringstream fileString2;
			fileString2 << file << i << "_right.bmp";
			char* fileChar2 = new char[100];
			fileString2 >> fileChar2;
			_player_right.AddBitmap(fileChar2, RGB(255, 255, 255));		//�]�զ⬰�z��
		}
	}

	void Player::OnMove()								// ���a���W�v��bitmap
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
		//�������N��V����
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

	void Player::OnShow()								// ���a���
	{
		//������
		if (_isMovingLeft)
		{
			//��ܩ����ʵe
			_player_left.SetTopLeft(GetX(), GetY());
			_player_left.OnShow();
			//����ܩ��k�ʵe
			//_player_right.SetTopLeft(-_pointX, -_pointY);
		}
		//���k��
		else if (_isMovingRight)
		{
			//����ܩ����ʵe
			//_player_left.SetTopLeft(-_pointX, -_pointY);
			//��ܩ��k�ʵe
			_player_right.SetTopLeft(GetX(), GetY());
			_player_right.OnShow();
		}
		//���U�Ω��W�U
		{
			//�̫᩹��
			if (_endLeftRight)
			{
				//��ܩ����ʵe
				_player_left.SetTopLeft(GetX(), GetY());
				_player_left.OnShow();
			}
			//�̫᩹�k
			else
			{
				//��ܩ��k�ʵe
				_player_right.SetTopLeft(GetX(), GetY());
				_player_right.OnShow();
			}
		}
	}

	void Player::SetMovingDown(bool flag)				// �]�w�O�_���b���U����
	{
		_isMovingDown = flag;
	}

	void Player::SetMovingLeft(bool flag)				// �]�w�O�_���b��������
	{
		_isMovingLeft = flag;
	}

	void Player::SetMovingRight(bool flag)				// �]�w�O�_���b���k����
	{
		_isMovingRight = flag;
	}

	void Player::SetMovingUp(bool flag)				// �]�w�O�_���b���W����
	{
		_isMovingUp = flag;
	}

	void Player::Offset(int dx, int dy) {
		_shape.Offset((float)dx, (float)dy);
	}

	void Player::SetXY(int x, int y)					// �]�w���a���W���y��
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
		_shape.Offset((float)(x - GetX()), (float)(y - GetY()));
	}

	int Player::GetX()									// ���o���a X �y��
	{
		return (int)_shape.GetLeft();
	}

	int Player::GetY()									// ���o���a Y �y��
	{
		return (int)_shape.GetTop();
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