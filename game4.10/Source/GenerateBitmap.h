#pragma once
// 產生 Bitmap
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

		//位圖文件頭文件定義
		//其中不包括文件類型信息（由於結構體的內存結構決定，要是加了的話將不能正確的讀取文件信息）
		typedef struct {
			WORD bfType;		//文件類型，必須是0x424D,即字符“BM”
			DWORD bfSize;		//文件大小
			WORD bfReserved1;	//保留字
			WORD bfReserved2;	//保留字
			DWORD bfOffBits;	//從文件頭到實際位圖數據的偏移字節數
		} BMPFILEHEADER_T;

		struct BMPFILEHEADER_S {
			WORD    bfType;
			DWORD   bfSize;
			WORD    bfReserved1;
			WORD    bfReserved2;
			DWORD   bfOffBits;
		};

		typedef struct {
			DWORD biSize;			//信息頭大小
			LONG biWidth;			//圖像寬度
			LONG biHeight;			//圖像高度
			WORD biPlanes;			//位平面數，必須為1
			WORD biBitCount;		//每像素位數
			DWORD biCompression;	//壓縮類型
			DWORD biSizeImage;		//壓縮圖像大小字節數
			LONG biXPelsPerMeter;	//水平分辨率
			LONG biYPelsPerMeter;	//垂直分辨率
			DWORD biClrUsed;		//位圖實際用到的色彩數
			DWORD biClrImportant;	//本位圖中重要的色彩數
		} BMPINFOHEADER_T;			//位圖信息頭定義

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

		//生成Bmp圖片，傳遞RGB值，傳遞圖片像素大小，傳遞圖片存儲路徑
		void generateBmp(BYTE* pData, int width, int height, char* filename);

	public:
		void GenerateBitmap::CreateBitmapFile(char* filePath, int width, int height);
	};
}