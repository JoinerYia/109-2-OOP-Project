#pragma once

#include <string>
#include <sstream>
#include "Entity.h"

namespace game_framework
{
	// ������
	class Gate
	{
	public:
		Gate();										// �]�w�ʵe����t�׬� 10(�V�j�V�C)
		Gate(int DelayCount);						// �]�w�ʵe����t�ת��`��(�V�j�V�C)
		Gate(int x, int y);							// �]�w�ʵe����t�׬� 10(�V�j�V�C)
		~Gate();
		void LoadBitmapGate(string file, int n);	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
		void OnMove();								// �����W�v��bitmap
		void OnShow();								// �����
		bool isCollision(Entity entity);			// �P�_

		void Offset(int dx, int dy);
		void SetXY(int x, int y);

		int GetX() const;
		int GetY() const;
		ShapeF GetShapeF();
	private:
		int				_type = 0;
		RectangleF		_shape;						// �������߮y�ФΤj�p
		CAnimation		_Gate;						// ���ʵe
		void Init(int x, int y, int width, int height, int DelayCount);//��l�Ƴ]�w
	};
}