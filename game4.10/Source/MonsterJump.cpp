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
		_yCenter = SIZE_Y / 2 - 65;
		_shadow = new CircleF(31);
		_shadow->SetLeftTop((float)x, (float)SIZE_Y - _shape->GetBottom());

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

	void MonsterJump::LoadBitmapEntity()	// �q���| "file" �s�W�ϧ�
	{
		//Ū���Ϥ�
		string file = "./RES/monster/monster_2";
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
		int yCenter = _yCenter;
		_isGrounded = this->GetY() > yCenter;
		if (_isGrounded)
		{
			//_speedY = 0;/*
			if (_gravity > 0)
				_speedY = -50;
			else _speedY = 50;//*/
		}
		else
		{
			_speedY += _gravity;
		}
		_shape->Offset((float)_speedX, (float)_speedY);
		_shadow->SetLeftTop(_shape->GetLeft(), yCenter * 2 - _shape->GetBottom()+150);
		//_MonsterBall.SetTopLeft(x, _yCenter * 2 - y - _MonsterBall.Height());
	}

	void MonsterJump::OnShow()								// �Ǫ����
	{
		//��ܹϤ�
		_Monster.SetTopLeft((int)_shape->GetLeft(), (int)_shape->GetTop());
		_Monster.ShowBitmap();
		_MonsterBall.SetTopLeft((int)_shadow->GetLeft(), (int)_shadow->GetTop());
		_MonsterBall.ShowBitmap();
	}

	int MonsterJump::isCollision(Entity entity)
	{
		int result = 0;
		if (_shadow->isShapeFCover(entity.GetShape()))result += 2;
		if (_shape->isShapeFCover(entity.GetShape()))result += 1;
		return result;
	}
}