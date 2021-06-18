/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
//#include <iostream>
//#include <fstream>
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <iostream>

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////
	int Abs(int value) {
		if (value < 0)
			return -value;
		else return value;
	}
	
	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(0);	// 一開始的loading進度為0%
		//
		// 開始載入資料
		//
		logo.LoadBitmap(IDB_BACKGROUND);
		//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateInit::OnBeginState()
	{
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_SPACE = ' ';
		if (nChar == KEY_SPACE)
			GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
		else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
	}

	void CGameStateInit::OnShow()
	{
		//
		// 貼上logo
		//
		logo.SetTopLeft((SIZE_X - logo.Width()) / 2, SIZE_Y / 8);
		logo.ShowBitmap();
		//
		// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
		//
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		pDC->TextOut(120, 220, "Please click mouse or press SPACE to begin.");
		pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");
		if (ENABLE_GAME_PAUSE)
			pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");
		pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		//
		// 開始載入資料
		//
		//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 最終進度為100%
		//
		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "Game Over ! (%d)", counter / 30);
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g)
	{
		//ball = new CBall [NUMBALLS];
		//testX = testY = 0;

		isAutoDisplay = false;

		player1 = Player(0, SIZE_Y / 2 - 100, 1);				// 玩家動畫播放速度的常數用預設值(越大越慢)
		player2 = Player(50, SIZE_Y / 2 - 100, 2);				// 玩家動畫播放速度的常數用預設值(越大越慢)
		gates.push_back(Gate(300, SIZE_Y / 2 - 30));// 門動畫播放速度的常數用預設值(越大越慢)
		gates.push_back(Gate(1080, SIZE_Y / 2 - 30));

		floors.push_back(Floor(-100, SIZE_Y / 2 - 15, 400, 30));
		floors.push_back(Floor(540, SIZE_Y / 2 - 15, 540, 30));
		floors.push_back(Floor(1320, SIZE_Y / 2 - 15, 810, 30));
		floors.push_back(Floor(1320 + 810, SIZE_Y / 2 - 15, 2810, 30));

		for (int i = 0; i < 4; i++)
		{
			_monster.push_back(new MonsterJump(640 + 100 * i, SIZE_Y / 2 - 100));
		}

		MonsterGo tmpMonGo;
		for (int i = 0; i < 4; i++)
		{
			_monster.push_back(new MonsterGo(1350 + i * 70, SIZE_Y / 2 - 45));
		}

		platform tmpPlatformGo;
		for (int i = 0; i < 2; i++)
		{
			tmpPlatformGo = platform(550 + i * 70, SIZE_Y / 2 - 57);
			_platformGo.push_back(tmpPlatformGo);
		}

		/*
		_monsterJump = new MonsterJump[_monsterJumpCount];
		for (int i = 0; i < _monsterJumpCount; i++)
		{
			_monsterJump[i] = MonsterJump(i);
			_monsterJump[i].Offset(1100 - i * 100, 50);
		}
		_monsterGo = new MonsterGo[_monsterGoCount];
		for (int i = 0; i < _monsterGoCount; i++)
		{
			_monsterGo[i] = MonsterGo(i);
			_monsterGo[i].Offset(1100 - i * 100, 50);
			_monsterGo[i].SetStartX(1100 - i * 100);
		}
		//*/

	}

	CGameStateRun::~CGameStateRun()
	{
		//delete [] ball;
	}

	void CGameStateRun::OnBeginState()
	{
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 45;
		const int BALL_PER_ROW = 7;
		const int HITS_LEFT = 10;
		const int HITS_LEFT_X = 590;
		const int HITS_LEFT_Y = 0;
		const int ANIMATION_SPEED = 15;
		/*for (int i = 0; i < NUMBALLS; i++) {				// 設定球的起始座標
			int x_pos = i % BALL_PER_ROW;
			int y_pos = i / BALL_PER_ROW;
			ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
			ball[i].SetDelay(x_pos);
			ball[i].SetIsAlive(true);
		}
		eraser.Initialize();//*/
		background.SetTopLeft(0, 0);				// 設定背景的起始座標
		//help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
		//hits_left.SetInteger(player1.GetX());					// 指定剩下的撞擊數
		//hits_left.SetTopLeft(HITS_LEFT_X, HITS_LEFT_Y);		// 指定剩下撞擊數的座標
		//CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
		//CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
		//CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI
	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		//
		// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
		//
		// 移動背景圖的座標
		//

		if (isAutoDisplay)
			AutoDisplay();

		background.SetTopLeft((SIZE_X - background.Width()) / 2, (SIZE_Y - background.Height()) / 2);

		//音檔撥放
		//CAudio::Instance()->Play(AUDIO_DING);
		//音檔停止
		//CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
		//CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
		//遊戲停止
		//GotoGameState(GAME_STATE_OVER);
		//
		// 移動彈跳的球
		//
		//bball.OnMove();
		//c_test.OnMove();
		bool isPlayer1Grouded = false,
			isPlayer2Grouded = false,
			isPlayer1Passed = false,
			isPlayer2Passed = false;
		bool isP1R = player1.isMovingRight(),
			isP1L = player1.isMovingLeft(),
			isP2R = player2.isMovingRight(),
			isP2L = player2.isMovingLeft();
		//*
		if (player1.isJumping() || player2.isJumping())
		{
			if (player1.GetGravity() > 0) {
				if (player1.isJumping() || player2.GetY() - player1.GetY() > 45)
				{
					if (player1.GetShape()->isShapeCoverWithDepart(player2.GetShape(), 2)) {
						if (player2.GetY() - player1.GetY() > 45)
						{
							isPlayer1Grouded = true;
							if (!player1.isMoving()) {
								player1.SetMovingLeft(player2.isMovingLeft());
								player1.SetMovingRight(player2.isMovingRight());
							}
						}
						else if (player1.GetY() - player2.GetY() > 55)
						{
							isPlayer2Grouded = true;
							if (!player2.isMoving()) {
								player2.SetMovingLeft(player1.isMovingLeft());
								player2.SetMovingRight(player1.isMovingRight());
							}
						}
					}
				}
			}
			else {
				if (player1.isJumping() || player1.GetY() - player2.GetY() > 55)
				{
					if (player1.GetShape()->isShapeCoverWithDepart(player2.GetShape(), 2)) {
						if (player1.GetY() - player2.GetY() > 55)
						{
							isPlayer1Grouded = true;
							if (!player1.isMoving()) {
								player1.SetMovingLeft(player2.isMovingLeft());
								player1.SetMovingRight(player2.isMovingRight());
							}
						}
						else if (player2.GetY() - player1.GetY() > 45)
						{
							isPlayer2Grouded = true;
							if (!player2.isMoving()) {
								player2.SetMovingLeft(player1.isMovingLeft());
								player2.SetMovingRight(player1.isMovingRight());
							}
						}
					}
				}
			}

			if (player2.GetGravity() > 0) {
				if (player2.isJumping() || player1.GetY() - player2.GetY() > 55)
				{
					if (player2.GetShape()->isShapeCoverWithDepart(player1.GetShape(), 2)) {
						if (player2.GetY() - player1.GetY() > 45)
						{
							isPlayer1Grouded = true;
							if (!player1.isMoving()) {
								player1.SetMovingLeft(player2.isMovingLeft());
								player1.SetMovingRight(player2.isMovingRight());
							}
						}
						else if (player1.GetY() - player2.GetY() > 55)
						{
							isPlayer2Grouded = true;
							if (!player2.isMoving()) {
								player2.SetMovingLeft(player1.isMovingLeft());
								player2.SetMovingRight(player1.isMovingRight());
							}
						}
					}
				}
			}
			else {
				if (player2.isJumping() || player2.GetY() - player1.GetY() > 45)
				{
					if (player2.GetShape()->isShapeCoverWithDepart(player1.GetShape(), 2)) {
						if (player1.GetY() - player2.GetY() > 55)
						{
							isPlayer1Grouded = true;
							if (!player1.isMoving()) {
								player1.SetMovingLeft(player2.isMovingLeft());
								player1.SetMovingRight(player2.isMovingRight());
							}
						}
						else if (player2.GetY() - player1.GetY() > 45)
						{
							isPlayer2Grouded = true;
							if (!player2.isMoving()) {
								player2.SetMovingLeft(player1.isMovingLeft());
								player2.SetMovingRight(player1.isMovingRight());
							}
						}
					}
				}
			}
		}
		else {
			if (player1.GetShape()->isShapeCoverWithDepart(player2.GetShape(), 3)) {
				if (player2.GetY() - player1.GetY() > 45)
				{
					if (player1.GetGravity() > 0)
					{
						isPlayer1Grouded = true;
						if (!player1.isMoving()) {
							player1.SetMovingLeft(player2.isMovingLeft());
							player1.SetMovingRight(player2.isMovingRight());
						}
					}
					if (player2.GetGravity() < 0)
					{
						isPlayer2Grouded = true;
						if (!player2.isMoving()) {
							player2.SetMovingLeft(player1.isMovingLeft());
							player2.SetMovingRight(player1.isMovingRight());
						}
					}
				}
				else if (player1.GetY() - player2.GetY() > 55)
				{
					if (player2.GetGravity() > 0)
					{
						isPlayer2Grouded = true;
						if (!player2.isMoving()) {
							player2.SetMovingLeft(player1.isMovingLeft());
							player2.SetMovingRight(player1.isMovingRight());
						}
					}
					if (player1.GetGravity() < 0)
					{
						isPlayer1Grouded = true;
						if (!player1.isMoving()) {
							player1.SetMovingLeft(player2.isMovingLeft());
							player1.SetMovingRight(player2.isMovingRight());
						}
					}
				}
			}
		}//*/

		int numberOfPlatform = _platformGo.end() - _platformGo.begin();
		vector<platform>::iterator platformGo;
		for (int i = 0; i < numberOfPlatform; i++)
		{
			platformGo = _platformGo.begin() + i;
			isPlayer1Grouded |= platformGo->isCollision(player1) == 1;
			isPlayer2Grouded |= platformGo->isCollision(player2) == 1;
			platformGo->OnMove();
		}

		for (vector<Floor>::iterator floor = floors.begin(); floor != floors.end(); floor++)
		{
			isPlayer1Grouded |= floor->isCollision(player1);
			isPlayer2Grouded |= floor->isCollision(player2);
		}
		for (vector<Gate>::iterator gate = gates.begin(); gate != gates.end(); gate++)
		{
			isPlayer1Passed |= gate->isCollision(player1);
			isPlayer2Passed |= gate->isCollision(player2);
			gate->OnMove();
		}
		player1.SetGrounded(isPlayer1Grouded && !isPlayer1Passed);
		player2.SetGrounded(isPlayer2Grouded && !isPlayer2Passed);
		player1.SetPassed(isPlayer1Passed);
		player2.SetPassed(isPlayer2Passed);

		player1.OnMove();
		player2.OnMove();

		#pragma region Reset
		player1.SetMovingRight(isP1R);
		player1.SetMovingLeft(isP1L);
		player2.SetMovingRight(isP2R);
		player2.SetMovingLeft(isP2L);
		#pragma endregion


		int typeOfPlayer1Collision, typeOfPlayer2Collision;
		int numberOfMonster = _monster.end() - _monster.begin();
		vector<Entity*>::iterator monster;
		for (int i = 0; i < numberOfMonster; i++)
		{
			monster = _monster.begin() + i;
			(*monster)->OnMove();
			typeOfPlayer1Collision = (*monster)->isCollision(player1);
			typeOfPlayer2Collision = (*monster)->isCollision(player2);
			if (typeOfPlayer1Collision > 1 || typeOfPlayer2Collision > 1) {
				_monster.erase(monster);
				i--;
				numberOfMonster--;
			}
			else if (typeOfPlayer1Collision + typeOfPlayer2Collision > 0)
			{
				player1.Spawn();
				player2.Spawn();
			}
		}//*/


		// 攝影機移動
		int move_x = 0;
		int moving_ratio = 10;
		if (player1.GetX() > SIZE_X * (moving_ratio - 1) / moving_ratio && player2.GetX() > SIZE_X * (moving_ratio - 1) / moving_ratio)
		{
			move_x = 100;
		}
		else if (player1.GetX() < SIZE_X / moving_ratio && player2.GetX() < SIZE_X / moving_ratio)
		{
			move_x = -100;
		}
		player1.SetXY(player1.GetX() - move_x, player1.GetY());
		player2.SetXY(player2.GetX() - move_x, player2.GetY());

		for (int i = 0; i < numberOfPlatform; i++)
		{
			platformGo = _platformGo.begin() + i;
			platformGo->SetXY(platformGo->GetX() - move_x, platformGo->GetY());
		}

		for (vector<Floor>::iterator floor = floors.begin(); floor != floors.end(); floor++)
		{
			floor->SetXY(floor->GetX() - move_x, floor->GetY());
		}
		for (vector<Gate>::iterator gate = gates.begin(); gate != gates.end(); gate++)
		{
			gate->SetXY(gate->GetX() - move_x, gate->GetY());
		}
		for (vector<Entity*>::iterator monster = _monster.begin(); monster != _monster.end(); monster++)
		{
			(*monster)->SetXY((*monster)->GetX() - move_x, (*monster)->GetY());
		}
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		//
		// 開始載入資料
		//
		//int i;
		//for (i = 0; i < NUMBALLS; i++)	
		//	ball[i].LoadBitmap();								// 載入第i個球的圖形
		//eraser.LoadBitmap();
		background.LoadBitmap(IDB_BACKGROUND);					// 載入背景的圖形
		//test.LoadBitmap(IDB_TIGER, RGB(255, 255, 255));			// 練習時用的圖片

		//c_test.LoadBitmap();
		player1.LoadBitmapPlayer("RES/playerMove/playerMove_1_", 6);
		player2.LoadBitmapPlayer("RES/playerMove/playerMove_2_", 5);

		for (vector<Gate>::iterator gate = gates.begin(); gate != gates.end(); gate++)
		{
			gate->LoadBitmapGate("RES/gate/gate_1_", 5);
		}

		for (vector<Entity*>::iterator monster = _monster.begin(); monster != _monster.end(); monster++)
		{
			(*monster)->LoadBitmapEntity();
		}

		for (vector<platform>::iterator platformGo = _platformGo.begin(); platformGo != _platformGo.end(); platformGo++)
		{
			platformGo->LoadBitmapEntity();
		}
		//floor1.LoadBitmapPlayer("E:/X/臺北科技大學/109-2-OOP-Project/game4.10/rgb.bmp");
		//gameMap.LoadBitmap();
		//
		// 完成部分Loading動作，提高進度
		//
		ShowInitProgress(50);
		//Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 繼續載入其他資料
		//
		//help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// 載入說明的圖形
		//corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
		//corner.ShowBitmap(background);							// 將corner貼到background
		//bball.LoadBitmap();										// 載入圖形
		//hits_left.LoadBitmap();
		CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
		CAudio::Instance()->Load(AUDIO_NTUT, "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//
	}

	//鍵盤控制相關
	#pragma region KeyControl

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) //處理鍵盤按鍵釋放的動作
	{
		const char KEY_LEFT = 0x25;		// keyboard左箭頭
		const char KEY_UP = 0x26;		// keyboard上箭頭
		const char KEY_RIGHT = 0x27;	// keyboard右箭頭
		const char KEY_DOWN = 0x28;		// keyboard下箭頭
		const char KEY_W = 0x57;		// keyboard W
		const char KEY_S = 0x53;		// keyboard S
		const char KEY_A = 0x41;		// keyboard A
		const char KEY_D = 0x44;		// keyboard D
		if (nChar == KEY_LEFT)
		{
			player1.SetMovingLeft(true);
		}
		if (nChar == KEY_RIGHT)
		{
			player1.SetMovingRight(true);
		}
		if (nChar == KEY_UP)
		{
			player1.SetJumping(true);
		}
		if (nChar == KEY_DOWN)
		{
			player1.SetJumping(true);
		}
		if (nChar == KEY_W)
		{
			player2.SetJumping(true);
		}
		if (nChar == KEY_S)
		{
			player2.SetJumping(true);
		}
		if (nChar == KEY_A)
		{
			player2.SetMovingLeft(true);
		}
		if (nChar == KEY_D)
		{
			player2.SetMovingRight(true);
		}
		if (nChar == 'R')
		{
			player1.Spawn();
			player2.Spawn();

			_monster.clear();
			for (int i = 0; i < 4; i++)
			{
				_monster.push_back(new MonsterJump(640 + 100 * i, SIZE_Y / 2 - 100));
			}
			for (int i = 0; i < 4; i++)
			{
				_monster.push_back(new MonsterGo(1350 + i * 70, SIZE_Y / 2 - 45));
			}
			for (vector<Entity*>::iterator monster = _monster.begin(); monster != _monster.end(); monster++)
			{
				(*monster)->LoadBitmapEntity();
			}
			//*/

		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) //處理鍵盤按鍵釋放的動作 
	{
		const char KEY_LEFT = 0x25;		// keyboard左箭頭
		const char KEY_UP = 0x26;		// keyboard上箭頭
		const char KEY_RIGHT = 0x27;	// keyboard右箭頭
		const char KEY_DOWN = 0x28;		// keyboard下箭頭
		const char KEY_W = 0x57;		// keyboard W
		const char KEY_S = 0x53;		// keyboard S
		const char KEY_A = 0x41;		// keyboard A
		const char KEY_D = 0x44;		// keyboard D
		if (nChar == KEY_LEFT)
		{
			//eraser.SetMovingLeft(false);
			player1.SetMovingLeft(false);
		}
		if (nChar == KEY_RIGHT)
		{
			//eraser.SetMovingRight(false);
			player1.SetMovingRight(false);
		}
		if (nChar == KEY_UP)
		{
			//eraser.SetMovingUp(false);
			player1.SetJumping(false);
		}
		if (nChar == KEY_DOWN)
		{
			//eraser.SetMovingDown(false);
			player1.SetJumping(false);
		}
		if (nChar == KEY_W)
		{
			player2.SetJumping(false);
		}
		if (nChar == KEY_S)
		{
			player2.SetJumping(false);
		}
		if (nChar == KEY_A)
		{
			player2.SetMovingLeft(false);
		}
		if (nChar == KEY_D)
		{
			player2.SetMovingRight(false);
		}
		if (nChar == 'P')
		{
			indexOfAutoDisplay = 0;
			isAutoDisplay = !isAutoDisplay;
			if (!isAutoDisplay) {
				player1.SetMovingLeft(false);
				player1.SetMovingRight(false);
				player1.SetJumping(false);
				player2.SetMovingLeft(false);
				player2.SetMovingRight(false);
				player2.SetJumping(false);
			}
		}
	}

	#pragma endregion


	//滑鼠相關的控制
	#pragma region MouseControl

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠移動的動作
	{

	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠右鍵按下的動作
	{

	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠右鍵釋放的動作
	{

	}

	#pragma endregion


	void CGameStateRun::OnShow()
	{
		//
		//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
		//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
		//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
		//
		//
		//  貼上背景圖、撞擊數、球、擦子、彈跳的球
		//
		background.ShowBitmap();			// 貼上背景圖
		//help.ShowBitmap();					// 貼上說明圖
		//hits_left.ShowBitmap();
		//for (int i=0; i < NUMBALLS; i++)
		//	ball[i].OnShow();				// 貼上第i號球
		//bball.OnShow();						// 貼上彈跳的球
		//eraser.OnShow();					// 貼上擦子
		//
		//  貼上左上及右下角落的圖
		//
		//corner.SetTopLeft(0, 0);
		//corner.ShowBitmap();
		//corner.SetTopLeft(SIZE_X - corner.Width(), SIZE_Y - corner.Height());
		//corner.ShowBitmap();
		//test.ShowBitmap();
		//c_test.OnShow();

		for (vector<Entity*>::iterator monster = _monster.begin(); monster != _monster.end(); monster++)
		{
			(*monster)->OnShow();
		}

		for (vector<platform>::iterator platformGo = _platformGo.begin(); platformGo != _platformGo.end(); platformGo++)
		{
			platformGo->OnShow();
		}
		
		player1.OnShow();
		player2.OnShow();

		for (vector<Gate>::iterator gate = gates.begin(); gate != gates.end(); gate++)
		{
			gate->OnShow();
		}

		//gameMap.OnShow();
		for (vector<Floor>::iterator floor = floors.begin(); floor != floors.end(); floor++)
		{
			floor->OnShow();
		}

	}

	void CGameStateRun::AutoDisplay() {
		if (indexOfAutoDisplay == 0) {
			player1.Spawn();
			player2.Spawn();

			_monster.clear();
			for (int i = 0; i < 4; i++)
			{
				_monster.push_back(new MonsterJump(640 + 100 * i, SIZE_Y / 2 - 100));
			}
			for (int i = 0; i < 4; i++)
			{
				_monster.push_back(new MonsterGo(1350 + i * 70, SIZE_Y / 2 - 45));
			}
			for (vector<Entity*>::iterator monster = _monster.begin(); monster != _monster.end(); monster++)
			{
				(*monster)->LoadBitmapEntity();
			}
		}
		else if (indexOfAutoDisplay < 10) {
			player2.SetMovingRight(true);
		}
		else if (indexOfAutoDisplay < 20) {
			player1.SetMovingRight(true);
		}
		else if (indexOfAutoDisplay < 35) {
			player1.SetJumping(true);
			player2.SetMovingRight(false);
		}
		else if (indexOfAutoDisplay < 40) {
			player2.SetJumping(true);
		}
		else if (indexOfAutoDisplay < 45) {
			player1.SetMovingRight(true);
			player1.SetJumping(true);
		}
		else if (indexOfAutoDisplay < 60) {
			player1.SetJumping(false);
			player2.SetMovingRight(true);
			player2.SetJumping(true);
		}
		else if (indexOfAutoDisplay < 80) {
			player1.SetMovingRight(true);
			player2.SetJumping(false);
		}
		else if (indexOfAutoDisplay < 90) {
			player1.SetMovingRight(false);
			player2.SetMovingRight(false);
		}
		else if (indexOfAutoDisplay < 100) {
			player1.SetMovingRight(true);
		}
		else if (indexOfAutoDisplay < 140) {
			player1.SetMovingRight(false);
			player2.SetMovingRight(true);
		}
		else if (indexOfAutoDisplay < 160) {
			player1.SetMovingRight(true);
			player2.SetMovingRight(true);
		}
		else if (indexOfAutoDisplay < 170) {
			player1.SetJumping(true);
			player2.SetJumping(true);
		}
		else if (indexOfAutoDisplay < 200) {
			player1.SetJumping(false);
			player2.SetJumping(false);
		}
		else if (indexOfAutoDisplay < 220) {
			player1.SetMovingRight(false);
			player2.SetMovingRight(false);
		}
		else if (indexOfAutoDisplay < 230) { }
		else if (indexOfAutoDisplay < 235) {
			player1.SetMovingRight(true);
		}
		else if (indexOfAutoDisplay < 240) { }
		else if (indexOfAutoDisplay < 280) {
			player1.SetMovingRight(false);
			player2.SetMovingRight(true);
		}
		else if (indexOfAutoDisplay < 300) {
			player2.SetMovingRight(false);
		}
		else if (indexOfAutoDisplay < 340) {
			player2.SetMovingRight(true);
		}
		else if (indexOfAutoDisplay < 380) {
			player1.SetMovingRight(true);
		}
		else if (indexOfAutoDisplay < 390) {
			player1.SetMovingLeft(false);
			player1.SetMovingRight(false);
			player1.SetJumping(false);
			player2.SetMovingLeft(false);
			player2.SetMovingRight(false);
			player2.SetJumping(false);
		}
		else if (indexOfAutoDisplay < 500) {}
		else {
			//isAutoDisplay = false;
			indexOfAutoDisplay = -1;
		}
		indexOfAutoDisplay += 1;
	}
}