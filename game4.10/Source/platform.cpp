#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "platform.h"

namespace game_framework
{
	void platform::Init(int x, int y, int DelayCount)
	{

		_shape = new RectangleF(65, 64);				//���]�I���c
		_shape->SetLeftTop((float)x, (float)y);			//���]�y��
		_yCenter = SIZE_Y / 2 - 125;
		_shadow = new RectangleF(65, 64);

		_isRightOrLeft = true;
		_platform_left.SetDelayCount(DelayCount);		//�w�]��
		_platform_right.SetDelayCount(DelayCount);		//�w�]��

		_maxSpeed = 5;									//��l�Ƴ̰��t��
		_speedX = 0;									//��l�Ƥ����t��
		_speedY = 0;									//��l�ƫ����t��
		_acceleration = 5;								//��l�ƥ[�t��
		_gravity = 5;									//��l�ƭ��O�[�t��
		_startX = x;									//��l�Ƥ@�}�l�� X �y��
		_moveSpace = 250;								//��l�ƥ��k���ʪ��Z��
	}

	platform::platform()									// �]�w�ʵe����t�׬� 10(�V�j�V�C)
	{
		Init(0, 0, 10);
	}

	platform::platform(int DelayCount)			// �]�w�ʵe����t�ת��`��(�V�j�V�C)
	{
		Init(0, 0, DelayCount);
	}

	platform::platform(int x, int y)
	{
		Init(x, y, 10);
	}

	platform::platform(int x, int y, int DelayCount)
	{
		Init(x, y, DelayCount);
	}

	platform::~platform() {	}

	void platform::LoadBitmapEntity()	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
	{
		string file = "./RES/platform/icon_w1l1_";

		//Ū�������ʵe�Ϥ�
		stringstream fileString1;
		fileString1 << file << "up_left.bmp";
		char* fileChar1 = new char[100];
		fileString1 >> fileChar1;
		_platform_left.AddBitmap(fileChar1, RGB(255, 255, 255));				//�]�զ⬰�z��
		delete[] fileChar1;

		//Ū�����k�ʵe�Ϥ�
		stringstream fileString2;
		fileString2 << file << "up_right.bmp";
		char* fileChar2 = new char[100];
		fileString2 >> fileChar2;
		_platform_right.AddBitmap(fileChar2, RGB(255, 255, 255));			//�]�զ⬰�z��
		delete[] fileChar2;

		_shadow->SetLeftTop((float)_shape->GetLeft(), (float)SIZE_Y - _shape->GetBottom());
	}

	void platform::OnMove()													// ���x���W�v��bitmap
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

		_platform_left.OnMove();
		_platform_right.OnMove();

		_shape->Offset((float)_speedX, (float)_speedY);
		_shadow->SetLeftTop(_shape->GetLeft(), SIZE_Y - _shape->GetBottom());
	}

	void platform::OnShow()								// ���x���
	{
		int x = (int)_shape->GetLeft(), y = (int)_shape->GetTop();
		//������
		if (_isRightOrLeft)
		{
			//��ܩ����ʵe
			_platform_left.SetTopLeft(x, y);
			_platform_left.OnShow();
			//����ܩ��k�ʵe
		}
		//���k��
		else {
			//����ܩ����ʵe
			//��ܩ��k�ʵe
			_platform_right.SetTopLeft(x, y);
			_platform_right.OnShow();
		}
	}

	void platform::SetStartX(int x)			// �]�w�@�}�l�� X �y��
	{
		_startX = x;
	}

	void platform::SetMoveSpace(int distance)	// �]�w�V�k�����ʶZ��
	{
		_moveSpace = distance;
	}

	int platform::isCollision(Entity entity)
	{
		int result = 0;
		if (_shadow->isShapeFCover(entity.GetShape()))result += 2;
		if (_shape->isShapeFCover(entity.GetShape()))result += 1;
		return result;
	}

}