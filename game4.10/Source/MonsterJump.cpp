#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "MonsterJump.h"

namespace game_framework
{
	void MonsterJump::Init(int x, int y, int DelayCount)
	{
		_shape.SetLeftTop((float)x, (float)y);			//���]�y��

		_isJumping = false;//��l�Ʋ��ʤ�V
		_isGrounded = true;								//��l�Ƹ��a���A
		_monster.SetDelayCount(DelayCount);			//�w�]��
		//_MonsterJump.SetTopLeft(x, y);

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

	void MonsterJump::OnMove()														// ���a���W�v��bitmap
	{
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
		//���ʪ��ʵe
		_monster.OnMove();

		Offset(_speedX, _speedY);
	}

	void MonsterJump::OnShow()								// ���a���
	{
		int x = GetX(), y = GetY();
		_monster.SetTopLeft(GetX(), GetY());
		_monster.OnShow();
	}

	void MonsterJump::SetJumping(bool flag)					// �]�w�O�_���b���D
	{
		_isJumping = flag;
	}

	void MonsterJump::ChangeGravity()								// ���୫�O
	{
		_gravity *= -1;
	}
}