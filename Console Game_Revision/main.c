#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
#include "Digitalv.h"
#include "game_src/game1.h"
#include "game_src/game2.h"
#include "game_src/game3.h"
#include "game_src/game4.h"
#include "game_src/game5.h"
#include "game_src/game6.h"
#include "game_src/game7.h"
#include "game_src/game8.h"
#include "game_src/game9.h"
#include "src/screen.h"
#include "src/sound.h"
#include "src/action.h"
#include "src/menu.h"
#pragma comment(lib, "winmm.lib")
#pragma warning(disable:4996)
#define WIDTH 80
#define HEIGHT 40
#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
#define FUNCTION_KEY -32
#define ESC 27
#define ENTER 13
#define MAZE_SIZE_X 18
#define MAZE_SIZE_Y 34
#define A 65
#define S 83
#define D 68
#define W 87
#define J 74
#define K 75
#define L 76
#define I 73
#define MCI_DGV_PLAY_REPEAT 0x00010000L
int dwID;
MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

char gm[20][50] = { "", "하노이 탑", "미로 찾기", "러브 찬스", "신호등 달리기", "색칠 놀이", "도둑이야", "별똥별이다", "등짝을 보자", "이긴 사람", "???", "???", "???", "???", "???", "???", "???","???", "???" };
char order[9] = { 'Z', 'X', 'C', 'V', 'B', 'N', 'M', 'F', 'G' };
int selme = 0;
int dir1 = -1, dir2 = -1;
int total1 = 0, total2 = 0;

/*
이 게임은 주로 게임 함수, 메뉴 함수, 기타 수행 함수로 구성되어 있다.
메뉴 함수에서 선택을 하면 여러 미니 게임을 고를 수 있고
게임 함수에서 각기 다른 미니 게임을 실행하며
수행 함수에서는 입력 처리, 화면 출력, 등등의 보조 역할을 한다.

총 게임 함수는 9개이고, 미니 게임 갯수도 총 9개이다.
*/

typedef struct {
	int posx, posy;
}chrpos;







int check_snake(chrpos* snake, chrpos* snake2, int len) {
	int i;
	if (snake[0].posx < 0 || snake[0].posy < 0 || snake[0].posx > 37 || snake[0].posy > 33)
		return 1;
	for (i = 1; i < len - 1; i++) {
		if (snake[0].posx == snake[i].posx && snake[0].posy == snake[i].posy)
			return 1;
		if (snake[0].posx == snake2[i].posx && snake[0].posy == snake2[i].posy)
			return 1;
	}
	return 0;
}
//뱀 충돌 확인

void move_snake(chrpos* p1_snake, chrpos* p2_snake, int len1, int len2) {
	int i, j;
	{
		if (GetAsyncKeyState(W) & 0x8000) if (dir1 != 1) dir1 = 0;
		if (GetAsyncKeyState(S) & 0x8000) if (dir1 != 0) dir1 = 1;
		if (GetAsyncKeyState(A) & 0x8000) if (dir1 != 3) dir1 = 2;
		if (GetAsyncKeyState(D) & 0x8000) if (dir1 != 2) dir1 = 3;
		if (GetAsyncKeyState(I) & 0x8000) if (dir2 != 1) dir2 = 0;
		if (GetAsyncKeyState(K) & 0x8000) if (dir2 != 0) dir2 = 1;
		if (GetAsyncKeyState(J) & 0x8000) if (dir2 != 3) dir2 = 2;
		if (GetAsyncKeyState(L) & 0x8000) if (dir2 != 2) dir2 = 3;
	}
	if (dir1 != -1) {
		int i;
		gotoxy(2 * p1_snake[len1 - 1].posx + 2, p1_snake[len1 - 1].posy + 1);
		printf("  ");
		for (i = len1 - 1; i > 0; i--) p1_snake[i] = p1_snake[i - 1];
		gotoxy(2 * p1_snake[1].posx + 2, p1_snake[1].posy + 1);
		tc(cc_cyan);
		printf("◎");
	}
	switch (dir1) {
	case 0: p1_snake[0].posy--; break;
	case 1: p1_snake[0].posy++; break;
	case 2: p1_snake[0].posx--; break;
	case 3: p1_snake[0].posx++; break;
	}
	gotoxy(2 * p1_snake[0].posx + 2, p1_snake[0].posy + 1);
	tc(cc_cyan);
	printf("●");
	if (dir2 != -1) {
		int i;
		gotoxy(2 * p2_snake[len2 - 1].posx + 2, p2_snake[len2 - 1].posy + 1);
		printf("  ");
		for (i = len2 - 1; i > 0; i--) p2_snake[i] = p2_snake[i - 1];
		gotoxy(2 * p2_snake[1].posx + 2, p2_snake[1].posy + 1);
		tc(cc_yellow);
		printf("◎");
	}
	switch (dir2) {
	case 0: p2_snake[0].posy--; break;
	case 1: p2_snake[0].posy++; break;
	case 2: p2_snake[0].posx--; break;
	case 3: p2_snake[0].posx++; break;
	}
	gotoxy(2 * p2_snake[0].posx + 2, p2_snake[0].posy + 1);
	tc(cc_yellow);
	printf("●");
}
//뱀 이동



