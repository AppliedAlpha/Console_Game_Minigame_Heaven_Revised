#include <Windows.h>
#include "action.h"

typedef struct {
	int posx, posy;
}chrpos;

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void tc(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//문자 색깔 지정


void print_score(int sc1, int sc2) {
	gotoxy(32, 37);
	tc(c_white);
	printf("%4d", sc1);
	gotoxy(44, 37);
	printf("%4d", sc2);
}
//점수 출력 함수

void normalbound(int a) {
	gotoxy(0, 0);
	int x, y;
	tc(a);
	for (x = 0; x < WIDTH; x += 2) {
		for (y = 0; y < HEIGHT; y++) {
			if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 2) {
				gotoxy(x, y);
				printf("■");
			}
		}
	}
}
//윤곽 출력 함수

void halfbound(int a, int type) {
	int i;
	tc(a);
	switch (type) {
	case 0:
		for (i = 1; i <= 38; i++) {
			if (i != 35) {
				gotoxy(39, i);
				printf("||");
			}
		}
		break;
	case 1:
		for (i = 1; i <= 38; i++) {
			if (i != 35) {
				gotoxy(38, i);
				printf("■■");
			}
		}
		break;
	case 2:
		for (i = 36; i <= 38; i++) {
			gotoxy(39, i);
			printf("||");
		}
		break;
	case 3:
		gotoxy(2, 18);
		for (i = 0; i < 38; i++) printf("■");
		for (i = 36; i <= 38; i++) {
			gotoxy(39, i);
			printf("||");
		}
		break;
	default: break;
	}
	gotoxy(2, 35);
	printf("============================================================================");
}
//내부 선 출력 함수

void border(int y) {
	gotoxy(2, y);
	for (int i = 0; i < 38; i++) printf("〓");
}
//경계선 출력 함수

void mt_start(int a) {
	int i;
	tc(a);
	gotoxy(24, 22);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓");
	for (i = 23; i <= 25; i++) {
		gotoxy(24, i);
		printf("┃");
		gotoxy(54, i);
		printf("┃");
	}
	gotoxy(24, 26);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓");
	gotoxy(36, 24);
	printf("시    작");
}
//시작 버튼 출력

void mt_quit(int a) {
	int i;
	tc(a);
	gotoxy(24, 29);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓");
	for (i = 30; i <= 32; i++) {
		gotoxy(24, i);
		printf("┃");
		gotoxy(54, i);
		printf("┃");
	}
	gotoxy(24, 33);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓");
	gotoxy(36, 31);
	printf("종    료");
}
//나가기 버튼 출력

void sm_np(int a) {
	int i;
	tc(a);
	gotoxy(8, 4);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓");
	for (i = 5; i <= 33; i++) {
		gotoxy(8, i);
		printf("┃");
		gotoxy(30, i);
		printf("┃");
	}
	gotoxy(8, 34);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓");
	gotoxy(16, 7);
	printf("노    멀");
}
//노멀 모드 출력

void sm_sp(int a) {
	int i;
	tc(a);
	gotoxy(48, 4);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓");
	for (i = 5; i <= 33; i++) {
		gotoxy(48, i);
		printf("┃");
		gotoxy(70, i);
		printf("┃");
	}
	gotoxy(48, 34);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓");
	gotoxy(56, 7);
	printf("선    택");
}
//선택 모드 출력

void winner(int a, int b) {
	tc(cc_yellow);
	int win[4][7] = { {1,0,1,0,1,0,1}, {1,1,0,1,0,1,1}, {1,0,0,0,0,0,1}, {1,1,1,1,1,1,1} };
	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 4; y++) {
			if (win[y][x]) {
				gotoxy(x * 2 + a, y + b);
				printf("■");
			}
			else {
				gotoxy(x * 2 + a, y + b);
				printf("  ");
			}
		}
	}
}
//승자 왕관 출력

void print_halfmoon(int a, int b) {
	int hm[5][10] = {
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,1,1,0,0,1,1,0,0},
	{0,1,0,0,0,0,0,0,1,0},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1} };
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 5; y++) {
			if (hm[y][x]) {
				gotoxy(x * 2 + a, y + b);
				printf("■");
			}
			else {
				gotoxy(x * 2 + a, y + b);
				printf("  ");
			}
		}
	}
}
//사람 얼굴 출력

