#include <mmsystem.h>
#include "action.h"
int selme = 0;

void selectmenu(int selcheck) {
	char ch = 0;
	if (selcheck) PlaySound(TEXT("tp_click.wav"), 0, SND_FILENAME | SND_ASYNC);
	if (selcheck % 2) sm_np(cc_green);
	else sm_np(c_white);
	if (selcheck - 1 && selcheck > 0) sm_sp(cc_purple);
	else sm_sp(c_white);
	if (selcheck == 0) {
		tc(c_white);
		gotoxy(53, 36);
		printf("※ ←, →키로 이동합니다.");
		gotoxy(47, 38);
		printf("※ ENTER키로 항목을 선택합니다.");
	}
	while (kbhit()) getch();
	if (!selcheck) Sleep(1200);
	tc(c_white);
	while (1) {
		if (kbhit()) {
			ch = getch();
			if (ch == FUNCTION_KEY) {
				ch = getch();
				if (ch == LEFT) {
					selectmenu(1);
					return;
				}
				else if (ch == RIGHT) {
					selectmenu(2);
					return;
				}
			}
			else if (ch == ENTER) break;
		}
	}
	if (selcheck == 0) selcheck = 1;
	selme = selcheck - 1;
	return;
}

void maintitle(int selcheck) {
	char ch = 0;
	if (selcheck % 2) mt_start(cc_red);
	else mt_start(c_white);
	if (selcheck - 1 && selcheck > 0) mt_quit(cc_red);
	else mt_quit(c_white);
	gotoxy(53, 36);
	if (selcheck == 0) {
		tc(c_white);
		printf("※ ↑, ↓키로 이동합니다.");
		gotoxy(47, 38);
		printf("※ ENTER키로 항목을 선택합니다.");
	}
	tc(c_white);

	char filename[100];
	int dpi;
	HBITMAP bitmap;
	HWND hWnd = getConsoleWindowHandle();
	dpi = GetDPI(hWnd);
	sprintf(filename, "Title.bmp");
	bitmap = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	paint(hWnd, dpi, bitmap, 800, 440);
	if (!selcheck) Sleep(800);
	if (selcheck) PlaySound(TEXT("tp_click.wav"), 0, SND_FILENAME | SND_ASYNC);
	while (1) {
		if (kbhit()) {
			ch = getch();
			if (ch == FUNCTION_KEY) {
				ch = getch();
				if (ch == UP) {
					maintitle(1);
					return;
				}
				else if (ch == DOWN) {
					maintitle(2);
					return;
				}
			}
			else if (ch == ENTER) break;
		}
	}
	if (selcheck == 0) {
		maintitle(0);
		return;
	}
	if (selcheck == 2) {
		cls();
		exit(0);
	}
}
//메인 화면 출력 함수

void enter_menu(int* dwID) {
	while (1) {
		waiting();
		selectmenu(0); //메뉴 고르기
		stopAllSounds(&dwID); //소리 정지
		if (!selme) normalgame(); //노말
		else {
			cls();
			normalbound(c_gray);
			selectgame(0); //선택
		}
	}
}

void spin_number(int a) {
	tc(c_gray);
	gotoxy(7, 21);
	printf("%1d", (a + 5) % 9 + 1);
	gotoxy(19, 21);
	printf("%1d", (a + 6) % 9 + 1);
	gotoxy(31, 21);
	printf("%1d", (a + 7) % 9 + 1);
	gotoxy(49, 21);
	printf("%1d", a % 9 + 1);
	gotoxy(61, 21);
	printf("%1d", (a + 1) % 9 + 1);
	gotoxy(73, 21);
	printf("%1d", (a + 2) % 9 + 1);
	tc(cc_white);
	gotoxy(40, 21);
	printf("%1d", a);
}

