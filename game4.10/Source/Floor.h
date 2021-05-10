#pragma once
#include "Shape.h"
#include "GenerateBitmap.h"

namespace game_framework
{
	class Floor
	{

	private:
		RectangleF _shape;
		CMovingBitmap _floor;					//�a�O
		int _x;
		int _y;
		int _width;
		int _height;
		void Init(int x, int y, int width, int height);

	public:
		Floor();
		Floor(int width, int height);
		Floor(int x, int y, int width, int height);
		~Floor();

		void LoadBitmapMonster(char* file);	// �q���| file �s�W�ϧ�
		//Offset ���ʦa�O�y��
		//SetXY �]�w�a�O�y��
		bool isCollision(ShapeF& shape);		//�P�_�O�_�I��a�O
		void OnShow();							// �a�O���

		void Offset(int dx, int dy);
		void SetXY(int x, int y);

		int GetX() const;
		int GetY() const;
		ShapeF GetShapeF();
	};
}