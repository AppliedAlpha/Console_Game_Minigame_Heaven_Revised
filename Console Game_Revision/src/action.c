#include "action.h"
#include "sound.h"

// 미니게임 제목 및 순서 배열
char gm[20][50] = { 
	"", "하노이 탑", "미로 찾기", "러브 찬스", "신호등 달리기", 
	"색칠 놀이", "도둑이야", "별똥별이다", "등짝을 보자", "이긴 사람",
	"???", "???", "???", "???", "???", "???", "???","???", "???" };
char order[9] = { 'Z', 'X', 'C', 'V', 'B', 'N', 'M', 'F', 'G' };

// 키 입력 대기 함수
void waiting() { while (kbhit()) getch(); }

// 콘솔창 비우는 함수
void cls() { system("cls"); }

// 마우스 좌표 이동 함수
void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 텍스트 색깔 지정 함수
// color은 "action.h"의 Macro 활용
void tc(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 회전판 숫자 출력 함수
void spin_number(int num) {
	tc(c_gray);
	gotoxy(7, 21);
	printf("%1d", (num + 5) % 9 + 1);
	gotoxy(19, 21);
	printf("%1d", (num + 6) % 9 + 1);
	gotoxy(31, 21);
	printf("%1d", (num + 7) % 9 + 1);
	gotoxy(49, 21);
	printf("%1d", num % 9 + 1);
	gotoxy(61, 21);
	printf("%1d", (num + 1) % 9 + 1);
	gotoxy(73, 21);
	printf("%1d", (num + 2) % 9 + 1);
	tc(cc_white);
	gotoxy(40, 21);
	printf("%1d", num);
}

// 회전판 출력 함수
void spin(int num) {
	int i;
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
	PlaySound(TEXT("audio/spin.wav"), 0, SND_FILENAME | SND_ASYNC);

	for (i = 1; i <= 41; i++) {
		spin_number((num + i + 8) % 9 + 1);
		Sleep(50);
	}
	for (i = 42; i <= 81; i++) {
		spin_number((num + i + 8) % 9 + 1);
		Sleep(95);
	}
	for (i = 82; i <= 87; i++) {
		spin_number((num + i + 8) % 9 + 1);
		Sleep(280);
	}
	for (i = 88; i <= 90; i++) {
		spin_number((num + i + 8) % 9 + 1);
		Sleep(340);
	}
	spin_number(num);
	gotoxy(24, 30);
	tc(cc_yellow);
	printf("\"%s\"", gm[num]);
	tc(c_white);
	printf(" 게임을 시작합니다!");
	Sleep(2000);
}

// 설명창 함수
void explain(int num) {
	HWND hWnd = getConsoleWindowHandle();
	HBITMAP nm, ex, ht, rd, g;
	char name[100], explain[100], howto[100], ready[100], go[100];
	int dpi = GetDPI(hWnd);
	sprintf(explain, "image/explain.bmp");
	sprintf(ready, "image/ready.bmp");
	sprintf(go, "image/go.bmp");
	
	// 게임 이름 이미지
	char name_path[] = "image/0.bmp"; // 6
	name_path[6] = num + '0';
	sprintf(name, name_path);

	// 게임 설명 이미지
	char howto_path[] = "image/h0.bmp"; // 7
	howto_path[7] = num + '0';
	sprintf(howto, howto_path);
	
	// 비트맵 형식으로 변환
	nm = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	ex = (HBITMAP)LoadImage(NULL, explain, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	ht = (HBITMAP)LoadImage(NULL, howto, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	rd = (HBITMAP)LoadImage(NULL, ready, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	g = (HBITMAP)LoadImage(NULL, go, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	paint(hWnd, dpi, nm, 800, 800);

	// 게임 (제목) 효과음 불러오기
	char sound_path[] = "audio/0.wav"; // 6
	sound_path[6] = num + '0';
	PlaySound(TEXT(sound_path), 0, SND_FILENAME);
	
	// 설명 효과음 불러오기
	paint(hWnd, dpi, ex, 800, 800);
	PlaySound(TEXT("audio/explain.wav"), 0, SND_FILENAME);
	cls();
	Sleep(85);

	// 설명 창 출력
	paint(hWnd, dpi, ht, 800, 800);
	PlaySound(TEXT("audio/anticipation.wav"), 0, SND_FILENAME);
	cls();
	Sleep(85);

	paint(hWnd, dpi, rd, 800, 800);
	PlaySound(TEXT("audio/ready.wav"), 0, SND_FILENAME | SND_ASYNC);
	Sleep(2000);
	cls();
	Sleep(85);

	paint(hWnd, dpi, g, 800, 800);
	PlaySound(TEXT("audio/go.wav"), 0, SND_FILENAME | SND_ASYNC);
	Sleep(1000);
	cls();
}

// 점수 출력 함수
void print_score(int sc1, int sc2) {
	gotoxy(32, 37);
	tc(c_white);
	printf("%4d", sc1);
	gotoxy(44, 37);
	printf("%4d", sc2);
}

// 윤곽 출력 함수
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

// 내부 선 출력 함수
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

// 경계선 출력 함수
void border(int y) {
	gotoxy(2, y);
	for (int i = 0; i < 38; i++) printf("〓");
}

// 시작 버튼 출력
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

// 종료 버튼 출력
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

// 노멀 버튼 출력
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

// 선택 버튼 출력
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

// 승리자 왕관 그리기 함수
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

// 반달형 사람 도트 출력 (게임3)
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

// 하트 도트 출력 (게임3)
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

// 하트 도트 제거 (게임3)
void remove_Heart(int a) {
	int i, j;
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 9; j++) {
			gotoxy(2 * i + (28 - 24 * (a == 2) + 24 * (a == 3)), 11 - 8 * (!a) + 8 * (a == 1) + j);
			printf("  ");
		}
	}
}

// 플레이어1 우승
void p1_win(int** total1, int** total2, int** dwID) {
	mciSendCommandW(**dwID, MCI_CLOSE, 0, NULL);
	PlaySound(TEXT("audio/win.wav"), 0, SND_FILENAME | SND_ASYNC);

	gotoxy(4, 37);
	tc(cc_yellow);
	printf("★ You Win! Please Wait...");
	gotoxy(62, 37);
	tc(cc_red);
	printf("☆ You Lose...");
	(**total1)++;
}

// 플레이어2 우승
void p2_win(int** total1, int** total2, int** dwID) {
	mciSendCommandW(**dwID, MCI_CLOSE, 0, NULL);
	PlaySound(TEXT("audio/win.wav"), 0, SND_FILENAME | SND_ASYNC);

	gotoxy(50, 37);
	tc(cc_yellow);
	printf("★ You Win! Please Wait...");
	gotoxy(4, 37);
	tc(cc_red);
	printf("☆ You Lose...");
	(**total2)++;
}

// 비김 처리
void tie(int **dwID) {
	mciSendCommandW(**dwID, MCI_CLOSE, 0, NULL);
	PlaySound(TEXT("audio/tie.wav"), 0, SND_FILENAME | SND_ASYNC);

	gotoxy(4, 37);
	tc(cc_green);
	printf("☆ Well done!!");
	gotoxy(62, 37);
	printf("☆ Well done!!");
}

// 자전거 출력 (게임4)
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

// 자전거 선 출력 (게임4)
void print_line(int y, int* line, int move) {
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

// 손 출력 (게임9)
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
		break;
	}
}