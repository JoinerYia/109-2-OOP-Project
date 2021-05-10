#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Gate.h"

namespace game_framework
{
	void Gate::Init(int x, int y, int width, int height, int DelayCount)
	{
		_type = 0;
		_shape = RectangleF((float)width, (float)height);				//���]�I���c
		_shape.SetLeftTop((float)x, (float)y);			//���]�y��
		_Gate.SetDelayCount(DelayCount);				//�w�]��
	}

	Gate::Gate()										// �]�w�ʵe����t�׬� 10(�V�j�V�C)
	{
		Init(0, 0, 210, 60, 10);
	}

	Gate::Gate(int DelayCount)							// �]�w�ʵe����t�ת��`��(�V�j�V�C)
	{
		Init(0, 0, 210, 60, DelayCount);
	}

	Gate::Gate(int x, int y)							// �]�w�ʵe����t�׬� 10(�V�j�V�C)
	{
		Init(x, y, 210, 60, 10);
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

	bool Gate::isCollision(Entity entity)
	{
		return _shape.isShapeFCover(entity.GetShape());
	}

	void Gate::Offset(int dx, int dy) {
		_shape.Offset((float)dx, (float)dy);
	}

	void Gate::SetXY(int x, int y) {
		_shape.Offset((float)(x - GetX()), (float)(y - GetY()));
	}

	int Gate::GetX() const { return (int)_shape.GetLeft(); }
	int Gate::GetY() const { return (int)_shape.GetTop(); }
	ShapeF Gate::GetShapeF() { return _shape; }
}