void spin(int a) {
	int i;
	{
		tc(cc_yellow);
		gotoxy(32, 9);
		printf("■■■■■■■■");
		gotoxy(32, 10);
		printf("■            ■");
		gotoxy(34, 11);
		printf("■        ■");
		gotoxy(34, 12);
		printf("■        ■");
		gotoxy(36, 13);
		printf("■    ■");
		gotoxy(36, 14);
		printf("■    ■");
		gotoxy(38, 15);
		printf("■■");
		gotoxy(38, 16);
		printf("■■");
		tc(cc_cyan);
		for (i = 18; i <= 24; i++) {
			gotoxy(36, i);
			if (i == 18 || i == 24) printf("■■■■");
			else printf("■    ■");
		}
		tc(c_gray);
		gotoxy(2, 18);
		printf("■■■■■■■■■■■■■■■■■");
		gotoxy(44, 18);
		printf("■■■■■■■■■■■■■■■■■");
		gotoxy(2, 24);
		printf("■■■■■■■■■■■■■■■■■");
		gotoxy(44, 24);
		printf("■■■■■■■■■■■■■■■■■");
		for (i = 19; i <= 23; i++) {
			gotoxy(12, i);
			printf("■");
			gotoxy(24, i);
			printf("■");
			gotoxy(54, i);
			printf("■");
			gotoxy(66, i);
			printf("■");
		}
	}
	PlaySound(TEXT("spin.wav"), 0, SND_FILENAME | SND_ASYNC);
	for (i = 1; i <= 41; i++) {
		spin_number((a + i + 8) % 9 + 1);
		Sleep(50);
	}
	for (i = 42; i <= 81; i++) {
		spin_number((a + i + 8) % 9 + 1);
		Sleep(95);
	}
	for (i = 82; i <= 87; i++) {
		spin_number((a + i + 8) % 9 + 1);
		Sleep(280);
	}
	for (i = 88; i <= 90; i++) {
		spin_number((a + i + 8) % 9 + 1);
		Sleep(340);
	}
	spin_number(a);
	gotoxy(24, 30);
	tc(cc_yellow);
	printf("\"%s\"", gm[a]);
	tc(c_white);
	printf(" 게임을 시작합니다!");
	Sleep(2000);
}