void print_Heart(int a) {
	int i, j;
	int heart[9][12] = {
	{2,2,1,1,2,2,2,2,1,1,2,2},
	{2,1,0,0,1,2,2,1,0,0,1,2},
	{1,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,0,1},
	{2,1,0,0,0,0,0,0,1,0,1,2},
	{2,2,1,0,0,0,0,1,0,1,2,2},
	{2,2,2,1,0,0,0,0,1,2,2,2},
	{2,2,2,2,1,0,0,1,2,2,2,2},
	{2,2,2,2,2,1,1,2,2,2,2,2} };
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 9; j++) {
			gotoxy(2 * i + (28 - 24 * (a == 2) + 24 * (a == 3)), 11 - 8 * (!a) + 8 * (a == 1) + j);
			if (heart[j][i] == 1) {
				tc(c_red);
				printf("■");
			}
			else if (!heart[j][i]) {
				tc(cc_red);
				printf("■");
			}
			else printf("  ");
		}
	}
}
//하트 출력

void remove_Heart(int a) {
	int i, j;
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 9; j++) {
			gotoxy(2 * i + (28 - 24 * (a == 2) + 24 * (a == 3)), 11 - 8 * (!a) + 8 * (a == 1) + j);
			printf("  ");
		}
	}
}
//하트 삭제

void p1_win() {
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
	PlaySound(TEXT("win.wav"), 0, SND_FILENAME | SND_ASYNC);
	gotoxy(4, 37);
	tc(cc_yellow);
	printf("★ You Win! Please Wait...");
	gotoxy(62, 37);
	tc(cc_red);
	printf("☆ You Lose...");
	total1++;
}
//1P 승

void p2_win() {
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
	PlaySound(TEXT("win.wav"), 0, SND_FILENAME | SND_ASYNC);
	gotoxy(50, 37);
	tc(cc_yellow);
	printf("★ You Win! Please Wait...");
	gotoxy(4, 37);
	tc(cc_red);
	printf("☆ You Lose...");
	total2++;
}
//2P 승

void tie() {
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
	PlaySound(TEXT("tie.wav"), 0, SND_FILENAME | SND_ASYNC);
	gotoxy(4, 37);
	tc(cc_green);
	printf("☆ Well done!!");
	gotoxy(62, 37);
	printf("☆ Well done!!");
}
//비김

void print_bike(int x, int y, int c) {
	int i, j;
	int bike[10][12] = {
	{0,0,0,0,-1,-1,0,0,1,0,0,0},
	{0,0,0,0,-1,-1,0,0,0,1,0,0},
	{0,0,0,1,1,1,1,0,1,0,1,0},
	{0,0,0,0,1,0,2,2,0,1,0,0},
	{0,0,0,0,2,2,0,2,2,1,0,0},
	{0,0,0,2,0,2,2,0,0,2,0,0},
	{0,0,2,0,0,2,0,0,0,2,0,0},
	{1,1,1,0,0,1,0,0,0,1,1,1},
	{1,0,1,0,0,1,1,0,0,1,0,1},
	{1,1,1,0,0,0,0,0,0,1,1,1} };
	tc(c_white);
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 10; j++) {
			if (bike[j][i] == 1) {
				gotoxy(2 * i + x, j + y);
				printf("■");
			}
		}
	}
	tc(cc_blue);
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 10; j++) {
			if (bike[j][i] == 2) {
				gotoxy(2 * i + x, j + y);
				printf("■");
			}
		}
	}
	if (c == cc_blue) tc(cc_cyan);
	else tc(cc_red);
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 2; j++) {
			if (bike[j][i] == -1) {
				gotoxy(2 * i + x, j + y);
				printf("▣");
			}
		}
	}
}
//자전거 이동 함수

