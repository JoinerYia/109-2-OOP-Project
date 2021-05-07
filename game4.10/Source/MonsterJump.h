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
		MonsterJump(int type);						// 設定怪物類別
		~MonsterJump();

		void LoadBitmapMonster(string file);		// 從路徑 "file" 新增圖形
		void OnMove() override;						// 設定怪物座標
		void OnShow() override;						// 怪物顯示

		void SetJumping(bool flag);					// 設定是否正在跳躍
		void SetGrounded(bool flag);				// 設定是否已經落地

		void ChangeGravity();						// 反轉重力
	private:
		RectangleF		 _shape;					// 怪物的中心座標及大小
		CMovingBitmap	_Monster;					// 怪物圖片
		bool			_isJumping;					// 是否正在跳躍
		bool			_isGrounded;				// 是否已經落地
		//int			_type;						// 是幾號怪物
		void Init(int x, int y, int type);			// 初始化設定
		//Offset									// 移動怪物座標
		//SetXY										// 設定怪物座標
		//GetX										// 取得怪物X座標
		//GetY										// 取得怪物Y座標
	};
}