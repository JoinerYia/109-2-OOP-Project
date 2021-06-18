/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
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
	// �o��class���C�����C���}�Y�e������
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
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
		//
		// �}�l���J���
		//
		logo.LoadBitmap(IDB_BACKGROUND);
		//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
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
			GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
		else if (nChar == KEY_ESC)								// Demo �����C������k
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
	}

	void CGameStateInit::OnShow()
	{
		//
		// �K�Wlogo
		//
		logo.SetTopLeft((SIZE_X - logo.Width()) / 2, SIZE_Y / 8);
		logo.ShowBitmap();
		//
		// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
		//
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		pDC->TextOut(120, 220, "Please click mouse or press SPACE to begin.");
		pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");
		if (ENABLE_GAME_PAUSE)
			pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");
		pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
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
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
		//
		// �}�l���J���
		//
		//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// �̲׶i�׬�100%
		//
		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		sprintf(str, "Game Over ! (%d)", counter / 30);
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g)
	{
		//ball = new CBall [NUMBALLS];
		//testX = testY = 0;

		isAutoDisplay = false;

		player1 = Player(0, SIZE_Y / 2 - 100, 1);				// ���a�ʵe����t�ת��`�ƥιw�]��(�V�j�V�C)
		player2 = Player(50, SIZE_Y / 2 - 100, 2);				// ���a�ʵe����t�ת��`�ƥιw�]��(�V�j�V�C)
		gates.push_back(Gate(300, SIZE_Y / 2 - 30));// ���ʵe����t�ת��`�ƥιw�]��(�V�j�V�C)
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
		/*for (int i = 0; i < NUMBALLS; i++) {				// �]�w�y���_�l�y��
			int x_pos = i % BALL_PER_ROW;
			int y_pos = i / BALL_PER_ROW;
			ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
			ball[i].SetDelay(x_pos);
			ball[i].SetIsAlive(true);
		}
		eraser.Initialize();//*/
		background.SetTopLeft(0, 0);				// �]�w�I�����_�l�y��
		//help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
		//hits_left.SetInteger(player1.GetX());					// ���w�ѤU��������
		//hits_left.SetTopLeft(HITS_LEFT_X, HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
		//CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
		//CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
		//CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI
	}

	void CGameStateRun::OnMove()							// ���ʹC������
	{
		//
		// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
		//
		// ���ʭI���Ϫ��y��
		//

		if (isAutoDisplay)
			AutoDisplay();

		background.SetTopLeft((SIZE_X - background.Width()) / 2, (SIZE_Y - background.Height()) / 2);

		//���ɼ���
		//CAudio::Instance()->Play(AUDIO_DING);
		//���ɰ���
		//CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
		//CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
		//�C������
		//GotoGameState(GAME_STATE_OVER);
		//
		// ���ʼu�����y
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


		// ��v������
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

	void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
		//
		// �}�l���J���
		//
		//int i;
		//for (i = 0; i < NUMBALLS; i++)	
		//	ball[i].LoadBitmap();								// ���J��i�Ӳy���ϧ�
		//eraser.LoadBitmap();
		background.LoadBitmap(IDB_BACKGROUND);					// ���J�I�����ϧ�
		//test.LoadBitmap(IDB_TIGER, RGB(255, 255, 255));			// �m�߮ɥΪ��Ϥ�

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
		//floor1.LoadBitmapPlayer("E:/X/�O�_��ޤj��/109-2-OOP-Project/game4.10/rgb.bmp");
		//gameMap.LoadBitmap();
		//
		// ��������Loading�ʧ@�A�����i��
		//
		ShowInitProgress(50);
		//Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// �~����J��L���
		//
		//help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// ���J�������ϧ�
		//corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
		//corner.ShowBitmap(background);							// �Ncorner�K��background
		//bball.LoadBitmap();										// ���J�ϧ�
		//hits_left.LoadBitmap();
		CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
		CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
		CAudio::Instance()->Load(AUDIO_NTUT, "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
		//
		// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
		//
	}

	//��L�������
	#pragma region KeyControl

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) //�B�z��L�������񪺰ʧ@
	{
		const char KEY_LEFT = 0x25;		// keyboard���b�Y
		const char KEY_UP = 0x26;		// keyboard�W�b�Y
		const char KEY_RIGHT = 0x27;	// keyboard�k�b�Y
		const char KEY_DOWN = 0x28;		// keyboard�U�b�Y
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

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) //�B�z��L�������񪺰ʧ@ 
	{
		const char KEY_LEFT = 0x25;		// keyboard���b�Y
		const char KEY_UP = 0x26;		// keyboard�W�b�Y
		const char KEY_RIGHT = 0x27;	// keyboard�k�b�Y
		const char KEY_DOWN = 0x28;		// keyboard�U�b�Y
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


	//�ƹ�����������
	#pragma region MouseControl

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʪ��ʧ@
	{

	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{

	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{

	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ��k����U���ʧ@
	{

	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ��k�����񪺰ʧ@
	{

	}

	#pragma endregion


	void CGameStateRun::OnShow()
	{
		//
		//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
		//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
		//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
		//
		//
		//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
		//
		background.ShowBitmap();			// �K�W�I����
		//help.ShowBitmap();					// �K�W������
		//hits_left.ShowBitmap();
		//for (int i=0; i < NUMBALLS; i++)
		//	ball[i].OnShow();				// �K�W��i���y
		//bball.OnShow();						// �K�W�u�����y
		//eraser.OnShow();					// �K�W���l
		//
		//  �K�W���W�Υk�U��������
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