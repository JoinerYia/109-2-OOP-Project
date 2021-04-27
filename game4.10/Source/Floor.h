#pragma once
#include "MapItem.h"
#include "Shape.h"

namespace game_framework
{
	class Floor : public MapItem
	{

	private:

		void Init(float x, float y, float width, float height);

	public:
		Floor();
		Floor(float width, float height);
		Floor(float x, float y, float width, float height);
		~Floor();

		//Offset ���ʦa�O�y��
		//SetXY �]�w�a�O�y��
		bool isCollision(ShapeF& shape);		//�P�_�O�_�I��a�O
		void OnShow();								// �a�O���
	};
}