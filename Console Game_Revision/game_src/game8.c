#include "../src/action.h"
int dir1 = -1, dir2 = -1;

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
//πÏ √Êµπ »Æ¿Œ

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
		printf("°›");
	}
	switch (dir1) {
	case 0: p1_snake[0].posy--; break;
	case 1: p1_snake[0].posy++; break;
	case 2: p1_snake[0].posx--; break;
	case 3: p1_snake[0].posx++; break;
	}
	gotoxy(2 * p1_snake[0].posx + 2, p1_snake[0].posy + 1);
	tc(cc_cyan);
	printf("°‹");
	if (dir2 != -1) {
		int i;
		gotoxy(2 * p2_snake[len2 - 1].posx + 2, p2_snake[len2 - 1].posy + 1);
		printf("  ");
		for (i = len2 - 1; i > 0; i--) p2_snake[i] = p2_snake[i - 1];
		gotoxy(2 * p2_snake[1].posx + 2, p2_snake[1].posy + 1);
		tc(cc_yellow);
		printf("°›");
	}
	switch (dir2) {
	case 0: p2_snake[0].posy--; break;
	case 1: p2_snake[0].posy++; break;
	case 2: p2_snake[0].posx--; break;
	case 3: p2_snake[0].posx++; break;
	}
	gotoxy(2 * p2_snake[0].posx + 2, p2_snake[0].posy + 1);
	tc(cc_yellow);
	printf("°‹");
}
//πÏ ¿Ãµø

void tail_n8(int* total1, int* total2, int* dwID) {
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
		printf("°›");
		p2_snake[i].posx = 28 + i;
		p2_snake[i].posy = 18;
		gotoxy(2 * p2_snake[i].posx + 2, p2_snake[i].posy + 1);
		tc(cc_yellow);
		printf("°›");
	}
	gotoxy(2 * p1_snake[0].posx + 2, p1_snake[0].posy + 1);
	tc(cc_cyan);
	printf("°‹");
	gotoxy(2 * p2_snake[0].posx + 2, p2_snake[0].posy + 1);
	tc(cc_yellow);
	printf("°‹");
	item.posx = rand() % 36 + 1;
	item.posy = rand() % 32 + 1;
	if (item.posy == 18) item.posy = rand() % 17 + 1;
	gotoxy(2 * item.posx + 2, item.posy + 1);
	tc(cc_red);
	printf("¢æ");
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
				printf("¢æ");
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
	case 0: tie(&dwID); break;
	case 1: p1_win(&total1, &total2, &dwID); break;
	case 2: p2_win(&total1, &total2, &dwID); break;
	}
	Sleep(3000);
}