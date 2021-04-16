#pragma once

#include <string>
#include <sstream>
#include "Shape.h"

namespace game_framework
{
	// ������
	class Gate
	{
	public:
		Gate();										// �]�w�ʵe����t�׬� 10(�V�j�V�C)
		Gate(int DelayCount);						// �]�w�ʵe����t�ת��`��(�V�j�V�C)
		~Gate();
		void LoadBitmapGate(string file, int n);	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
		void OnMove();								// �����W�v��bitmap
		void OnShow();								// �����
		void SetXY(int x, int y);					// �]�w�����W���y��
		int GetX();									// ���o�� X �y��
		int GetY();									// ���o�� Y �y��
	private:
		RectangleF		 _shape;					// �������߮y�ФΤj�p
		CAnimation		_Gate;						// ���ʵe
	};
}