/*여기서부터 게임 함수*/
void click_n1() {
	cls();
	int i, j, sc1 = 0, sc2 = 0;
	{
		normalbound(c_gray);
		halfbound(c_gray, 0);
		for (i = 2; i <= 33; i++) {
			tc(c_white);
			gotoxy(18, i);
			printf("■■");
			gotoxy(58, i);
			printf("■■");
		}
	}
	while (sc1 < 40 && sc2 < 40) {
		if (sc1 >= 5 && !(sc1 % 5)) {
			switch (sc1 / 5) {
			case 1: tc(cc_purple); break;
			case 2: tc(cc_blue); break;
			case 3: tc(cc_cyan); break;
			case 4: tc(c_green); break;
			case 5: tc(cc_green); break;
			case 6: tc(cc_yellow); break;
			case 7: tc(cc_red); break;
			default: break;
			}
			for (i = 0; i < 18 - 2 * (sc1 / 5); i++) {
				for (j = 0; j < 3; j++) {
					if (!(j == 1 && i >= 8 - (sc1 / 5) && i <= 9 - (sc1 / 5))) {
						gotoxy(2 * (i + sc1 / 5) + 2, j + 35 - 4 * (sc1 / 5));
						printf("■");
					}
				}
			}
		}
		if (sc2 >= 5 && !(sc2 % 5)) {
			switch (sc2 / 5) {
			case 1: tc(cc_purple); break;
			case 2: tc(cc_blue); break;
			case 3: tc(cc_cyan); break;
			case 4: tc(c_green); break;
			case 5: tc(cc_green); break;
			case 6: tc(cc_yellow); break;
			case 7: tc(cc_red); break;
			default: break;
			}
			for (i = 0; i < 18 - 2 * (sc2 / 5); i++) {
				for (j = 0; j < 3; j++) {
					if (!(j == 1 && i >= 8 - (sc2 / 5) && i <= 9 - (sc2 / 5))) {
						gotoxy(2 * (i + sc2 / 5) + 42, j + 35 - 4 * (sc2 / 5));
						printf("■");
					}
				}
			}
		}
		print_score(sc1, sc2);
		if (GetAsyncKeyState(A) & 0x8000) {
			Sleep(40);
			if (!(GetAsyncKeyState(A) & 0x8001)) sc1++;
		}
		if (GetAsyncKeyState(J) & 0x8000) {
			Sleep(40);
			if (!(GetAsyncKeyState(J) & 0x8001)) sc2++;
		}
	}
	print_score(sc1, sc2);
	if (sc1 > sc2) {
		winner(4, 2);
		p1_win();
	}
	else if (sc2 > sc1) {
		winner(62, 2);
		p2_win();
	}
	else tie();
	Sleep(3000);
}
//edit 

void maze_n2() {
	cls();
	int i, j, x = 0, y = 0, rt;
	chrpos p1 = { 0,0 };
	chrpos p2 = { 0,0 };
	int map[MAZE_SIZE_Y][MAZE_SIZE_X] = { 0 };
	{
		normalbound(c_gray);
		halfbound(c_gray, 1);
		map[x][y] = 1;
		for (i = 0; i < 10000; i++) {
			rt = rand() % 4 + 1;
			if (rt == 1) {
				if (y == 0) continue;
				if (map[y - 2][x] == 0) {
					map[--y][x] = 1;
					map[--y][x] = 1;
				}
				else y -= 2;
			}
			if (rt == 2) {
				if (x == MAZE_SIZE_X - 2) continue;
				if (map[y][x + 2] == 0) {
					map[y][++x] = 1;
					map[y][++x] = 1;
				}
				else x += 2;
			}
			if (rt == 3) {
				if (y == MAZE_SIZE_Y - 2) continue;
				if (map[y + 2][x] == 0) {
					map[++y][x] = 1;
					map[++y][x] = 1;
				}
				else y += 2;
			}
			if (rt == 4) {
				if (x == 0) continue;
				if (map[y][x - 2] == 0) {
					map[y][--x] = 1;
					map[y][--x] = 1;
				}
				else x -= 2;
			}
		}
		map[MAZE_SIZE_Y - 2][MAZE_SIZE_X - 1] = 1;
		tc(c_white);
		for (i = 0; i < MAZE_SIZE_X; i++) {
			for (j = 0; j < MAZE_SIZE_Y; j++) {
				if (!map[j][i]) {
					gotoxy(2 * i + 2, j + 1);
					printf("■");
					gotoxy(2 * i + 42, j + 1);
					printf("■");
				}
			}
		}
		tc(cc_yellow);
		gotoxy(36, 33);
		printf("☞");
		gotoxy(76, 33);
		printf("☞");
	}
	Sleep(1000);
	while (1) {
		gotoxy(2 * p1.posx + 2, p1.posy + 1);
		tc(cc_cyan);
		printf("◈");
		gotoxy(2 * p2.posx + 42, p2.posy + 1);
		tc(cc_red);
		printf("◈");
		Sleep(150);
		if (GetAsyncKeyState(A) && p1.posx > 0) {
			if (map[p1.posy][p1.posx - 1]) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posx--;
			}
		}
		if (GetAsyncKeyState(D) && p1.posx < MAZE_SIZE_X - 1) {
			if (map[p1.posy][p1.posx + 1]) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posx++;
			}
		}
		if (GetAsyncKeyState(W) && p1.posy > 0) {
			if (map[p1.posy - 1][p1.posx]) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posy--;
			}
		}
		if (GetAsyncKeyState(S) && p1.posy < MAZE_SIZE_Y - 1) {
			if (map[p1.posy + 1][p1.posx]) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posy++;
			}
		}
		if (GetAsyncKeyState(J) && p2.posx > 0) {
			if (map[p2.posy][p2.posx - 1]) {
				gotoxy(2 * p2.posx + 42, p2.posy + 1);
				printf("  ");
				p2.posx--;
			}
		}
		if (GetAsyncKeyState(L) && p2.posx < MAZE_SIZE_X - 1) {
			if (map[p2.posy][p2.posx + 1]) {
				gotoxy(2 * p2.posx + 42, p2.posy + 1);
				printf("  ");
				p2.posx++;
			}
		}
		if (GetAsyncKeyState(I) && p2.posy > 0) {
			if (map[p2.posy - 1][p2.posx]) {
				gotoxy(2 * p2.posx + 42, p2.posy + 1);
				printf("  ");
				p2.posy--;
			}
		}
		if (GetAsyncKeyState(K) && p2.posy < MAZE_SIZE_Y - 1) {
			if (map[p2.posy + 1][p2.posx]) {
				gotoxy(2 * p2.posx + 42, p2.posy + 1);
				printf("  ");
				p2.posy++;
			}
		}
		if ((p1.posx == MAZE_SIZE_X - 1 && p1.posy == MAZE_SIZE_Y - 2) || (p2.posx == MAZE_SIZE_X - 1 && p2.posy == MAZE_SIZE_Y - 2))  break;
	}
	if (p1.posx == MAZE_SIZE_X - 1 && p1.posy == MAZE_SIZE_Y - 2) {
		if (p2.posx == MAZE_SIZE_X - 1 && p2.posy == MAZE_SIZE_Y - 2) tie();
		else {
			for (i = 12; i < 30; i++) {
				for (j = 15; j < 21; j++) {
					gotoxy(i, j);
					printf("  ");
				}
			}
			winner(14, 16);
			p1_win();
		}
	}
	else if (p2.posx == MAZE_SIZE_X - 1 && p2.posy == MAZE_SIZE_Y - 2) {
		for (i = 52; i < 70; i++) {
			for (j = 15; j < 21; j++) {
				gotoxy(i, j);
				printf("  ");
			}
		}
		winner(54, 16);
		p2_win();
	}
	Sleep(3000);
}

