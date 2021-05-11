#pragma once

#include <string>
#include <sstream>
#include "Shape.h"
#include "Entity.h"

namespace game_framework
{
	// �Ǫ�����
	class MonsterGo : public Entity
	{
	public:
		MonsterGo();									// �]�w�ʵe����t�׬� 10(�V�j�V�C)
		MonsterGo(int DelayCount);						// �]�w�Ǫ����O �� �ʵe����t�ת��`��(�V�j�V�C)
		MonsterGo(int x, int y);
		MonsterGo(int x, int y, int DelayCount);
		~MonsterGo();

		void LoadBitmapMonster(string file, int n);	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
		void OnMove() override;						// �Ǫ����W�v��bitmap
		void OnShow() override;						// �Ǫ����

		void SetMovingLeft(bool flag);				// �]�w�O�_���b��������
		void SetMovingRight(bool flag);				// �]�w�O�_���b���k����
		void SetJumping(bool flag);					// �]�w�O�_���b���D
		void SetGrounded(bool flag);				// �]�w�O�_�w�g���a
		void SetPassed(bool flag);					// �]�w�O�_�w�g�q�L�ǰe��
		void SetStartX(int x);						// �]�w�@�}�l�� X �y��

		void ChangeGravity();						// ���୫�O
	private:
		//RectangleF		 _shape;					// �Ǫ������߮y�ФΤj�p
		CAnimation		_Monster_left, _Monster_right;// �Ǫ��ʵe
		bool			_isMovingLeft;				// �O�_���b��������
		bool			_isMovingRight;				// �O�_���b���k����
		bool			_isJumping;					// �O�_���b���D
		bool			_isGrounded;				// �O�_�w�g���a
		bool			_isPassed;					// �O�_�w�g�q�L�ǰe��
		bool			_endLeftRight;				// �̫�O�����٬O���k(true ��ܥ�)
		int				_startX;					// �@�}�l�� X �y��
		int				_moveSpace;					// ���k���ʪ��Z��
		//int			_type;						// �O�X���Ǫ�
		void Init(int x, int y, int DelayCount);	//��l�Ƴ]�w
		//Offset									// ���ʩǪ��y��
		//SetXY										// �]�w�Ǫ��y��
		//GetX										// ���o�Ǫ�X�y��
		//GetY										// ���o�Ǫ�Y�y��
	};
}