void print_line(int y, int* line, int move) { // 9, line1, 0
	int i;
	tc(cc_yellow);
	for (i = 0; i < 35; i++) {
		if (*(line + i)) {
			if (i != 4 && i != 5 && i != 7 && i != 8 && i != 9) {
				gotoxy(6 + 2 * i, y);
				printf("■");
			}
			if (i != 3 && i != 5 && i != 6 && i != 9) {
				gotoxy(6 + 2 * i, y + 1);
				printf("■");
			}
		}
		else {
			if (i != 4 && i != 5 && i != 7 && i != 8 && i != 9) {
				gotoxy(6 + 2 * i, y);
				printf("  ");
			}
			if (i != 3 && i != 5 && i != 6 && i != 9) {
				gotoxy(6 + 2 * i, y + 1);
				printf("  ");
			}
		}
	}
	if (!(move % 100)) {
		print_bike(6, 5, cc_blue);
		print_bike(6, 22, cc_red);
		*(line + 35) = *(line + 0);
		for (i = 1; i <= 35; i++)* (line + (i - 1)) = *(line + i);
	}
}
//선 출력

void print_hand(int x, int y, int rd) {
	int i, j;
	int h0[14][11] = {
		{ 0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,0,1,0,1,0,1,0,1,0 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 0,1,2,2,2,2,2,2,2,1,0 },
	{ 0,0,1,1,1,1,1,1,1,0,0 } };
	int h2[14][11] = {
		{ 0,1,0,1,0,0,0,0,0,0,0 },
	{ 1,2,1,2,1,0,0,0,0,0,0 },
	{ 1,2,1,2,1,0,0,0,0,0,0 },
	{ 1,2,1,2,1,0,0,0,0,0,0 },
	{ 1,2,1,2,1,1,0,1,0,1,0 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 0,1,2,2,2,2,2,2,2,1,0 },
	{ 0,0,1,1,1,1,1,1,1,0,0 } };
	int h5[14][11] = {
		{ 0,1,0,1,0,1,0,1,0,1,0 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 0,1,2,2,2,2,2,2,2,1,0 },
	{ 0,0,1,1,1,1,1,1,1,0,0 } };
	for (i = 0; i < 11; i++) {
		for (j = 0; j < 14; j++) {
			gotoxy(2 * i + x, j + y);
			printf("  ");
		}
	}
	switch (rd) {
	case 0:
		if (y <= 18) tc(cc_blue);
		else tc(cc_red);
		for (i = 0; i < 11; i++) {
			for (j = 0; j < 14; j++) {
				if (h0[j][i] == 1) {
					gotoxy(2 * i + x, j + y);
					printf("■");
				}
				if (h0[j][i] == 0) {
					gotoxy(2 * i + x, j + y);
					printf("  ");
				}
			}
		}
		/*tc(cc_white);
		for (i = 0; i < 11; i++) {
			for (j = 0; j < 14; j++) {
				if (h0[j][i] == 2) {
					gotoxy(2 * i + x, j + y);
					printf("■");
				}
			}
		}*/
		break;
	case 1:
		if (y <= 18) tc(cc_blue);
		else tc(cc_red);
		for (i = 0; i < 11; i++) {
			for (j = 0; j < 14; j++) {
				if (h2[j][i] == 1) {
					gotoxy(2 * i + x, j + y);
					printf("■");
				}
				if (h2[j][i] == 0) {
					gotoxy(2 * i + x, j + y);
					printf("  ");
				}
			}
		}
		/*tc(cc_white);
		for (i = 0; i < 11; i++) {
			for (j = 0; j < 14; j++) {
				if (h2[j][i] == 2) {
					gotoxy(2 * i + x, j + y);
					printf("■");
				}
			}
		}*/
		break;
	case 2:
		if (y <= 18) tc(cc_blue);
		else tc(cc_red);
		for (i = 0; i < 11; i++) {
			for (j = 0; j < 14; j++) {
				if (h5[j][i] == 1) {
					gotoxy(2 * i + x, j + y);
					printf("■");
				}
				if (h5[j][i] == 0) {
					gotoxy(2 * i + x, j + y);
					printf("  ");
				}
			}
		}
		/*tc(cc_white);
		for (i = 0; i < 11; i++) {
			for (j = 0; j < 14; j++) {
				if (h5[j][i] == 2) {
					gotoxy(2 * i + x, j + y);
					printf("■");
				}
			}
		}*/
		break;
	}
}
//손 출력 함수