void heart_n3() {
	cls();
	int i, rd, sc1 = 0, sc2 = 0, print_c = 0;
	char ch;
	normalbound(c_gray);
	halfbound(c_gray, 2);
	tc(c_white);
	print_halfmoon(10, 30);
	print_halfmoon(50, 30);
	clock_t start = clock();
	while (print_c <= 40) {
		float tt;
		print_score(sc1, sc2);
		rd = rand() % 4;
		print_Heart(rd);
		print_c++;
		if (print_c <= 10) tt = 1.5;
		else if (print_c <= 20) tt = 1.0;
		else if (print_c <= 30) tt = 0.7;
		else tt = 0.4;
		start = clock();
		while (1) {
			if (rd == 0) {
				if (GetAsyncKeyState(W) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(W) & 0x8001)) {
						sc1++;
						start = clock();
						break;
					}
				}
				if (GetAsyncKeyState(I) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(I) & 0x8001)) {
						sc2++;
						start = clock();
						break;
					}
				}
			}
			if (rd == 1) {
				if (GetAsyncKeyState(S) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(S) & 0x8001)) {
						sc1++;
						start = clock();
						break;
					}
				}
				if (GetAsyncKeyState(K) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(K) & 0x8001)) {
						sc2++;
						start = clock();
						break;
					}
				}
			}
			if (rd == 2) {
				if (GetAsyncKeyState(A) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(A) & 0x8001)) {
						sc1++;
						start = clock();
						break;
					}
				}
				if (GetAsyncKeyState(J) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(J) & 0x8001)) {
						sc2++;
						start = clock();
						break;
					}
				}
			}
			if (rd == 3) {
				if (GetAsyncKeyState(D) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(D) & 0x8001)) {
						sc1++;
						start = clock();
						break;
					}
				}
				if (GetAsyncKeyState(L) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(L) & 0x8001)) {
						sc2++;
						start = clock();
						break;
					}
				}
			}
			if ((clock() - start) / CLOCKS_PER_SEC > (float)tt) break;
		}
		remove_Heart(rd);
		Sleep(200);
	}
	print_score(sc1, sc2);
	if (sc1 > sc2) {
		winner(16, 24);
		p1_win();
	}
	else if (sc2 > sc1) {
		winner(50, 24);
		p2_win();
	}
	else tie();
	Sleep(3000);
}

