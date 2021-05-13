#pragma once

#include <string>
#include <sstream>
#include "Shape.h"
#include "Entity.h"

namespace game_framework
{
	// 玩家物件
	class MonsterJump : public Entity
	{
	public:
		MonsterJump();								// 預設設定
		MonsterJump(int x, int y);					// 設定怪物位置
		~MonsterJump();

		void LoadBitmapEntity() override;			// 從路徑 "file" 新增圖形
		void OnMove() override;						// 設定怪物座標
		void OnShow() override;						// 怪物顯示
		int isCollision(Entity entity) override;

	private:
		//RectangleF		 _shape;					// 怪物的中心座標及大小
		CMovingBitmap	_Monster, _MonsterBall;		// 怪物圖片、與怪物對應的球圖片
		ShapeF*			_shadow;
		bool			_isGrounded;				// 是否已經落地
		int				_yCenter;					//怪物與怪物對應的球的中心
		//int			_type;						// 是幾號怪物
		void Init(int x, int y);					// 初始化設定
		//Offset									// 移動怪物座標
		//SetXY										// 設定怪物座標
		//GetX										// 取得怪物X座標
		//GetY										// 取得怪物Y座標
	};
}