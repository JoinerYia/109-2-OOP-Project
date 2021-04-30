#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Monster.h"

namespace game_framework
{
	void Monster::LoadBitmapMonster(string file, int n)				// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
	{
		for (int i = 1; i <= n; i++)
		{
			//Ū���ʵe�Ϥ�
			stringstream fileString1;
			fileString1 << file << i << ".bmp";
			char* fileChar1 = new char[100];
			fileString1 >> fileChar1;
			_monster.LoadBitmapA(fileChar1, RGB(255, 255, 255));	//�]�զ⬰�z��
			delete[] fileChar1;
		}
	}

	void Monster::Offset(int dx, int dy) { _shape.Offset((float)dx, (float)dy); }
	void Monster::SetXY(int x, int y) { _shape.Offset((float)(x - GetX()), (float)(y - GetY())); }

	int Monster::GetX() { return (int)_shape.GetLeft(); }
	int Monster::GetY() { return (int)_shape.GetTop(); }

	void Monster::OnMove()								// ���a���W�v��bitmap
	{
	}

	void Monster::OnShow()								// ���a���
	{
	}
}