void run_n4() {
	cls();
	int i, j, rd, sc1 = 0, sc2 = 0;
	int hold1 = 0, hold2 = 0;
	int rd1[3] = { 0,0,0 }, rd2[3] = { 0,0,0 };
	clock_t start = clock();
	int line1[36] = { 1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1 };
	int line2[36] = { 1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1 };
	normalbound(c_gray);
	halfbound(c_white, 3);
	tc(c_white);
	border(3);
	border(16);
	border(20);
	border(33);
	print_line(9, line1, 0);
	print_line(26, line2, 0);
	print_bike(6, 5, cc_blue);
	print_bike(6, 22, cc_red);
	tc(c_white);
	gotoxy(16, 17);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(16, 19);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■");
	tc(c_black);
	gotoxy(18, 18);
	printf("■■■■■■■■■■■■■■■■■■■■■■");
	rd1[0] = rand() % 11 + 20;
	rd1[1] = rand() % 31 + 170;
	rd1[2] = rand() % 61 + 270;
	rd2[0] = rand() % 11 + 20;
	rd2[1] = rand() % 31 + 170;
	rd2[2] = rand() % 61 + 270;
	while (sc1 <= 5000 && sc2 <= 5000) {
		tc(cc_green);
		gotoxy(18, 18);
		printf("■■■■■■■■■■■■■■■■■■■■■■");
		start = clock();
		rd = rand() % 3 + 3;
		while (sc1 <= 5000 && sc2 <= 5000) {
			if (GetAsyncKeyState(D) & 0x8001) {
				hold1++;
				if (hold1 >= rd1[0]) sc1++;
				else if (hold1 >= rd1[1]) sc1 += 3;
				else if (hold1 >= rd1[2]) sc1 += 5;
				sc1++;
				print_line(9, line1, sc1);
			}
			else {
				hold1 = 0;
				rd1[0] = rand() % 11 + 20;
				rd1[1] = rand() % 31 + 170;
				rd1[2] = rand() % 61 + 270;
			}
			if (GetAsyncKeyState(L) & 0x8001) {
				hold2++;
				if (hold1 >= rd2[0]) sc2++;
				else if (hold1 >= rd2[1]) sc2 += 3;
				else if (hold1 >= rd2[2]) sc2 += 5;
				sc2++;
				print_line(26, line2, sc2);
			}
			else {
				hold2 = 0;
				rd2[0] = rand() % 11 + 20;
				rd2[1] = rand() % 31 + 170;
				rd2[2] = rand() % 61 + 270;
			}
			if ((clock() - start) / CLOCKS_PER_SEC > (float)rd) break;
			print_score(sc1, sc2);
		}
		tc(cc_red);
		gotoxy(18, 18);
		printf("■■■■■■■■■■■■■■■■■■■■■■");
		start = clock();
		rd = rand() % 2 + 1;
		while (sc1 <= 5000 && sc2 <= 5000) {
			if ((GetAsyncKeyState(D) & 0x8001) && sc1 > 0) {
				sc1 -= (rand() % 7 + 1);
				Sleep(15);
			}
			if ((GetAsyncKeyState(L) & 0x8001) && sc2 > 0) {
				sc2 -= (rand() % 7 + 1);
				Sleep(15);
			}
			if ((clock() - start) / CLOCKS_PER_SEC > (float)rd) break;
			print_score(sc1, sc2);
		}
	}
	print_score(sc1, sc2);
	if (sc1 > sc2) {
		winner(62, 4);
		p1_win();
	}
	else if (sc2 > sc1) {
		winner(62, 21);
		p2_win();
	}
	else tie();
	Sleep(3000);
}

