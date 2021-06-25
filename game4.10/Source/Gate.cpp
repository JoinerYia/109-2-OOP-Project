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

		if (width > height) {
			_shape = RectangleF((float)width - 80, (float)height - 2);//���]�I���c
			_shape.SetLeftTop((float)x + 40, (float)y + 1);			//���]�y��
		}
		else {
			_shape = RectangleF((float)width - 2, (float)height - 80);//���]�I���c
			_shape.SetLeftTop((float)x + 1, (float)y + 40);			//���]�y��
		}//*/
		_Gate.SetDelayCount(DelayCount);				//�w�]��
	}

	Gate::Gate()										// �]�w�ʵe����t�׬� 10(�V�j�V�C)
	{
		Init(0, 0, 240, 60, 10);
	}

	Gate::Gate(int DelayCount)							// �]�w�ʵe����t�ת��`��(�V�j�V�C)
	{
		Init(0, 0, 240, 60, DelayCount);
	}

	Gate::Gate(int x, int y)							// �]�w�ʵe����t�׬� 10(�V�j�V�C)
	{
		Init(x, y, 240, 60, 10);
	}

	Gate::Gate(int x, int y, bool isVertical)
	{
		if(isVertical) Init(x, y, 60, 240, 10);
		else Init(x, y, 240, 60, 10);
	}

	Gate::~Gate() {	}

	void Gate::LoadBitmapGate(string file, int n)		// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
	{
		for (int i = 1; i <= n; i++)
		{
			//Ū���ʵe�Ϥ�
			stringstream fileString1;
			if (_shape.GetWidth() > _shape.GetHeight())
				fileString1 << file << i << ".bmp";
			else fileString1 << file << i << "_ver.bmp";
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
		/*
		CDC* myDC = CDDraw::GetBackCDC();
		myDC->SelectObject(GetStockObject(NULL_BRUSH));
		//myDC->SelectObject(GetStock)
		myDC->Rectangle((int)_shape.GetLeft(), (int)_shape.GetTop(), (int)_shape.GetRight(), (int)_shape.GetBottom());

		CDDraw::ReleaseBackCDC();//*/

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

	int Gate::GetX() const { 
		if (_shape.GetWidth() > _shape.GetHeight())
			return (int)_shape.GetLeft() - 40;
		else return (int)_shape.GetLeft();
	}
	int Gate::GetY() const {
		if (_shape.GetWidth() > _shape.GetHeight())
			return (int)_shape.GetTop();
		else return (int)_shape.GetTop() - 40;
	}
	ShapeF Gate::GetShapeF() { return _shape; }
}