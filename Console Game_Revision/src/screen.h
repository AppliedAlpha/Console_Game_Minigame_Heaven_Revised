#pragma once
#include "action.h"

HWND getConsoleWindowHandle();
int GetDPI(HWND hWnd);
void GetBMP(HDC hdc, HDC memdc, HBITMAP image);
void paint(HWND hWnd, int dpi, HBITMAP image, int sizex, int sizey);

void init_screen();
void open(HWND hWnd);
void draw_title(HWND hWnd);