void explain(int a) {
	char name[100], explain[100], howto[100], ready[100], go[100];
	int dpi;
	HBITMAP nm, ex, ht, rd, g;
	HWND hWnd = getConsoleWindowHandle();
	dpi = GetDPI(hWnd);
	sprintf(explain, "explain.bmp");
	sprintf(ready, "ready.bmp");
	sprintf(go, "go.bmp");
	switch (a) {
	case 1: sprintf(name, "1.bmp"); break;
	case 2: sprintf(name, "2.bmp"); break;
	case 3: sprintf(name, "3.bmp"); break;
	case 4: sprintf(name, "4.bmp"); break;
	case 5: sprintf(name, "5.bmp"); break;
	case 6: sprintf(name, "6.bmp"); break;
	case 7: sprintf(name, "7.bmp"); break;
	case 8: sprintf(name, "8.bmp"); break;
	case 9: sprintf(name, "9.bmp"); break;
	}
	switch (a) {
	case 1: sprintf(howto, "h1.bmp"); break;
	case 2: sprintf(howto, "h2.bmp"); break;
	case 3: sprintf(howto, "h3.bmp"); break;
	case 4: sprintf(howto, "h4.bmp"); break;
	case 5: sprintf(howto, "h5.bmp"); break;
	case 6: sprintf(howto, "h6.bmp"); break;
	case 7: sprintf(howto, "h7.bmp"); break;
	case 8: sprintf(howto, "h8.bmp"); break;
	case 9: sprintf(howto, "h9.bmp"); break;
	}
	nm = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	ex = (HBITMAP)LoadImage(NULL, explain, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	ht = (HBITMAP)LoadImage(NULL, howto, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	rd = (HBITMAP)LoadImage(NULL, ready, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	g = (HBITMAP)LoadImage(NULL, go, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	paint(hWnd, dpi, nm, 800, 800);
	switch (a) {
	case 1: PlaySound(TEXT("1.wav"), 0, SND_FILENAME); break;
	case 2: PlaySound(TEXT("2.wav"), 0, SND_FILENAME); break;
	case 3: PlaySound(TEXT("3.wav"), 0, SND_FILENAME); break;
	case 4: PlaySound(TEXT("4.wav"), 0, SND_FILENAME); break;
	case 5: PlaySound(TEXT("5.wav"), 0, SND_FILENAME); break;
	case 6: PlaySound(TEXT("6.wav"), 0, SND_FILENAME); break;
	case 7: PlaySound(TEXT("7.wav"), 0, SND_FILENAME); break;
	case 8: PlaySound(TEXT("8.wav"), 0, SND_FILENAME); break;
	case 9: PlaySound(TEXT("9.wav"), 0, SND_FILENAME); break;
	}
	paint(hWnd, dpi, ex, 800, 800);
	PlaySound(TEXT("explain.wav"), 0, SND_FILENAME);
	cls();
	Sleep(85);
	paint(hWnd, dpi, ht, 800, 800);
	PlaySound(TEXT("anticipation.wav"), 0, SND_FILENAME);
	cls();
	Sleep(85);
	paint(hWnd, dpi, rd, 800, 800);
	PlaySound(TEXT("ready.wav"), 0, SND_FILENAME | SND_ASYNC);
	Sleep(2000);
	cls();
	Sleep(85);
	paint(hWnd, dpi, g, 800, 800);
	PlaySound(TEXT("go.wav"), 0, SND_FILENAME | SND_ASYNC);
	Sleep(1000);
	cls();
}

int again() {
	cls();
	int i, j;
	char ch;
	int p[5][3] = { { 1,1,1 },{ 1,0,1 },{ 1,1,1 },{ 1,0,0 },{ 1,0,0 } };
	normalbound(c_gray);
	{
		tc(cc_yellow);
		gotoxy(30, 5);
		printf("★ 최종 점수 체크 ★");
		tc(cc_cyan);
		for (i = 8; i <= 12; i++) {
			gotoxy(22, i);
			printf("■");
		}
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 5; j++) {
				if (p[j][i]) {
					gotoxy(2 * i + 28, j + 8);
					printf("■");
					gotoxy(2 * i + 56, j + 8);
					printf("■");
				}
			}
		}
		gotoxy(46, 8);
		printf("■■■");
		gotoxy(50, 9);
		printf("■");
		gotoxy(46, 10);
		printf("■■■");
		gotoxy(46, 11);
		printf("■");
		gotoxy(46, 12);
		printf("■■■");
	}
	tc(cc_white);
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (i == 0 || i == 8 || j == 0 || j == 8) {
				gotoxy(2 * i + 19, j + 15);
				printf("■");
				gotoxy(2 * i + 45, j + 15);
				printf("■");
			}
		}
	}
	tc(cc_cyan);
	gotoxy(28, 19);
	printf("%1d", total1);
	gotoxy(54, 19);
	printf("%1d", total2);
	if (total1 > total2) {
		gotoxy(21, 27);
		tc(cc_blue);
		printf("★ 1P의 승리입니다! 다시 하시겠습니까?");
	}
	else if (total1 < total2) {
		gotoxy(21, 27);
		tc(cc_red);
		printf("★ 2P의 승리입니다! 다시 하시겠습니까?");
	}
	else {
		gotoxy(19, 27);
		tc(cc_green);
		printf("★ 비겼군요! 놀라워요! 다시 하시겠습니까?");
	}
	tc(c_white);
	gotoxy(21, 30);
	printf("Y : Yes (선택 메뉴로 돌아갑니다)");
	gotoxy(21, 32);
	printf("N : No (종료합니다)");
	while (1) {
		if (kbhit()) {
			ch = getch();
			if (ch == 121 || ch == 110 || ch == 89 || ch == 78) break;
		}
	}
	if (ch == 121 || ch == 89) {
		cls();
		return 1;
	}
	else {
		cls();
		return 0;
	}
}

