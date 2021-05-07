#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "MonsterJump.h"

namespace game_framework
{
	void MonsterJump::Init(int x, int y, int type)
	{
		_type = type;
		if (_type == 2)
			_shape = RectangleF(45, 60);
		else _shape = RectangleF(45, 50);				// ���]�I���c
		_shape.SetLeftTop((float)x, (float)y);			// ���]�y��

		_isJumping = true;								// �w�]�@�����D
		_isGrounded = true;								// ��l�Ƹ��a���A
		//_Monster_left.SetTopLeft(x, y);

		_maxSpeed = 20;									// ��l�Ƴ̰��t��
		_speedX = 0;									// ��l�Ƥ����t��
		_speedY = 0;									// ��l�ƫ����t��
		_acceleration = 5;								// ��l�ƥ[�t��
		_gravity = 3;									// ��l�ƭ��O�[�t��
	}

	MonsterJump::MonsterJump()							// �w�]�]�w
	{
		Init(0, 0, 0);
	}

	MonsterJump::MonsterJump(int type)					// �]�w�Ǫ����O
	{
		Init(0, 0, type);
	}

	MonsterJump::~MonsterJump() {	}

	void MonsterJump::LoadBitmapMonster(string file)	// �q���| "file" �s�W�ϧ�
	{
		//Ū���Ϥ�
		stringstream fileString1;
		fileString1 << file << ".bmp";
		char* fileChar1 = new char[100];
		fileString1 >> fileChar1;
		_Monster.LoadBitmapA(fileChar1, RGB(255, 255, 255));				//�]�զ⬰�z��
		delete[] fileChar1;
	}

	void MonsterJump::OnMove()												// �]�w�Ǫ��y��
	{
		if (_type == 1 && _isJumping)
		{
			_type = 1;
		}
		
		if (!_isGrounded)
		{
			_speedY += _gravity;
			if (_speedY == 0)
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
		if (_isJumping || (!_isGrounded))
		{
			//���ʪ��ʵe
			_Monster.SetTopLeft(GetX(), GetY());
		}
		else
		{
			//���ۤ��ʪ����A
		}

		Offset(_speedX, _speedY);
	}

	void MonsterJump::OnShow()								// �Ǫ����
	{
		int x = GetX(), y = GetY();
		//��ܹϤ�
		_Monster.SetTopLeft(x, y);
		_Monster.ShowBitmap();
	}

	void MonsterJump::SetJumping(bool flag)					// �]�w�O�_���b���D
	{
		_isJumping = flag;
	}

	void MonsterJump::SetGrounded(bool flag)
	{
		_isGrounded = flag;
	}

	void MonsterJump::ChangeGravity()								// ���୫�O
	{
		_gravity *= -1;
	}
}