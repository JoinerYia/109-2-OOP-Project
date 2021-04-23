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

	void Player::Init(int x, int y, int type, int DelayCount)
	{
		_type = type;
		if(_type == 2)
			_shape = RectangleF(45, 60);
		else _shape = RectangleF(45, 50);				//���]�I���c
		_shape.SetLeftTop((float)x, (float)y);			//���]�y��

		_isMovingLeft = _isMovingRight = _isJumping = false;//��l�Ʋ��ʤ�V
		_isGrounded = true;								//��l�Ƹ��a���A
		_player_left.SetDelayCount(DelayCount);			//�w�]��
		_player_right.SetDelayCount(DelayCount);		//�w�]��

		_maxSpeed = 20;									//��l�Ƴ̰��t��
		_acceleration = 5;								//��l�ƥ[�t��
		_gravity = 5;									//��l�ƭ��O�[�t��
	}

	Player::Player()									// �]�w�ʵe����t�׬� 10(�V�j�V�C)
	{
		Init(0, 0, 0, 3);
	}

	Player::Player(int type)							// �]�w�ʵe����t�ת��`��(�V�j�V�C)
	{
		Init(0, 0, type, 3);
	}

	Player::Player(int type, int DelayCount)			// �]�w�ʵe����t�ת��`��(�V�j�V�C)
	{
		Init(0, 0, type, DelayCount);
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
			_player_left.AddBitmap(fileChar1, RGB(255, 255, 255));				//�]�զ⬰�z��

			//Ū�����k�ʵe�Ϥ�
			stringstream fileString2;
			fileString2 << file << i << "_right.bmp";
			char* fileChar2 = new char[100];
			fileString2 >> fileChar2;
			_player_right.AddBitmap(fileChar2, RGB(255, 255, 255));				//�]�զ⬰�z��
		}
	}

	void Player::OnMove()														// ���a���W�v��bitmap
	{
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
		//�������N��V����
		if (_isMovingLeft || _isMovingRight || _isJumping || (!_isGrounded))
		{
			//���ʪ��ʵe
			_player_left.OnMove();
			_player_right.OnMove();
		}
		else
		{
			//���ۤ��ʪ����A
			_player_left.Reset();
			_player_right.Reset();
		}
		
		Offset(_speedX, _speedY);
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
		}
		//���k��
		else if (_isMovingRight)
		{
			//����ܩ����ʵe
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

	void Player::SetMovingLeft(bool flag)				// �]�w�O�_���b��������
	{
		_isMovingLeft = flag;
	}

	void Player::SetMovingRight(bool flag)				// �]�w�O�_���b���k����
	{
		_isMovingRight = flag;
	}

	void Player::SetJumping(bool flag)					// �]�w�O�_���b���D
	{
		_isJumping = flag;
	}

	void Player::SetPassed(bool flag)				// �]�w�O�_�w�g�q�L�ǰe��
	{
		if (_isPassed && (!flag) && !_isGrounded)
		{
			ChangeGravity();
		}
		_isPassed = flag;
	}

	void Player::ChangeGravity()								// ���୫�O
	{
		_gravity *= -1;
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