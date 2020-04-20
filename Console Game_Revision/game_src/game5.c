#include "../src/action.h"

void color_n5(int* total1, int* total2, int* dwID) {
	int i, j, game = 300; //100=1├╩;
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
		printf("б┌");
		gotoxy(2 * p2.posx + 2, p2.posy + 1);
		tc(cc_red);
		printf("б┌");
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
							printf("бс");
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
							printf("бс");
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
							printf("бс");
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
							printf("бс");
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
							printf("бс");
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
							printf("бс");
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
							printf("бс");
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
							printf("бс");
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
		p1_win(&total1, &total2, &dwID);
		tc(cc_yellow);
	}
	else if (m1 < m2) tc(cc_red);
	else tc(cc_cyan);
	gotoxy(32, 37);
	printf("    ");
	gotoxy(32, 37);
	printf("%4d", m1);
	if (m1 < m2) {
		p2_win(&total1, &total2, &dwID);
		tc(cc_yellow);
	}
	else if (m1 > m2) tc(cc_red);
	else {
		tie(&dwID);
		tc(cc_cyan);
	}
	gotoxy(44, 37);
	printf("    ");
	gotoxy(44, 37);
	printf("%d", m2);
	Sleep(3000);
}