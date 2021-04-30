#pragma once

#include <string>
#include <sstream>
#include "Shape.h"
#include "Monster.h"

namespace game_framework
{
	// 玩家物件
	class MonsterJump : public Monster
	{
	public:
		MonsterJump();									// 設定動畫播放速度為 10(越大越慢)
		MonsterJump(int DelayCount);			// 設定玩家類別 及 動畫播放速度的常數(越大越慢)
		~MonsterJump();

		void OnMove() override;						// 玩家依頻率更換bitmap
		void OnShow() override;						// 玩家顯示

		void SetJumping(bool flag);					// 設定是否正在跳躍
		void SetGrounded(bool flag);				// 設定是否已經落地

		void ChangeGravity();						// 反轉重力
	private:
		RectangleF		 _shape;					// 玩家的中心座標及大小
		bool			_isJumping;					// 是否正在跳躍
		bool			_isGrounded;				// 是否已經落地
		void Init(int x, int y, int DelayCount);//初始化設定
		//Offset									//移動玩家座標
		//SetXY										//設定玩家座標
		//GetX										//取得玩家X座標
		//GetY										//取得玩家Y座標
	};
}