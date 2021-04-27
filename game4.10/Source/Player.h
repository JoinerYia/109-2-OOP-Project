#pragma once

#include <string>
#include <sstream>
#include "Shape.h"
#include "Entity.h"

namespace game_framework
{
	/*
	class Ctest
	{
	public:
		Ctest();
		void LoadBitmap();
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap	test;		// 練習時用的圖片
		int				testX, testY;//練習用移動距離
	};
	*/

	// 玩家物件
	class Player : public Entity
	{
	public:
		Player();									// 設定動畫播放速度為 10(越大越慢)
		Player(int type);							// 設定玩家類別 及 動畫播放速度為 10(越大越慢)
		Player(int type, int DelayCount);			// 設定玩家類別 及 動畫播放速度的常數(越大越慢)
		~Player();

		void LoadBitmapPlayer(string file, int n);	// 從路徑 "file(1 ~ n)" 新增 n 張圖形
		void OnMove() override;						// 玩家依頻率更換bitmap
		void OnShow() override;						// 玩家顯示

		void SetMovingLeft(bool flag);				// 設定是否正在往左移動
		void SetMovingRight(bool flag);				// 設定是否正在往右移動
		void SetJumping(bool flag);					// 設定是否正在跳躍
		void SetGrounded(bool flag);				// 設定是否已經落地
		void SetPassed(bool flag);					// 設定是否已經通過傳送門

		void ChangeGravity();						// 反轉重力
	private:
		RectangleF		 _shape;					// 玩家的中心座標及大小
		CAnimation		_player_left, _player_right;// 玩家動畫
		bool			_isMovingLeft;				// 是否正在往左移動
		bool			_isMovingRight;				// 是否正在往右移動
		bool			_isJumping;					// 是否正在跳躍
		bool			_isGrounded;				// 是否已經落地
		bool			_isPassed;					// 是否已經通過傳送門
		bool			_endLeftRight;				// 最後是往左還是往右(true 表示左)
		//int			_type;						// 是幾號玩家
		void Init(int x, int y, int type, int DelayCount);//初始化設定
		//Offset									//移動玩家座標
		//SetXY										//設定玩家座標
		//GetX										//取得玩家X座標
		//GetY										//取得玩家Y座標
	};
	/*
	class CGameMap
	{
	public:
		CGameMap();
		void LoadBitmap();
		void OnShow();
	private:
		CMovingBitmap	blue, green;		// 藍綠兩地圖
		int map[4][5];//地圖矩陣 index
		const int				testX, testY;//座標
		const int MW, MH;//地圖寬高
	};
	*/
}