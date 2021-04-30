#pragma once

#include <string>
#include <sstream>
#include "MapItem.h"
#include "Entity.h"

namespace game_framework
{
	// ������
	class Gate : public MapItem
	{
	public:
		Gate();										// �]�w�ʵe����t�׬� 10(�V�j�V�C)
		Gate(int DelayCount);						// �]�w�ʵe����t�ת��`��(�V�j�V�C)
		~Gate();
		void LoadBitmapGate(string file, int n);	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
		void OnMove();								// �����W�v��bitmap
		void OnShow();								// �����
		bool isCollision(Entity entity);			// �P�_
		// Offset(int dx, dint y);					// ���ʪ��y��
		// SetXY(int x, int y);						// �]�w�����W���y��
		// GetX();									// ���o�� X �y��
		// GetY();									// ���o�� Y �y��
	private:
		//				_shape;						// �������߮y�ФΤj�p
		CAnimation		_Gate;						// ���ʵe
		void Init(int x, int y, int width, int height, int DelayCount);//��l�Ƴ]�w
	};
}