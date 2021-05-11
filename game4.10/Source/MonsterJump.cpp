#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "MonsterJump.h"

namespace game_framework
{
	void MonsterJump::Init(int x, int y)
	{
		_shape = new CircleF(31);						// ���]�I���c
		_shape->SetLeftTop((float)x, (float)y);			// ���]�y��
		_yCenter = SIZE_Y / 2;

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
		Init(0, 0);
	}

	MonsterJump::MonsterJump(int x, int y)	// �]�w�Ǫ����O
	{
		Init(x, y);
	}

	MonsterJump::~MonsterJump() {	}

	void MonsterJump::LoadBitmapMonster(string file)	// �q���| "file" �s�W�ϧ�
	{
		//Ū���Ϥ�
		stringstream fileString1, fileString2;
		fileString1 << file << ".bmp";
		char* fileChar1 = new char[100];
		fileString1 >> fileChar1;
		_Monster.LoadBitmapA(fileChar1, RGB(255, 255, 255));				//�]�զ⬰�z��
		fileString2 << file << "_ball.bmp";
		char* fileChar2 = new char[100];
		fileString2 >> fileChar2;
		_MonsterBall.LoadBitmapA(fileChar2, RGB(0, 0, 0));					//�]�¦⬰�z��
		delete[] fileChar1;
		delete[] fileChar2;
	}

	void MonsterJump::OnMove()												// �]�w�Ǫ��y��
	{
		_isGrounded = GetY() > SIZE_Y / 2 - 15;
		if (_isGrounded)
		{
			//_speedY = 5;
			if (_gravity > 0)
				_speedY = -50;
			else _speedY = 50;
		}
		else
		{
			_speedY += _gravity;
		}
		//���ʪ��ʵe
		_Monster.SetTopLeft(_shape->GetX(), _shape->GetY());
		_MonsterBall.SetTopLeft(_shape->GetX(), SIZE_Y - _shape->GetY() + _MonsterBall.Height());

		_shape->Offset((float)_speedX, (float)_speedY);
	}

	void MonsterJump::OnShow()								// �Ǫ����
	{
		int x = _shape->GetX(), y = _shape->GetY();
		//��ܹϤ�
		_Monster.SetTopLeft(x, y);
		_Monster.ShowBitmap();
		_MonsterBall.SetTopLeft(x, SIZE_Y - y + _MonsterBall.Height());
		_MonsterBall.ShowBitmap();
	}

	void MonsterJump::SetGrounded(bool flag)
	{
		_isGrounded = flag;
	}
}