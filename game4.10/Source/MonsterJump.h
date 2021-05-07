#pragma once

#include <string>
#include <sstream>
#include "Shape.h"
#include "Entity.h"

namespace game_framework
{
	// ���a����
	class MonsterJump : public Entity
	{
	public:
		MonsterJump();								// �w�]�]�w
		MonsterJump(int type);						// �]�w�Ǫ����O
		~MonsterJump();

		void LoadBitmapMonster(string file);		// �q���| "file" �s�W�ϧ�
		void OnMove() override;						// �]�w�Ǫ��y��
		void OnShow() override;						// �Ǫ����

		void SetJumping(bool flag);					// �]�w�O�_���b���D
		void SetGrounded(bool flag);				// �]�w�O�_�w�g���a

		void ChangeGravity();						// ���୫�O
	private:
		RectangleF		 _shape;					// �Ǫ������߮y�ФΤj�p
		CMovingBitmap	_Monster;					// �Ǫ��Ϥ�
		bool			_isJumping;					// �O�_���b���D
		bool			_isGrounded;				// �O�_�w�g���a
		//int			_type;						// �O�X���Ǫ�
		void Init(int x, int y, int type);			// ��l�Ƴ]�w
		//Offset									// ���ʩǪ��y��
		//SetXY										// �]�w�Ǫ��y��
		//GetX										// ���o�Ǫ�X�y��
		//GetY										// ���o�Ǫ�Y�y��
	};
}