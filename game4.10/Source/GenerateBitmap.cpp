#include "GenerateBitmap.h"

namespace game_framework
{
	//生成Bmp圖片，傳遞RGB值，傳遞圖片像素大小，傳遞圖片存儲路徑
	void GenerateBitmap::generateBmp(BYTE* pData, int width, int height, char* filename)
	{
		int size = width * height * 3;	// 每個像素點3個字節
		// 位圖第一部分，文件信息
		BMPFILEHEADER_T bfh;
		bfh.bfType = 0X4d42;			// bm
		bfh.bfSize = size				// data size
			+ sizeof(BMPFILEHEADER_T)	// first section size
			+ sizeof(BMPINFOHEADER_T)	// second section size
			;
		bfh.bfReserved1 = 0;			// reserved
		bfh.bfReserved2 = 0;			// reserved
		bfh.bfOffBits = bfh.bfSize - size;

		// 位圖第二部分，數據信息
		BMPINFOHEADER_T bih;
		bih.biSize = sizeof(BMPINFOHEADER_T);
		bih.biWidth = width;
		bih.biHeight = height;
		bih.biPlanes = 1;
		bih.biBitCount = 24;
		bih.biCompression = 0;
		bih.biSizeImage = size;
		bih.biXPelsPerMeter = 0;
		bih.biYPelsPerMeter = 0;
		bih.biClrUsed = 0;
		bih.biClrImportant = 0;
		FILE* fp = fopen(filename, "wb");
		if (!fp) return;
		fwrite(&bfh, 1, sizeof(BMPFILEHEADER_T), fp);
		fwrite(&bih, 1, sizeof(BMPINFOHEADER_T), fp);
		fwrite(pData, 1, size, fp);
		fclose(fp);
	}

	void GenerateBitmap::CreateBitmapFile(char* filePath, int width, int height)
	{
		BYTE_BITMAP** pRGB = new BYTE_BITMAP*[height];	// 定義位圖數據
		//BYTE_BITMAP pRGB[240][480];	// 定義位圖數據
		for (int i = 0; i < height; i++)
		{
			pRGB[i] = new BYTE_BITMAP[width];
		}
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				// 設置背景為黑色
				pRGB[i][j].r = 0x00;
				pRGB[i][j].g = 0x00;
				pRGB[i][j].b = 0x00;
				
			}
		}
		//memset(pRGB, 0, sizeof(pRGB));		// 設置背景為黑色
		// 畫一個白色的矩形
		/*
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				pRGB[i, j].r = 0xff;
				pRGB[i, j].g = 0xff;
				pRGB[i, j].b = 0xff;
			}
		}*/
		// 生成BMP圖片
		generateBmp((BYTE*)pRGB, width, height, filePath);
		/*
		for (int i = 0; i < height; i++)
			delete pRGB[i];
		delete pRGB;
		*/
	}
}