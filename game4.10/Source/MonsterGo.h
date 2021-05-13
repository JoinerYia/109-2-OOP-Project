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

		void LoadBitmapEntity() override;	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
		void OnMove() override;						// �Ǫ����W�v��bitmap
		void OnShow() override;						// �Ǫ����
		int isCollision(Entity entity) override;

		void SetStartX(int x);						// �]�w�@�}�l�� X �y��
		void SetMoveSpace(int distance);			// �]�w�V�k�����ʶZ��

	private:
		//RectangleF		 _shape;					// �Ǫ������߮y�ФΤj�p
		CAnimation		_Monster_left, _Monster_right;// �Ǫ��ʵe
		CAnimation		_Monster_shadow;			// �P�Ǫ��������y�Ϥ�
		ShapeF*			_shadow;
		bool			_isRightOrLeft;				// False���k���� True��������
		int				_startX;					// �@�}�l�� X �y��
		int				_moveSpace;					// ���k���ʪ��Z��
		int				_yCenter;					//�Ǫ��P�Ǫ��������y������
		//int			_type;						// �O�X���Ǫ�
		void Init(int x, int y, int DelayCount);	//��l�Ƴ]�w
		//Offset									// ���ʩǪ��y��
		//SetXY										// �]�w�Ǫ��y��
		//GetX										// ���o�Ǫ�X�y��
		//GetY										// ���o�Ǫ�Y�y��
	};
}