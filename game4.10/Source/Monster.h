#pragma once

#include <string>
#include <sstream>
#include "Shape.h"
#include "Entity.h"

namespace game_framework
{
	// ���a����
	class Monster : public Entity
	{
	public:
		//void OnMove();
	private:
		Entity _monster, _shadow;
		int _yCenter, _dy;
	};
}