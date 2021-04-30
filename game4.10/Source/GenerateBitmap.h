#pragma once
// ���� Bitmap
#include <pshpack2.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

namespace game_framework
{
	class GenerateBitmap
	{
	private:
		typedef long BOOL;
		typedef long LONG;
		typedef unsigned char BYTE;
		typedef unsigned long DWORD;
		typedef unsigned short WORD;

		//��Ϥ���Y���w�q
		//�䤤���]�A��������H���]�ѩ󵲺c�骺���s���c�M�w�A�n�O�[�F���ܱN���ॿ�T��Ū�����H���^
		typedef struct {
			WORD bfType;		//��������A�����O0x424D,�Y�r�š�BM��
			DWORD bfSize;		//���j�p
			WORD bfReserved1;	//�O�d�r
			WORD bfReserved2;	//�O�d�r
			DWORD bfOffBits;	//�q����Y���ڦ�ϼƾڪ������r�`��
		} BMPFILEHEADER_T;

		struct BMPFILEHEADER_S {
			WORD    bfType;
			DWORD   bfSize;
			WORD    bfReserved1;
			WORD    bfReserved2;
			DWORD   bfOffBits;
		};

		typedef struct {
			DWORD biSize;			//�H���Y�j�p
			LONG biWidth;			//�Ϲ��e��
			LONG biHeight;			//�Ϲ�����
			WORD biPlanes;			//�쥭���ơA������1
			WORD biBitCount;		//�C�������
			DWORD biCompression;	//���Y����
			DWORD biSizeImage;		//���Y�Ϲ��j�p�r�`��
			LONG biXPelsPerMeter;	//��������v
			LONG biYPelsPerMeter;	//��������v
			DWORD biClrUsed;		//��Ϲ�ڥΨ쪺��m��
			DWORD biClrImportant;	//����Ϥ����n����m��
		} BMPINFOHEADER_T;			//��ϫH���Y�w�q

		struct BYTE_BITMAP {
			BYTE b;
			BYTE g;
			BYTE r;
		};

		/*
		struct BITMAP
		{
			BYTE_BITMAP bmp[];
			const int width, height;
			BITMAP(int width, int height) : width(width), height(height) {
				bmp = new BYTE_BITMAP[this->width, this->height];
			}
		};*/

		//�ͦ�Bmp�Ϥ��A�ǻ�RGB�ȡA�ǻ��Ϥ������j�p�A�ǻ��Ϥ��s�x���|
		void generateBmp(BYTE* pData, int width, int height, char* filename);

	public:
		void GenerateBitmap::CreateBitmapFile(char* filePath, int width, int height);
	};
}