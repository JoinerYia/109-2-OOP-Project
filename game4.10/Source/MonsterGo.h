#pragma once

#include <string>
#include <sstream>
#include "Shape.h"
#include "Entity.h"

namespace game_framework
{
	// 怪物物件
	class MonsterGo : public Entity
	{
	public:
		MonsterGo();									// 設定動畫播放速度為 10(越大越慢)
		MonsterGo(int DelayCount);						// 設定怪物類別 及 動畫播放速度的常數(越大越慢)
		MonsterGo(int x, int y);
		MonsterGo(int x, int y, int DelayCount);
		~MonsterGo();

		void LoadBitmapMonster(string file, int n);	// 從路徑 "file(1 ~ n)" 新增 n 張圖形
		void OnMove() override;						// 怪物依頻率更換bitmap
		void OnShow() override;						// 怪物顯示

		void SetMovingLeft(bool flag);				// 設定是否正在往左移動
		void SetMovingRight(bool flag);				// 設定是否正在往右移動
		void SetJumping(bool flag);					// 設定是否正在跳躍
		void SetGrounded(bool flag);				// 設定是否已經落地
		void SetPassed(bool flag);					// 設定是否已經通過傳送門
		void SetStartX(int x);						// 設定一開始的 X 座標

		void ChangeGravity();						// 反轉重力
	private:
		//RectangleF		 _shape;					// 怪物的中心座標及大小
		CAnimation		_Monster_left, _Monster_right;// 怪物動畫
		bool			_isMovingLeft;				// 是否正在往左移動
		bool			_isMovingRight;				// 是否正在往右移動
		bool			_isJumping;					// 是否正在跳躍
		bool			_isGrounded;				// 是否已經落地
		bool			_isPassed;					// 是否已經通過傳送門
		bool			_endLeftRight;				// 最後是往左還是往右(true 表示左)
		int				_startX;					// 一開始的 X 座標
		int				_moveSpace;					// 左右移動的距離
		//int			_type;						// 是幾號怪物
		void Init(int x, int y, int DelayCount);	//初始化設定
		//Offset									// 移動怪物座標
		//SetXY										// 設定怪物座標
		//GetX										// 取得怪物X座標
		//GetY										// 取得怪物Y座標
	};
}