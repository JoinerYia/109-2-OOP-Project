#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "MonsterGo.h"

namespace game_framework
{
	void MonsterGo::Init(int x, int y, int DelayCount)
	{

		_shape = new RectangleF(63, 31);				//���]�I���c
		_shape->SetLeftTop((float)x, (float)y);			//���]�y��
		_yCenter = SIZE_Y / 2 - 125;
		_shadow = new RectangleF(63, 31);

		_isRightOrLeft = true;
		_Monster_left.SetDelayCount(DelayCount);		//�w�]��
		_Monster_right.SetDelayCount(DelayCount);		//�w�]��
		_Monster_shadow.SetDelayCount(DelayCount);		//�w�]��

		_maxSpeed = 5;									//��l�Ƴ̰��t��
		_speedX = 0;									//��l�Ƥ����t��
		_speedY = 0;									//��l�ƫ����t��
		_acceleration = 5;								//��l�ƥ[�t��
		_gravity = 5;									//��l�ƭ��O�[�t��
		_startX = x;									//��l�Ƥ@�}�l�� X �y��
		_moveSpace = 250;								//��l�ƥ��k���ʪ��Z��
	}

	MonsterGo::MonsterGo()									// �]�w�ʵe����t�׬� 10(�V�j�V�C)
	{
		Init(0, 0, 10);
	}

	MonsterGo::MonsterGo(int DelayCount)			// �]�w�ʵe����t�ת��`��(�V�j�V�C)
	{
		Init(0, 0, DelayCount);
	}

	MonsterGo::MonsterGo(int x, int y)
	{
		Init(x, y, 10);
	}

	MonsterGo::MonsterGo(int x, int y, int DelayCount)
	{
		Init(x, y, DelayCount);
	}

	MonsterGo::~MonsterGo() {	}

	void MonsterGo::LoadBitmapEntity()	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
	{
		string file = "./RES/monster/monster_1_";
		
		//Ū�������ʵe�Ϥ�
		stringstream fileString1;
		fileString1 << file << "up_left.bmp";
		char* fileChar1 = new char[100];
		fileString1 >> fileChar1;
		_Monster_left.AddBitmap(fileChar1, RGB(255, 255, 255));				//�]�զ⬰�z��
		delete[] fileChar1;

		//Ū�����k�ʵe�Ϥ�
		stringstream fileString2;
		fileString2 << file << "up_right.bmp";
		char* fileChar2 = new char[100];
		fileString2 >> fileChar2;
		_Monster_right.AddBitmap(fileChar2, RGB(255, 255, 255));			//�]�զ⬰�z��
		delete[] fileChar2;

		//Ū�������y�ʵe�Ϥ�
		stringstream fileString3;
		fileString3 << file << "ball_down.bmp";
		char* fileChar3 = new char[100];
		fileString3 >> fileChar3;
		_Monster_shadow.AddBitmap(fileChar3, RGB(0, 0, 0));					//�]�¦⬰�z��
		delete[] fileChar3;
		 

		_shadow->SetLeftTop((float)_shape->GetLeft(), (float)SIZE_Y - _shape->GetBottom());
		_Monster_shadow.SetTopLeft((int)_shadow->GetLeft(), (int)_shadow->GetTop());
	}

	void MonsterGo::OnMove()													// ���a���W�v��bitmap
	{
		int yCenter = _yCenter;
		if (_isRightOrLeft)
		{
			if (_speedX > -_maxSpeed)
			{
				_speedX -= _acceleration;
				if (_speedX < -_maxSpeed)
					_speedX = -_maxSpeed;
			}
			if (this->GetX() < _startX)
			{
				// ��������@�w�Z����N���k��
				_isRightOrLeft = false;
			}
		}
		else {
			if (_speedX < _maxSpeed)
			{
				_speedX += _acceleration;
				if (_speedX > _maxSpeed)
					_speedX = _maxSpeed;
			}
			if (this->GetX() > _startX + _moveSpace)
			{
				// ���k����@�w�Z����N������
				_isRightOrLeft = true;
			}
		}

		_Monster_left.OnMove();
		_Monster_right.OnMove();

		_shape->Offset((float)_speedX, (float)_speedY);
		_shadow->SetLeftTop(_shape->GetLeft(), SIZE_Y - _shape->GetBottom());
	}

	void MonsterGo::OnShow()								// ���a���
	{
		int x = (int)_shape->GetLeft(), y = (int)_shape->GetTop();
		//������
		if (_isRightOrLeft)
		{
			//��ܩ����ʵe
			_Monster_left.SetTopLeft(x, y);
			_Monster_left.OnShow();
			//����ܩ��k�ʵe
		}
		//���k��
		else {
			//����ܩ����ʵe
			//��ܩ��k�ʵe
			_Monster_right.SetTopLeft(x, y);
			_Monster_right.OnShow();
		}
		_Monster_shadow.SetTopLeft((int)_shadow->GetLeft(), (int)_shadow->GetTop());
		_Monster_shadow.OnShow();
	}

	void MonsterGo::SetStartX(int x)			// �]�w�@�}�l�� X �y��
	{
		_startX = x;
	}

	void MonsterGo::SetMoveSpace(int distance)	// �]�w�V�k�����ʶZ��
	{
		_moveSpace = distance;
	}

	int MonsterGo::isCollision(Entity entity)
	{
		int result = 0;
		if (_shadow->isShapeFCover(entity.GetShape()))result += 2;
		if (_shape->isShapeFCover(entity.GetShape()))result += 1;
		return result;
	}

}