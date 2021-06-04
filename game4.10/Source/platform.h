#pragma once

#include <string>
#include <sstream>
#include "Shape.h"
#include "Entity.h"

namespace game_framework
{
	// 平台物件
	class platform : public Entity
	{
	public:
		platform();									// 設定動畫播放速度為 10(越大越慢)
		platform(int DelayCount);						// 設定平台類別 及 動畫播放速度的常數(越大越慢)
		platform(int x, int y);
		platform(int x, int y, int DelayCount);
		~platform();

		void LoadBitmapEntity() override;	// 從路徑 "file(1 ~ n)" 新增 n 張圖形
		void OnMove() override;						// 平台依頻率更換bitmap
		void OnShow() override;						// 平台顯示
		int isCollision(Entity entity) override;

		void SetStartX(int x);						// 設定一開始的 X 座標
		void SetMoveSpace(int distance);			// 設定向右的移動距離

	private:
		//RectangleF		 _shape;					// 平台的中心座標及大小
		CAnimation		_platform_left, _platform_right;// 平台動畫
		bool			_isRightOrLeft;				// False往右移動 True往左移動
		int				_startX;					// 一開始的 X 座標
		int				_moveSpace;					// 左右移動的距離
		int				_yCenter;					//平台與平台對應的球的中心
		//int			_type;						// 是幾號平台
		void Init(int x, int y, int DelayCount);	//初始化設定
		//Offset									// 移動平台座標
		//SetXY										// 設定平台座標
		//GetX										// 取得平台X座標
		//GetY										// 取得平台Y座標
	};
}