#pragma once

#include <string>
#include <sstream>
#include "Shape.h"

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
	class Player
	{
	public:
		Player();									// 設定動畫播放速度為 10(越大越慢)
		Player(int DelayCount);						// 設定動畫播放速度的常數(越大越慢)
		~Player();
		void LoadBitmapPlayer(string file, int n);	// 從路徑 "file(1 ~ n)" 新增 n 張圖形
		void OnMove();								// 玩家依頻率更換bitmap
		void OnShow();								// 玩家顯示
		void SetMovingDown(bool flag);				// 設定是否正在往下移動
		void SetMovingLeft(bool flag);				// 設定是否正在往左移動
		void SetMovingRight(bool flag);				// 設定是否正在往右移動
		void SetMovingUp(bool flag);				// 設定是否正在往上移動
		void Offset(int dx, int dy);				// 移動玩家座標
		void SetXY(int x, int y);					// 設定玩家左上角座標
		int GetX();									// 取得玩家 X 座標
		int GetY();									// 取得玩家 Y 座標
	private:
		RectangleF		 _shape;				// 玩家的中心座標及大小
		CAnimation		_player_left, _player_right;// 玩家動畫
		bool			_isMovingDown;			// 是否正在往下移動
		bool			_isMovingLeft;			// 是否正在往左移動
		bool			_isMovingRight;			// 是否正在往右移動
		bool			_isMovingUp;			// 是否正在往上移動
		bool			_endLeftRight;			// 最後是往左還是往右(true 表示左)
		float			_gravity;				// 玩家所受的重力加速度
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