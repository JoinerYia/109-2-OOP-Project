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

		_isMovingLeft = true;							//�@�}�l�n������
		_isMovingRight = false;							//��l�Ʋ��ʤ�V
		_Monster_left.SetDelayCount(DelayCount);		//�w�]��
		_Monster_right.SetDelayCount(DelayCount);		//�w�]��
		//_Monster_left.SetTopLeft(x, y);

		_maxSpeed = 5;									//��l�Ƴ̰��t��
		_speedX = 0;									//��l�Ƥ����t��
		_speedY = 0;									//��l�ƫ����t��
		_acceleration = 5;								//��l�ƥ[�t��
		_gravity = 5;									//��l�ƭ��O�[�t��
		_startX = x;									//��l�Ƥ@�}�l�� X �y��
		_moveSpace = 150;								//��l�ƥ��k���ʪ��Z��
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

	void MonsterGo::LoadBitmapMonster(string file, int n)	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
	{
		for (int i = 1; i <= n; i++)
		{
			//Ū�������ʵe�Ϥ�
			stringstream fileString1;
			fileString1 << file << "_left.bmp";
			char* fileChar1 = new char[100];
			fileString1 >> fileChar1;
			_Monster_left.AddBitmap(fileChar1, RGB(255, 255, 255));				//�]�զ⬰�z��
			delete[] fileChar1;

			//Ū�����k�ʵe�Ϥ�
			stringstream fileString2;
			fileString2 << file << "_right.bmp";
			char* fileChar2 = new char[100];
			fileString2 >> fileChar2;
			_Monster_right.AddBitmap(fileChar2, RGB(255, 255, 255));			//�]�զ⬰�z��
			delete[] fileChar2;
		}
	}

	void MonsterGo::OnMove()													// ���a���W�v��bitmap
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
		else if (_isMovingRight)
		{
			if (_speedX < _maxSpeed)
			{
				_speedX += _acceleration;
				if (_speedX > _maxSpeed)
					_speedX = _maxSpeed;
			}
			_endLeftRight = false;
		}

		//�������N��V����
		if (_isMovingLeft || _isMovingRight)
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

		if (_isMovingLeft)
		{
			if (this->GetX() < _startX)
			{
				// ��������@�w�Z����N���k��
				_isMovingLeft = false;
				_isMovingRight = true;
			}
		}
		else if (_isMovingRight)
		{
			if (this->GetX() > _startX + _moveSpace)
			{
				// ���k����@�w�Z����N������
				_isMovingLeft = true;
				_isMovingRight = false;
			}
		}
	}

	void MonsterGo::OnShow()								// ���a���
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
		else {
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

	void MonsterGo::SetStartX(int x)					// �]�w�@�}�l�� X �y��
	{
		_startX = x;
	}

	void MonsterGo::ChangeGravity()								// ���୫�O
	{
		_gravity *= -1;
	}
}