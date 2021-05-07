#pragma once

#include <string>
#include <sstream>
#include "Shape.h"
#include "Entity.h"

namespace game_framework
{
	// ���a����
	class Monster : public Entity
	{
	public:
		Monster();									// �]�w�ʵe����t�׬� 10(�V�j�V�C)
		Monster(int type);							// �]�w���a���O �� �ʵe����t�׬� 10(�V�j�V�C)
		Monster(int type, int DelayCount);			// �]�w���a���O �� �ʵe����t�ת��`��(�V�j�V�C)
		~Monster();

		void LoadBitmapMonster(string file, int n);	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
		void OnMove() override;						// ���a���W�v��bitmap
		void OnShow() override;						// ���a���

		void SetMovingLeft(bool flag);				// �]�w�O�_���b��������
		void SetMovingRight(bool flag);				// �]�w�O�_���b���k����
		void SetJumping(bool flag);					// �]�w�O�_���b���D
		void SetGrounded(bool flag);				// �]�w�O�_�w�g���a
		void SetPassed(bool flag);					// �]�w�O�_�w�g�q�L�ǰe��

		void ChangeGravity();						// ���୫�O
	private:
		RectangleF		 _shape;					// ���a�����߮y�ФΤj�p
		CAnimation		_Monster_left, _Monster_right;// ���a�ʵe
		bool			_isMovingLeft;				// �O�_���b��������
		bool			_isMovingRight;				// �O�_���b���k����
		bool			_isJumping;					// �O�_���b���D
		bool			_isGrounded;				// �O�_�w�g���a
		bool			_isPassed;					// �O�_�w�g�q�L�ǰe��
		bool			_endLeftRight;				// �̫�O�����٬O���k(true ��ܥ�)
		//int			_type;						// �O�X�����a
		void Init(int x, int y, int type, int DelayCount);//��l�Ƴ]�w
		//Offset									//���ʪ��a�y��
		//SetXY										//�]�w���a�y��
		//GetX										//���o���aX�y��
		//GetY										//���o���aY�y��
	};
}