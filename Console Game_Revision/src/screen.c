#include "screen.h"

HWND getConsoleWindowHandle() {
	WCHAR title[2048] = { 0 };
	GetConsoleTitle(title, 2048);
	HWND hWnd = FindWindow(NULL, title);
	SetConsoleTitle(title);
	return hWnd;
}

int GetDPI(HWND hWnd) {
	HANDLE user32 = GetModuleHandle(TEXT("user32"));
	FARPROC func = GetProcAddress(user32, "GetDpiForWindow");
	if (func == NULL) return 96;
	return((UINT(__stdcall*)(HWND))func)(hWnd);
}

void GetBMP(HDC hdc, HDC memdc, HBITMAP image) {
	BITMAP bitmap;
	HDC bitmapDC = CreateCompatibleDC(hdc);
	GetObject(image, sizeof(bitmap), &bitmap);
	SelectObject(bitmapDC, image);
	BitBlt(memdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bitmapDC, 0, 0, SRCCOPY);
	DeleteDC(bitmapDC);
}

void paint(HWND hWnd, int dpi, HBITMAP image, int sizex, int sizey) {
	HDC hdc = GetDC(hWnd);
	HDC memdc = CreateCompatibleDC(hdc);
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, sizex, sizey);
	SelectObject(memdc, bitmap);
	GetBMP(hdc, memdc, image);
	StretchBlt(hdc, 0, 0, sizex, sizey, memdc, 0, 0, sizex, sizey, SRCCOPY);
	DeleteDC(memdc);
	DeleteObject(bitmap);
	ReleaseDC(hWnd, hdc);
}

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

void open(HWND hWnd) {
	char open_image[5][100];
	char image_path[5][20] = {"image/open1.bmp", "image/open2.bmp", "image/open3.bmp", "image/open4.bmp", "image/open5.bmp"};
	int dpi = GetDPI(hWnd);
	HBITMAP im[5];

	system("color 0f");
	cls();
	Sleep(972);
	system("color 7f");
	Sleep(324);

	for (int i = 0; i < 5; i++) {
		sprintf(open_image[i], image_path[i]);
		im[i] = (HBITMAP)LoadImage(NULL, open_image[i], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	for (int i = 0; i < 5; i++) {
		paint(hWnd, dpi, im[i], 800, 800);
		if (i != 4) {
			Sleep((i ? 2450 : 2508));
			cls();
			Sleep(85);
		}
		else {
			Sleep(2240);
			cls();
			Sleep(280);
		}
	}
	system("color 0f");
}