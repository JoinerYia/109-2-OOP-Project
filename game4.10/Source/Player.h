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
		CMovingBitmap	test;		// �m�߮ɥΪ��Ϥ�
		int				testX, testY;//�m�ߥβ��ʶZ��
	};
	*/

	// ���a����
	class Player : public Entity
	{
	public:
		Player();									// �]�w�ʵe����t�׬� 10(�V�j�V�C)
		Player(int type);							// �]�w���a���O �� �ʵe����t�׬� 10(�V�j�V�C)
		Player(int type, int DelayCount);			// �]�w���a���O �� �ʵe����t�ת��`��(�V�j�V�C)
		~Player();

		void LoadBitmapPlayer(string file, int n);	// �q���| "file(1 ~ n)" �s�W n �i�ϧ�
		void OnMove() override;						// ���a���W�v��bitmap
		void OnShow() override;						// ���a���

		void SetMovingLeft(bool flag);				// �]�w�O�_���b��������
		void SetMovingRight(bool flag);				// �]�w�O�_���b���k����
		void SetJumping(bool flag);					// �]�w�O�_���b���D
		void SetGrounded(bool flag);				// �]�w�O�_�w�g���a
		void SetPassed(bool flag);					// �]�w�O�_�w�g�q�L�ǰe��

		void ChangeGravity();						// ���୫�O
	private:
		RectangleF		 _shape;					// ���a�����߮y�ФΤj�p
		CAnimation		_player_left, _player_right;// ���a�ʵe
		bool			_isMovingLeft;				// �O�_���b��������
		bool			_isMovingRight;				// �O�_���b���k����
		bool			_isJumping;					// �O�_���b���D
		bool			_isGrounded;				// �O�_�w�g���a
		bool			_isPassed;					// �O�_�w�g�q�L�ǰe��
		bool			_endLeftRight;				// �̫�O�����٬O���k(true ��ܥ�)
		//int			_type;						// �O�X�����a
		void Init(int x, int y, int type, int DelayCount);//��l�Ƴ]�w
		//Offset									//���ʪ��a�y��
		//SetXY										//�]�w���a�y��
		//GetX										//���o���aX�y��
		//GetY										//���o���aY�y��
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