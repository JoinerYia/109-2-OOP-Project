#pragma once

#include <string>
#include <sstream>
#include "Shape.h"
#include "Entity.h"

namespace game_framework
{
	// ���a����
	class Monster
	{
	protected:
		void LoadBitmapMonster(string file, int n);	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
		void Offset(int dx, int dy);
		void SetXY(int x, int y);
		int GetX();
		int GetY();
		virtual void OnMove();						// ���a���W�v��bitmap
		virtual void OnShow();						// ���a���

		RectangleF		 _shape;					// ���a�����߮y�ФΤj�p
		CMovingBitmap	_monster;					// ���a�ʵe
	};
}