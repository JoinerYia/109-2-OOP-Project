#pragma once

#include <string>
#include <sstream>
#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"

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
		CMovingBitmap	test;		// �m�߮ɥΪ��Ϥ�
		int				testX, testY;//�m�ߥβ��ʶZ��
	};
	*/

	// ���a����
	class Player
	{
	public:
		Player();									// �]�w�ʵe����t�׬� 10(�V�j�V�C)
		Player(int DelayCount);						// �]�w�ʵe����t�ת��`��(�V�j�V�C)
		~Player();
		void LoadBitmapPlayer(string file, int n);	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
		void OnMove();								// ���a���W�v��bitmap
		void OnShow();								// ���a���
		void SetMovingDown(bool flag);				// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);				// �]�w�O�_���b��������
		void SetMovingRight(bool flag);				// �]�w�O�_���b���k����
		void SetMovingUp(bool flag);				// �]�w�O�_���b���W����
		void SetXY(int x, int y);					// �]�w���a���W���y��
		int GetX();									// ���o���a X �y��
		int GetY();									// ���o���a Y �y��
	private:
		CAnimation		_player;				// ���a�ʵe
		int				_pointX, _pointY;		// ���a�y��
		bool			_isMovingDown;			// �O�_���b���U����
		bool			_isMovingLeft;			// �O�_���b��������
		bool			_isMovingRight;			// �O�_���b���k����
		bool			_isMovingUp;			// �O�_���b���W����
	};
	/*
	class CGameMap
	{
	public:
		CGameMap();
		void LoadBitmap();
		void OnShow();
	private:
		CMovingBitmap	blue, green;		// �ź��a��
		int map[4][5];//�a�ϯx�} index
		const int				testX, testY;//�y��
		const int MW, MH;//�a�ϼe��
	};
	*/
}