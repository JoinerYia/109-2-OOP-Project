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
		MonsterJump(int x, int y);					// �]�w�Ǫ���m
		~MonsterJump();

		void LoadBitmapEntity() override;			// �q���| "file" �s�W�ϧ�
		void OnMove() override;						// �]�w�Ǫ��y��
		void OnShow() override;						// �Ǫ����
		int isCollision(Entity entity) override;

	private:
		//RectangleF		 _shape;					// �Ǫ������߮y�ФΤj�p
		CMovingBitmap	_Monster, _MonsterBall;		// �Ǫ��Ϥ��B�P�Ǫ��������y�Ϥ�
		ShapeF*			_shadow;
		bool			_isGrounded;				// �O�_�w�g���a
		int				_yCenter;					//�Ǫ��P�Ǫ��������y������
		//int			_type;						// �O�X���Ǫ�
		void Init(int x, int y);					// ��l�Ƴ]�w
		//Offset									// ���ʩǪ��y��
		//SetXY										// �]�w�Ǫ��y��
		//GetX										// ���o�Ǫ�X�y��
		//GetY										// ���o�Ǫ�Y�y��
	};
}