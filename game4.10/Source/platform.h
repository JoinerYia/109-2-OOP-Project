#pragma once

#include <string>
#include <sstream>
#include "Shape.h"
#include "Entity.h"

namespace game_framework
{
	// ���x����
	class platform : public Entity
	{
	public:
		platform();									// �]�w�ʵe����t�׬� 10(�V�j�V�C)
		platform(int DelayCount);						// �]�w���x���O �� �ʵe����t�ת��`��(�V�j�V�C)
		platform(int x, int y);
		platform(int x, int y, int DelayCount);
		~platform();

		void LoadBitmapEntity() override;	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
		void OnMove() override;						// ���x���W�v��bitmap
		void OnShow() override;						// ���x���
		int isCollision(Entity entity) override;

		void SetStartX(int x);						// �]�w�@�}�l�� X �y��
		void SetMoveSpace(int distance);			// �]�w�V�k�����ʶZ��

	private:
		//RectangleF		 _shape;					// ���x�����߮y�ФΤj�p
		CAnimation		_platform_left, _platform_right;// ���x�ʵe
		bool			_isRightOrLeft;				// False���k���� True��������
		int				_startX;					// �@�}�l�� X �y��
		int				_moveSpace;					// ���k���ʪ��Z��
		int				_yCenter;					//���x�P���x�������y������
		//int			_type;						// �O�X�����x
		void Init(int x, int y, int DelayCount);	//��l�Ƴ]�w
		//Offset									// ���ʥ��x�y��
		//SetXY										// �]�w���x�y��
		//GetX										// ���o���xX�y��
		//GetY										// ���o���xY�y��
	};
}