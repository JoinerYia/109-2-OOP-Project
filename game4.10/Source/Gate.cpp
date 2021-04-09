#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Gate.h"

namespace game_framework
{
	Gate::Gate()										// �]�w�ʵe����t�׬� 10(�V�j�V�C)
	{
		_shape = RectangleF(210, 60);					//���]�y��
		_Gate.SetDelayCount(10);
	}

	Gate::Gate(int DelayCount)							// �]�w�ʵe����t�ת��`��(�V�j�V�C)
	{
		_shape = RectangleF(210, 60);					//���]�y��
		_Gate.SetDelayCount(DelayCount);
	}

	Gate::~Gate() {	}

	void Gate::LoadBitmapGate(string file, int n)		// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
	{
		for (int i = 1; i <= n; i++)
		{
			//Ū���ʵe�Ϥ�
			stringstream fileString1;
			fileString1 << file << i << ".bmp";
			char* fileChar1 = new char[100];
			fileString1 >> fileChar1;
			_Gate.AddBitmap(fileChar1, RGB(255, 255, 255));				//�]�զ⬰�z��
		}
	}

	void Gate::OnMove()									// �����W�v��bitmap
	{
		_Gate.OnMove();
	}

	void Gate::OnShow()									// �����
	{
		//��ܰʵe
		_Gate.SetTopLeft(GetX(), GetY());
		_Gate.OnShow();
	}

	void Gate::SetXY(int x, int y)						// �]�w�����W���y��
	{
		_shape.Offset((float)(x - GetX()), (float)(y - GetY()));
	}

	int Gate::GetX()									// ���o�� X �y��
	{
		return (int)_shape.GetLeft();
	}

	int Gate::GetY()									// ���o�� Y �y��
	{
		return (int)_shape.GetTop();
	}
}