void normalgame() {
	int arr[9];
	int i, j, rd, tmp;
	cls();
	normalbound(c_gray);
	total1 = 0;
	total2 = 0;
	for (i = 0; i < 9; i++) arr[i] = i + 1;
	for (i = 0; i < 8; i++) {
		rd = rand() % (9 - i) + i;
		tmp = arr[i];
		arr[i] = arr[rd];
		arr[rd] = tmp;
	}
	for (i = 0; i < 9; i++) {
		spin(arr[i]);
		explain(arr[i]);
		Sleep(100);
		while (kbhit()) getch();
		mciOpen.lpstrElementName = "dating_tense.mp3";
		mciOpen.lpstrDeviceType = "mpegvideo";
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID = mciOpen.wDeviceID;
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)& mciPlay);
		while (kbhit()) getch();
		switch (arr[i]) {
		case 1: click_n1(); break;
		case 2: maze_n2(); break;
		case 3: heart_n3(); break;
		case 4: run_n4(); break;
		case 5: color_n5(); break;
		case 6: thief_n6(); break;
		case 7: star_n7(); break;
		case 8: tail_n8(); break;
		case 9: guess_n9(); break;
		}
		stopAllSounds(dwID);
		cls();
		normalbound(c_gray);
		while (kbhit()) getch();
	}
	if (again()) {
		{
			PlaySound(TEXT("select_mode.wav"), 0, SND_FILENAME | SND_ASYNC);
			Sleep(20);
			mciOpen.lpstrElementName = "sunburst.mp3";
			mciOpen.lpstrDeviceType = "mpegvideo";
			mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
			dwID = mciOpen.wDeviceID;
			mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
		}
		while (kbhit()) getch();
		return;
	}
	else exit(0);
}

void selectgame(int sel) {
	int i;
	char ch;
	int rc = rand() % 6 + 9;
	tc(rc);
	if (sel >= 0) PlaySound(TEXT("tp_click.wav"), 0, SND_FILENAME | SND_ASYNC);
	gotoxy(14, 2);
	printf("★ 시작할 게임을 선택하여 주십시오.");
	gotoxy(66, 38);
	printf("SELECT MODE");
	tc(c_white);
	gotoxy(50, 2);
	printf("(ENTER로 결정)");
	for (i = 1; i <= 9; i++) {
		if (i == sel) {
			tc(c_yellow);
			gotoxy(10, 3 + 3 * i);
			printf("▶  ");
		}
		else {
			tc(c_white);
			gotoxy(10, 3 + 3 * i);
			printf("   ");
		}
		gotoxy(14, 3 + 3 * i);
		printf("%d. %s", i, gm[i]);
		if (sel >= 10 && sel - 9 == i) {
			tc(c_yellow);
			gotoxy(44, 3 + 3 * i);
			printf("▶  ");
		}
		else {
			tc(c_white);
			gotoxy(44, 3 + 3 * i);
			printf("    ");
		}
		gotoxy(48, 3 + 3 * i);
		printf("%c. %s", order[i - 1], gm[i + 9]);
	}
	tc(cc_red);
	if (sel == 0) {
		gotoxy(10, 34);
		printf("▶  ");
	}
	else {
		gotoxy(10, 34);
		printf("    ");
	}
	gotoxy(14, 34);
	printf("0. 종료하기");
	while (1) {
		if (kbhit()) {
			ch = getch();
			if (ch >= '0' && ch <= '9') {
				selectgame(ch - 48);
				return;
			}
			else if (ch == ESC) {
				if (sel <= -1) {
					selectgame(-2);
					return;
				}
				else {
					selectgame(-1);
					return;
				}
			}
			else {
				for (i = 0; i < 9; i++) {
					if (ch == order[i] || ch == order[i] + 32) {
						selectgame(i + 10);
						return;
					}
				}
			}
			if (ch == ENTER) break;
		}
	}
	tc(c_white);
	if (sel == 0) {
		cls();
		exit(0);
		return;
	}
	if (sel >= 1 && sel <= 9) {
		while (kbhit()) getch();
		explain(sel);
		mciOpen.lpstrElementName = "dating_tense.mp3";
		mciOpen.lpstrDeviceType = "mpegvideo";
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID = mciOpen.wDeviceID;
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)& mciPlay);
	}
	Sleep(100);
	while (kbhit()) getch();
	switch (sel) {
	case 1: click_n1(); break;
	case 2: maze_n2(); break;
	case 3: heart_n3(); break;
	case 4: run_n4(); break;
	case 5: color_n5(); break;
	case 6: thief_n6(); break;
	case 7: star_n7(); break;
	case 8: tail_n8(); break;
	case 9: guess_n9(); break;
	default: cls(); /*printf("%d", sel);*/ Sleep(900); break;
	}
	cls();
	normalbound(c_gray);
	while (kbhit()) getch();
	selectgame(0);
	return;
}