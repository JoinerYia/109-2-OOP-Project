#pragma once

#include <string>
#include <sstream>
#include "Shape.h"
#include "Monster.h"

namespace game_framework
{
	// ���a����
	class MonsterJump : public Monster
	{
	public:
		MonsterJump();									// �]�w�ʵe����t�׬� 10(�V�j�V�C)
		MonsterJump(int DelayCount);			// �]�w���a���O �� �ʵe����t�ת��`��(�V�j�V�C)
		~MonsterJump();

		void OnMove() override;						// ���a���W�v��bitmap
		void OnShow() override;						// ���a���

		void SetJumping(bool flag);					// �]�w�O�_���b���D
		void SetGrounded(bool flag);				// �]�w�O�_�w�g���a

		void ChangeGravity();						// ���୫�O
	private:
		RectangleF		 _shape;					// ���a�����߮y�ФΤj�p
		bool			_isJumping;					// �O�_���b���D
		bool			_isGrounded;				// �O�_�w�g���a
		void Init(int x, int y, int DelayCount);//��l�Ƴ]�w
		//Offset									//���ʪ��a�y��
		//SetXY										//�]�w���a�y��
		//GetX										//���o���aX�y��
		//GetY										//���o���aY�y��
	};
}