void color_n5() {
	int i, j, game = 2000; //100=1초;
	int map[34][38] = { 0 };
	cls();
	normalbound(c_gray);
	halfbound(c_gray, 2);
	chrpos p1 = { 0,18 };
	chrpos p2 = { 37,18 };
	map[18][0] = 1;
	map[18][37] = 2;
	while (game) {
		int map1 = 0, map2 = 0;
		for (i = 0; i < 38; i++) {
			for (j = 0; j < 34; j++) {
				if (map[j][i] == 1) map1++;
				if (map[j][i] == 2) map2++;
			}
		}
		print_score(map1, map2);
		gotoxy(2 * p1.posx + 2, p1.posy + 1);
		tc(cc_blue);
		printf("★");
		gotoxy(2 * p2.posx + 2, p2.posy + 1);
		tc(cc_red);
		printf("★");
		Sleep(20);
		tc(cc_yellow);
		if (GetAsyncKeyState(A) && p1.posx > 0) {
			if (p1.posx - 1 != p2.posx || p1.posy != p2.posy) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posx--;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p1.posy + j >= 0 && p1.posx + i >= 0 && p1.posy + j <= 33 && p1.posx + i <= 37) {
						if ((p1.posy + j != p2.posy) || (p1.posx + i != p2.posx)) {
							map[p1.posy + j][p1.posx + i] = 1;
							gotoxy(2 * (p1.posx + i) + 2, p1.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		if (GetAsyncKeyState(D) && p1.posx < 37) {
			if (p1.posx + 1 != p2.posx || p1.posy != p2.posy) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posx++;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p1.posy + j >= 0 && p1.posx + i >= 0 && p1.posy + j <= 33 && p1.posx + i <= 37) {
						if ((p1.posy + j != p2.posy) || (p1.posx + i != p2.posx)) {
							map[p1.posy + j][p1.posx + i] = 1;
							gotoxy(2 * (p1.posx + i) + 2, p1.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		if (GetAsyncKeyState(W) && p1.posy > 0) {
			if (p1.posy - 1 != p2.posy || p1.posx != p2.posx) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posy--;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p1.posy + j >= 0 && p1.posx + i >= 0 && p1.posy + j <= 33 && p1.posx + i <= 37) {
						if ((p1.posy + j != p2.posy) || (p1.posx + i != p2.posx)) {
							map[p1.posy + j][p1.posx + i] = 1;
							gotoxy(2 * (p1.posx + i) + 2, p1.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		if (GetAsyncKeyState(S) && p1.posy < 33) {
			if (p1.posy + 1 != p2.posy || p1.posx != p2.posx) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posy++;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p1.posy + j >= 0 && p1.posx + i >= 0 && p1.posy + j <= 33 && p1.posx + i <= 37) {
						if ((p1.posy + j != p2.posy) || (p1.posx + i != p2.posx)) {
							map[p1.posy + j][p1.posx + i] = 1;
							gotoxy(2 * (p1.posx + i) + 2, p1.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		tc(cc_green);
		if (GetAsyncKeyState(J) && p2.posx > 0) {
			if (p2.posx - 1 != p1.posx || p1.posy != p2.posy) {
				gotoxy(2 * p2.posx + 2, p2.posy + 1);
				printf("  ");
				p2.posx--;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p2.posy + j >= 0 && p2.posx + i >= 0 && p2.posy + j <= 33 && p2.posx + i <= 37) {
						if ((p2.posy + j != p1.posy) || (p2.posx + i != p1.posx)) {
							map[p2.posy + j][p2.posx + i] = 2;
							gotoxy(2 * (p2.posx + i) + 2, p2.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		if (GetAsyncKeyState(L) && p2.posx < 37) {
			if (p2.posx + 1 != p1.posx || p1.posy != p2.posy) {
				gotoxy(2 * p2.posx + 2, p2.posy + 1);
				printf("  ");
				p2.posx++;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p2.posy + j >= 0 && p2.posx + i >= 0 && p2.posy + j <= 33 && p2.posx + i <= 37) {
						if ((p2.posy + j != p1.posy) || (p2.posx + i != p1.posx)) {
							map[p2.posy + j][p2.posx + i] = 2;
							gotoxy(2 * (p2.posx + i) + 2, p2.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		if (GetAsyncKeyState(I) && p2.posy > 0) {
			if (p2.posy - 1 != p1.posy || p1.posx != p2.posx) {
				gotoxy(2 * p2.posx + 2, p2.posy + 1);
				printf("  ");
				p2.posy--;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p2.posy + j >= 0 && p2.posx + i >= 0 && p2.posy + j <= 33 && p2.posx + i <= 37) {
						if ((p2.posy + j != p1.posy) || (p2.posx + i != p1.posx)) {
							map[p2.posy + j][p2.posx + i] = 2;
							gotoxy(2 * (p2.posx + i) + 2, p2.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		if (GetAsyncKeyState(K) && p2.posy < 33) {
			if (p2.posy + 1 != p1.posy || p1.posx != p2.posx) {
				gotoxy(2 * p2.posx + 2, p2.posy + 1);
				printf("  ");
				p2.posy++;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p2.posy + j >= 0 && p2.posx + i >= 0 && p2.posy + j <= 33 && p2.posx + i <= 37) {
						if ((p2.posy + j != p1.posy) || (p2.posx + i != p1.posx)) {
							map[p2.posy + j][p2.posx + i] = 2;
							gotoxy(2 * (p2.posx + i) + 2, p2.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		game -= 2;
		if (game >= 1000) tc(cc_cyan);
		else tc(cc_red);
		gotoxy(72, 37);
		printf("%4d", game);
	}
	int m1 = 0, m2 = 0;
	for (i = 0; i < 38; i++) {
		for (j = 0; j < 34; j++) {
			if (map[j][i] == 1) m1++;
			if (map[j][i] == 2) m2++;
		}
	}
	gotoxy(72, 37);
	printf("    ");
	if (m1 > m2) {
		p1_win();
		tc(cc_yellow);
	}
	else if (m1 < m2) tc(cc_red);
	else tc(cc_cyan);
	gotoxy(32, 37);
	printf("    ");
	gotoxy(32, 37);
	printf("%4d", m1);
	if (m1 < m2) {
		p2_win();
		tc(cc_yellow);
	}
	else if (m1 > m2) tc(cc_red);
	else {
		tie();
		tc(cc_cyan);
	}
	gotoxy(44, 37);
	printf("    ");
	gotoxy(44, 37);
	printf("%d", m2);
	Sleep(3000);
}

void thief_n6() {
	cls();
	int map[34][38] = { 0 };
	chrpos p1 = { 0,16 };
	chrpos p2 = { 37,16 };
	int sc1 = 0, sc2 = 0;
	int rd, i, j, game = 4000, mapcnt = 0, clcnt = 0;
	for (i = 3; i <= 34; i++) {
		for (j = 3; j <= 30; j++) {
			rd = rand() % 20;
			if (rd <= 10) map[j][i] = 1;
			if (rd == 11) map[j][i] = 2;
		}
	}
	normalbound(c_gray);
	halfbound(c_gray, 2);
	for (i = 3; i < 34; i++) {
		for (j = 3; j < 30; j++) {
			if (map[j][i] == 1) {
				tc(cc_yellow);
				gotoxy(2 * i + 2, j + 1);
				printf("▒");
			}
			if (map[j][i] == 2) {
				tc(cc_green);
				gotoxy(2 * i + 2, j + 1);
				printf("♣");
			}
		}
	}
	while (game) {
		mapcnt = 0;
		clcnt = 0;
		if (sc1 < 0) sc1 = 0;
		if (sc2 < 0) sc2 = 0;
		for (i = 3; i < 34; i++) {
			for (j = 3; j < 30; j++) {
				if (map[j][i] == 1) mapcnt++;
				if (map[j][i] == 2) clcnt++;
			}
		}
		tc(cc_yellow);
		gotoxy(66, 37);
		printf("[%3d]", mapcnt);
		if (sc1 + mapcnt < sc2 - clcnt * 10 || sc2 + mapcnt < sc1 - clcnt * 10) break;
		if (p1.posx == p2.posx && p1.posy == p2.posy) break;
		print_score(sc1, sc2);
		gotoxy(2 * p1.posx + 2, p1.posy + 1);
		tc(cc_cyan);
		printf("◈");
		gotoxy(2 * p2.posx + 2, p2.posy + 1);
		tc(cc_red);
		printf("◈");
		Sleep(50);
		game -= 5;
		if (game >= 1000) tc(cc_cyan);
		else tc(cc_red);
		gotoxy(72, 37);
		printf("%4d", game);
		if (GetAsyncKeyState(A) && p1.posx > 0) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posx--;
			if (map[p1.posy][p1.posx]) {
				switch (map[p1.posy][p1.posx]) {
				case 1: sc1++; break;
				case 2: sc1 -= 10; break;
				}
				map[p1.posy][p1.posx] = 0;
			}
		}
		if (GetAsyncKeyState(D) && p1.posx < 37) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posx++;
			if (map[p1.posy][p1.posx]) {
				switch (map[p1.posy][p1.posx]) {
				case 1: sc1++; break;
				case 2: sc1 -= 10; break;
				}
				map[p1.posy][p1.posx] = 0;
			}
		}
		if (GetAsyncKeyState(W) && p1.posy > 0) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posy--;
			if (map[p1.posy][p1.posx]) {
				switch (map[p1.posy][p1.posx]) {
				case 1: sc1++; break;
				case 2: sc1 -= 10; break;
				}
				map[p1.posy][p1.posx] = 0;
			}
		}
		if (GetAsyncKeyState(S) && p1.posy < 33) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posy++;
			if (map[p1.posy][p1.posx]) {
				switch (map[p1.posy][p1.posx]) {
				case 1: sc1++; break;
				case 2: sc1 -= 10; break;
				}
				map[p1.posy][p1.posx] = 0;
			}
		}
		if (GetAsyncKeyState(J) && p2.posx > 0) {
			gotoxy(2 * p2.posx + 2, p2.posy + 1);
			printf("  ");
			p2.posx--;
			if (map[p2.posy][p2.posx]) {
				switch (map[p2.posy][p2.posx]) {
				case 1: sc2++; break;
				case 2: sc2 -= 10; break;
				}
				map[p2.posy][p2.posx] = 0;
			}
		}
		if (GetAsyncKeyState(L) && p2.posx < 37) {
			gotoxy(2 * p2.posx + 2, p2.posy + 1);
			printf("  ");
			p2.posx++;
			if (map[p2.posy][p2.posx]) {
				switch (map[p2.posy][p2.posx]) {
				case 1: sc2++; break;
				case 2: sc2 -= 10; break;
				}
				map[p2.posy][p2.posx] = 0;
			}
		}
		if (GetAsyncKeyState(I) && p2.posy > 0) {
			gotoxy(2 * p2.posx + 2, p2.posy + 1);
			printf("  ");
			p2.posy--;
			if (map[p2.posy][p2.posx]) {
				switch (map[p2.posy][p2.posx]) {
				case 1: sc2++; break;
				case 2: sc2 -= 10; break;
				}
				map[p2.posy][p2.posx] = 0;
			}
		}
		if (GetAsyncKeyState(K) && p2.posy < 33) {
			gotoxy(2 * p2.posx + 2, p2.posy + 1);
			printf("  ");
			p2.posy++;
			if (map[p2.posy][p2.posx]) {
				switch (map[p2.posy][p2.posx]) {
				case 1: sc2++; break;
				case 2: sc2 -= 10; break;
				}
				map[p2.posy][p2.posx] = 0;
			}
		}
	}
	print_score(sc1, sc2);
	if (sc1 > sc2) p1_win();
	else if (sc2 > sc1) p2_win();
	else tie();
	Sleep(3000);
}

void star_n7() {
	cls();
	int map1[34][19] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0 },
	{ 0,0,0,1,1,0,0,1,0,0,0,1,0,0,1,1,0,0,0 },
	{ 0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,1,1,1,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };
	int map2[34][19] = {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0 },
	{ 0,0,0,1,1,0,0,1,0,0,0,1,0,0,1,1,0,0,0 },
	{ 0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,1,1,1,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };
	chrpos p1 = { 9,0 };
	chrpos p2 = { 9,0 };
	int sc1 = 0, sc2 = 0;
	int rd, i, j;
	normalbound(c_gray);
	halfbound(c_gray, 2);
	for (i = 1; i < 18; i++) {
		for (j = 2; j < 25; j++) {
			tc(cc_yellow);
			if (map1[j][i] == 1) {
				gotoxy(2 * i + 2, j + 1);
				printf("■");
			}
			if (map2[j][i] == 1) {
				gotoxy(2 * i + 40, j + 1);
				printf("■");
			}
		}
	}
	while (sc1 <= 2 && sc2 <= 2) {
		print_score(sc1, sc2);
		for (i = 1; i < 18; i++) {
			for (j = 2; j < 25; j++) {
				if (map1[j][i]) {
					if (p1.posx != i || p1.posy != j) {
						switch (map1[j][i]) {
						case 1: case 4: tc(cc_yellow); break;
						case 2: tc(cc_green); break;
						case 3: tc(cc_blue); break;
						}
						gotoxy(2 * i + 2, j + 1);
						printf("■");
					}
				}
				if (map2[j][i]) {
					if (p2.posx != i || p2.posy != j) {
						switch (map2[j][i]) {
						case 1: case 4: tc(cc_yellow); break;
						case 2: tc(cc_green); break;
						case 3: tc(cc_blue); break;
						}
						gotoxy(2 * i + 40, j + 1);
						printf("■");
					}
				}
			}
		}
		gotoxy(2 * p1.posx + 2, p1.posy + 1);
		tc(cc_cyan);
		printf("◈");
		gotoxy(2 * p2.posx + 40, p2.posy + 1);
		tc(cc_red);
		printf("◈");
		Sleep(50);
		if (GetAsyncKeyState(A) && p1.posx > 0) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posx--;
			if (map1[p1.posy][p1.posx] == sc1 + 1) map1[p1.posy][p1.posx]++;
		}
		if (GetAsyncKeyState(D) && p1.posx < 18) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posx++;
			if (map1[p1.posy][p1.posx] == sc1 + 1) map1[p1.posy][p1.posx]++;
		}
		if (GetAsyncKeyState(W) && p1.posy > 0) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posy--;
			if (map1[p1.posy][p1.posx] == sc1 + 1) map1[p1.posy][p1.posx]++;
		}
		if (GetAsyncKeyState(S) && p1.posy < 33) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posy++;
			if (map1[p1.posy][p1.posx] == sc1 + 1) map1[p1.posy][p1.posx]++;
		}
		if (GetAsyncKeyState(J) && p2.posx > 0) {
			gotoxy(2 * p2.posx + 40, p2.posy + 1);
			printf("  ");
			p2.posx--;
			if (map2[p2.posy + 1][p2.posx - 19] == sc2 + 1) map2[p2.posy + 1][p2.posx - 19]++;
		}
		if (GetAsyncKeyState(L) && p2.posx < 18) {
			gotoxy(2 * p2.posx + 40, p2.posy + 1);
			printf("  ");
			p2.posx++;
			if (map2[p2.posy + 1][p2.posx - 19] == sc2 + 1) map2[p2.posy + 1][p2.posx - 19]++;
		}
		if (GetAsyncKeyState(I) && p2.posy > 0) {
			gotoxy(2 * p2.posx + 40, p2.posy + 1);
			printf("  ");
			p2.posy--;
			if (map2[p2.posy + 1][p2.posx - 19] == sc2 + 1) map2[p2.posy + 1][p2.posx - 19]++;
		}
		if (GetAsyncKeyState(K) && p2.posy < 33) {
			gotoxy(2 * p2.posx + 40, p2.posy + 1);
			printf("  ");
			p2.posy++;
			if (map2[p2.posy + 1][p2.posx - 19] == sc2 + 1) map2[p2.posy + 1][p2.posx - 19]++;
		}
		int ct1 = 0, ct2 = 0;
		for (i = 1; i < 18; i++) {
			for (j = 9; j < 25; j++) {
				if (map1[j][i] == sc1 + 2) ct1++;
				if (map2[j][i] == sc2 + 2) ct2++;
			}
		}
		if (ct1 == 63) sc1++;
		if (ct2 == 63) sc2++;
	}
	for (i = 1; i < 18; i++) {
		for (j = 2; j < 25; j++) {
			if (map1[j][i]) {
				switch (map1[j][i]) {
				case 1: case 4: tc(cc_yellow); break;
				case 2: tc(cc_green); break;
				case 3: tc(cc_blue); break;
				}
				gotoxy(2 * i + 2, j + 1);
				printf("■");
			}
			if (map2[j][i]) {
				switch (map2[j][i]) {
				case 1: case 4: tc(cc_yellow); break;
				case 2: tc(cc_green); break;
				case 3: tc(cc_blue); break;
				}
				gotoxy(2 * i + 40, j + 1);
				printf("■");
			}
		}
	}
	print_score(sc1, sc2);
	if (sc1 > sc2) {
		tc(cc_cyan);
		p1_win();
	}
	else if (sc2 > sc1) {
		tc(cc_red);
		p2_win();
	}
	else {
		tc(cc_green);
		tie();
	}
	Sleep(3000);
}

void tail_n8() {
	cls();
	normalbound(c_gray);
	halfbound(c_gray, 2);
	chrpos p1_snake[300], p2_snake[300], item;
	int i, j, len1 = 10, len2 = 10;
	dir1 = -1;
	dir2 = -1;
	int speed = 150, win = -1;
	for (i = 0; i < 10; i++) {
		p1_snake[i].posx = 9 - i;
		p1_snake[i].posy = 18;
		gotoxy(2 * p1_snake[i].posx + 2, p1_snake[i].posy + 1);
		tc(cc_cyan);
		printf("◎");
		p2_snake[i].posx = 28 + i;
		p2_snake[i].posy = 18;
		gotoxy(2 * p2_snake[i].posx + 2, p2_snake[i].posy + 1);
		tc(cc_yellow);
		printf("◎");
	}
	gotoxy(2 * p1_snake[0].posx + 2, p1_snake[0].posy + 1);
	tc(cc_cyan);
	printf("●");
	gotoxy(2 * p2_snake[0].posx + 2, p2_snake[0].posy + 1);
	tc(cc_yellow);
	printf("●");
	item.posx = rand() % 36 + 1;
	item.posy = rand() % 32 + 1;
	if (item.posy == 18) item.posy = rand() % 17 + 1;
	gotoxy(2 * item.posx + 2, item.posy + 1);
	tc(cc_red);
	printf("♥");
	while (1) {
		print_score(len1, len2);
		if (check_snake(p1_snake, p2_snake, len1)) {
			if (check_snake(p2_snake, p1_snake, len2)) {
				win = 0;
				break;
			}
			else win = 2;
			break;
		}
		else if (check_snake(p2_snake, p1_snake, len2)) {
			win = 1;
			break;
		}
		if (p1_snake[0].posx == item.posx && p1_snake[0].posy == item.posy) {
			item.posx = rand() % 36 + 1;
			item.posy = rand() % 32 + 1;
			if (len1 < 300) {
				for (i = 0; i < 5; i++) {
					p1_snake[len1] = p1_snake[len1 - 1];
					len1++;
				}
			}
		}
		if (p2_snake[0].posx == item.posx && p2_snake[0].posy == item.posy) {
			item.posx = rand() % 36 + 1;
			item.posy = rand() % 32 + 1;
			if (len2 < 300) {
				for (i = 0; i < 5; i++) {
					p2_snake[len2] = p2_snake[len2 - 1];
					len2++;
				}
			}
		}
		while (1) {
			for (i = 0; i < len1; i++) if (p1_snake[i].posx == item.posx && p1_snake[i].posy == item.posy) break;
			for (j = 0; j < len2; j++) if (p2_snake[i].posx == item.posx && p2_snake[i].posy == item.posy) break;
			if (i == len1 && j == len2) {
				gotoxy(2 * item.posx + 2, item.posy + 1);
				tc(cc_red);
				printf("♥");
				break;
			}
			else {
				item.posx = rand() % 36 + 1;
				item.posy = rand() % 32 + 1;
			}
		}
		move_snake(p1_snake, p2_snake, len1, len2);
		speed = 100 - 5 * (len1 > len2) - 5 * (len1 <= len2);
		if (speed <= 20) speed = 20;
		Sleep(speed);
	}
	switch (win) {
	case -1: break;
	case 0: tie(); break;
	case 1: p1_win(); break;
	case 2: p2_win(); break;
	}
	Sleep(3000);
}

void guess_n9() {
	cls();
	normalbound(c_gray);
	halfbound(c_gray, 3);
	int sc1 = 0, sc2 = 0, rd1 = 0, rd2 = 0, rd3 = 0, rd4 = 0;
	{
		tc(cc_yellow);
		gotoxy(32, 7);
		printf("■  ■    ■■■");
		gotoxy(32, 8);
		printf("■  ■    ■    ");
		gotoxy(32, 9);
		printf("■  ■    ■■■");
		gotoxy(32, 10);
		printf("■  ■        ■");
		gotoxy(32, 11);
		printf("  ■      ■■■");
		tc(cc_green);
		gotoxy(32, 24);
		printf("■  ■    ■■■");
		gotoxy(32, 25);
		printf("■  ■    ■    ");
		gotoxy(32, 26);
		printf("■  ■    ■■■");
		gotoxy(32, 27);
		printf("■  ■        ■");
		gotoxy(32, 28);
		printf("  ■      ■■■");
	}
	rd1 = rand() % 3;
	rd2 = (rand() / 2) % 3;
	rd3 = (rand() / 3) % 3;
	rd4 = (rand() / 4) % 3;
	print_hand(6, 3, rd1);
	print_hand(52, 3, rd2);
	print_hand(6, 20, rd3);
	print_hand(52, 20, rd4);
	//clock_t c1 = clock();
	//clock_t c2 = clock();
	print_score(sc1, sc2);
	while (sc1 < 20 && sc2 < 20) {
		if (rd1 == (rd2 + 2) % 3) {
			if (GetAsyncKeyState(A) & 0x8000) {
				Sleep(100);
				if (!(GetAsyncKeyState(A) & 0x8001)) {
					sc1++;
					rd1 = rand() % 3;
					rd2 = (rand() / 2) % 3;
					print_hand(6, 3, rd1);
					print_hand(52, 3, rd2);
					print_score(sc1, sc2);
				}
			}
		}
		else if (rd1 == rd2) {
			if (GetAsyncKeyState(W) & 0x8000) {
				Sleep(100);
				if (!(GetAsyncKeyState(W) & 0x8001)) {
					sc1++;
					rd1 = rand() % 3;
					rd2 = (rand() / 2) % 3;
					print_hand(6, 3, rd1);
					print_hand(52, 3, rd2);
					print_score(sc1, sc2);
				}
			}
		}
		else if (rd1 == (rd2 + 1) % 3) {
			if (GetAsyncKeyState(D) & 0x8000) {
				Sleep(100);
				if (!(GetAsyncKeyState(D) & 0x8001)) {
					sc1++;
					rd1 = rand() % 3;
					rd2 = (rand() / 2) % 3;
					print_hand(6, 3, rd1);
					print_hand(52, 3, rd2);
					print_score(sc1, sc2);
				}
			}
		}
		if (rd3 == (rd4 + 2) % 3) {
			if (GetAsyncKeyState(J) & 0x8000) {
				Sleep(100);
				if (!(GetAsyncKeyState(J) & 0x8001)) {
					sc2++;
					rd3 = (rand() / 3) % 3;
					rd4 = (rand() / 4) % 3;
					print_hand(6, 20, rd3);
					print_hand(52, 20, rd4);
					print_score(sc1, sc2);
				}
			}
		}
		else if (rd3 == rd4) {
			if (GetAsyncKeyState(I) & 0x8000) {
				Sleep(100);
				if (!(GetAsyncKeyState(I) & 0x8001)) {
					sc2++;
					rd3 = (rand() / 3) % 3;
					rd4 = (rand() / 4) % 3;
					print_hand(6, 20, rd3);
					print_hand(52, 20, rd4);
					print_score(sc1, sc2);
				}
			}
		}
		else if (rd3 == (rd4 + 1) % 3) {
			if (GetAsyncKeyState(L) & 0x8000) {
				Sleep(100);
				if (!(GetAsyncKeyState(L) & 0x8001)) {
					sc2++;
					rd3 = (rand() / 3) % 3;
					rd4 = (rand() / 4) % 3;
					print_hand(6, 20, rd3);
					print_hand(52, 20, rd4);
					print_score(sc1, sc2);
				}
			}
		}
	}
	print_score(sc1, sc2);
	if (sc1 > sc2) p1_win();
	else if (sc2 > sc1) p2_win();
	else tie();
	Sleep(3000);
}

void main() {
	srand(time(NULL));
	init_screen();
	open_audio(&dwID, mciOpen, mciPlay);
	open(getConsoleWindowHandle());
	waiting();
	title_audio(&dwID, mciOpen, mciPlay);
	maintitle(0);
	stopAllSounds(&dwID);
	cls();
	select_audio(&dwID, mciOpen, mciPlay);
	enter_menu(&dwID);
	exit(0);
	getchar(); //끝
}