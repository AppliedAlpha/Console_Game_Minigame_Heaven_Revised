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
				printf("¢Æ");
			}
			if (map[j][i] == 2) {
				tc(cc_green);
				gotoxy(2 * i + 2, j + 1);
				printf("¢À");
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
		printf("¢Â");
		gotoxy(2 * p2.posx + 2, p2.posy + 1);
		tc(cc_red);
		printf("¢Â");
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