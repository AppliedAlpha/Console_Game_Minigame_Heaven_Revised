#pragma comment(lib, "winmm.lib")
#pragma warning(disable:4996)
#include <Windows.h>
#include <mmsystem.h>
#include "Digitalv.h"
#define WIDTH 80
#define HEIGHT 40

void init_screen() {
	// 콘솔 스크린 설정 및 제목 변경
	char chtemp[50];
	sprintf(chtemp, "mode con cols=%d lines=%d", WIDTH, HEIGHT);
	system(chtemp);
	system("title Minigames Heaven");

	// 커서 삭제
	CONSOLE_CURSOR_INFO c = { 0 };
	c.dwSize = 1;
	c.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}

void open(int dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay) {
	mciOpen.lpstrElementName = "Glacia1.mp3";
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
	dwID = mciOpen.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
	system("color 0f");
	cls();
	Sleep(972);
	system("color 7f");
	Sleep(324);
	char open1[100], open2[100], open3[100], open4[100], open5[100];
	int dpi;
	HBITMAP o1, o2, o3, o4, o5;
	HWND hWnd = getConsoleWindowHandle();
	dpi = GetDPI(hWnd);
	sprintf(open1, "Open1.bmp");
	sprintf(open2, "Open2.bmp");
	sprintf(open3, "Open3.bmp");
	sprintf(open4, "Open4.bmp");
	sprintf(open5, "Open5.bmp");
	o1 = (HBITMAP)LoadImage(NULL, open1, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	o2 = (HBITMAP)LoadImage(NULL, open2, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	o3 = (HBITMAP)LoadImage(NULL, open3, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	o4 = (HBITMAP)LoadImage(NULL, open4, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	o5 = (HBITMAP)LoadImage(NULL, open5, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	paint(hWnd, dpi, o1, 800, 800);
	Sleep(2508);
	cls();
	Sleep(85);
	paint(hWnd, dpi, o2, 800, 800);
	Sleep(2450);
	cls();
	Sleep(85);
	paint(hWnd, dpi, o3, 800, 800);
	Sleep(2450);
	cls();
	Sleep(85);
	paint(hWnd, dpi, o4, 800, 800);
	Sleep(2450);
	cls();
	Sleep(85);
	paint(hWnd, dpi, o5, 800, 800);
	Sleep(2240);
	cls();
	Sleep(280);
	system("color 0f");
}