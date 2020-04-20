#include "menu.h"
#include "sound.h"
#include "action.h"

int selectmenu(int selcheck) {
	char ch = 0;
	if (selcheck) PlaySound(TEXT("../audio/tp_click.wav"), 0, SND_FILENAME | SND_ASYNC);
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
	waiting();
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
	return selcheck - 1;
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

	draw_title(getConsoleWindowHandle());
	if (!selcheck) Sleep(800);
	else PlaySound(TEXT("../audio/tp_click.wav"), 0, SND_FILENAME | SND_ASYNC);

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

int again(int total1, int total2) {
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

void normalgame(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay) {
	int arr[9];
	int i, j, rd, tmp;
	cls();
	normalbound(c_gray);
	int total1 = 0, total2 = 0;
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
		waiting();
		play_audio(&dwID, mciOpen, mciPlay);
		waiting();
		switch (arr[i]) {
		case 1: click_n1(&total1, &total2); break;
		case 2: maze_n2(&total1, &total2); break;
		case 3: heart_n3(&total1, &total2); break;
		case 4: run_n4(&total1, &total2); break;
		case 5: color_n5(&total1, &total2); break;
		case 6: thief_n6(&total1, &total2); break;
		case 7: star_n7(&total1, &total2); break;
		case 8: tail_n8(&total1, &total2); break;
		case 9: guess_n9(&total1, &total2); break;
		}
		stopAllSounds(&dwID);
		cls();
		normalbound(c_gray);
		waiting();
	}
	if (again(total1, total2)) {
		select_audio(&dwID, mciOpen, mciPlay);
		waiting();
		return;
	}
	else exit(0);
}

void selectgame(int sel, int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay) {
	int i;
	char ch;
	int rc = rand() % 6 + 9;
	tc(rc);
	if (sel >= 0) PlaySound(TEXT("../audio/tp_click.wav"), 0, SND_FILENAME | SND_ASYNC);
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
					selectgame(-2, &dwID, mciOpen, mciPlay);
					return;
				}
				else {
					selectgame(-1, &dwID, mciOpen, mciPlay);
					return;
				}
			}
			else {
				for (i = 0; i < 9; i++) {
					if (ch == order[i] || ch == order[i] + 32) {
						selectgame(i + 10, &dwID, mciOpen, mciPlay);
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
		waiting();
		explain(sel);
		play_audio(&dwID, mciOpen, mciPlay);
	}
	Sleep(100);
	waiting();
	switch (sel) {
	case 1: click_n1(0, 0); break;
	case 2: maze_n2(0, 0); break;
	case 3: heart_n3(0, 0); break;
	case 4: run_n4(0, 0); break;
	case 5: color_n5(0, 0); break;
	case 6: thief_n6(0, 0); break;
	case 7: star_n7(0, 0); break;
	case 8: tail_n8(0, 0); break;
	case 9: guess_n9(0, 0); break;
	default: cls(); Sleep(900); break;
	}
	cls();
	normalbound(c_gray);
	waiting();
	selectgame(0, &dwID, mciOpen, mciPlay);
	return;
}

void enter_menu(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay) {
	while (1) {
		waiting();
		int selme = selectmenu(0); //메뉴 고르기
		stopAllSounds(&dwID); //소리 정지
		if (!selme) normalgame(&dwID, mciOpen, mciPlay); //노말
		else {
			cls();
			normalbound(c_gray);
			selectgame(0, &dwID, mciOpen, mciPlay); //선택
		}
	}
}