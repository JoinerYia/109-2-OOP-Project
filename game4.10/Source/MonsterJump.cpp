#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "MonsterJump.h"

namespace game_framework
{
	void MonsterJump::Init(int x, int y, int type, int DelayCount)
	{
		_type = type;
		if (_type == 2)
			_shape = RectangleF(45, 60);
		else _shape = RectangleF(45, 50);				//���]�I���c
		_shape.SetLeftTop((float)x, (float)y);			//���]�y��

		_isMovingLeft = _isMovingRight = _isJumping = false;//��l�Ʋ��ʤ�V
		_isPassed = false;								//��l�ƶǰe����V���A
		_isGrounded = true;								//��l�Ƹ��a���A
		_Monster_left.SetDelayCount(DelayCount);			//�w�]��
		_Monster_right.SetDelayCount(DelayCount);		//�w�]��
		//_Monster_left.SetTopLeft(x, y);

		_maxSpeed = 20;									//��l�Ƴ̰��t��
		_speedX = 0;									//��l�Ƥ����t��
		_speedY = 0;									//��l�ƫ����t��
		_acceleration = 5;								//��l�ƥ[�t��
		_gravity = 5;									//��l�ƭ��O�[�t��
	}

	MonsterJump::MonsterJump()									// �]�w�ʵe����t�׬� 10(�V�j�V�C)
	{
		Init(0, 0, 0, 10);
	}

	MonsterJump::MonsterJump(int type)							// �]�w�ʵe����t�ת��`��(�V�j�V�C)
	{
		Init(0, 0, type, 3);
	}

	MonsterJump::MonsterJump(int type, int DelayCount)			// �]�w�ʵe����t�ת��`��(�V�j�V�C)
	{
		Init(0, 0, type, DelayCount);
	}

	MonsterJump::~MonsterJump() {	}

	void MonsterJump::LoadBitmapMonster(string file, int n)	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
	{
		for (int i = 1; i <= n; i++)
		{
			//Ū�������ʵe�Ϥ�
			stringstream fileString1;
			fileString1 << file << i << "_left.bmp";
			char* fileChar1 = new char[100];
			fileString1 >> fileChar1;
			_Monster_left.AddBitmap(fileChar1, RGB(255, 255, 255));				//�]�զ⬰�z��
			delete[] fileChar1;

			//Ū�����k�ʵe�Ϥ�
			stringstream fileString2;
			fileString2 << file << i << "_right.bmp";
			char* fileChar2 = new char[100];
			fileString2 >> fileChar2;
			_Monster_right.AddBitmap(fileChar2, RGB(255, 255, 255));				//�]�զ⬰�z��
			delete[] fileChar2;
		}
	}

	void MonsterJump::OnMove()														// ���a���W�v��bitmap
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
		//�������N��V����
		if (_isMovingLeft || _isMovingRight || _isJumping || (!_isGrounded))
		{
			//���ʪ��ʵe
			_Monster_left.OnMove();
			_Monster_right.OnMove();
		}
		else
		{
			//���ۤ��ʪ����A
			_Monster_left.Reset();
			_Monster_right.Reset();
		}

		Offset(_speedX, _speedY);
	}

	void MonsterJump::OnShow()								// ���a���
	{
		int x = GetX(), y = GetY();
		//������
		if (_isMovingLeft)
		{
			//��ܩ����ʵe
			_Monster_left.SetTopLeft(GetX(), GetY());
			_Monster_left.OnShow();
			//����ܩ��k�ʵe
		}
		//���k��
		else if (_isMovingRight)
		{
			//����ܩ����ʵe
			//��ܩ��k�ʵe
			_Monster_right.SetTopLeft(GetX(), GetY());
			_Monster_right.OnShow();
		}
		//���U�Ω��W�U
		{
			//�̫᩹��
			if (_endLeftRight)
			{
				//��ܩ����ʵe
				_Monster_left.SetTopLeft(GetX(), GetY());
				_Monster_left.OnShow();
			}
			//�̫᩹�k
			else
			{
				//��ܩ��k�ʵe
				_Monster_right.SetTopLeft(GetX(), GetY());
				_Monster_right.OnShow();
			}
		}
	}

	void MonsterJump::SetMovingLeft(bool flag)				// �]�w�O�_���b��������
	{
		_isMovingLeft = flag;
	}

	void MonsterJump::SetMovingRight(bool flag)				// �]�w�O�_���b���k����
	{
		_isMovingRight = flag;
	}

	void MonsterJump::SetJumping(bool flag)					// �]�w�O�_���b���D
	{
		_isJumping = flag;
	}

	void MonsterJump::SetGrounded(bool flag)
	{
		_isGrounded = flag;
	}

	void MonsterJump::SetPassed(bool flag)				// �]�w�O�_�w�g�q�L�ǰe��
	{
		if (_isPassed && (!flag) && !_isGrounded)
		{
			ChangeGravity();
		}
		_isPassed = flag;
	}

	void MonsterJump::ChangeGravity()								// ���୫�O
	{
		_gravity *= -1;
	}
}