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
					printf("¡á");
					gotoxy(2 * i + 42, j + 1);
					printf("¡á");
				}
			}
		}
		tc(cc_yellow);
		gotoxy(36, 33);
		printf("¢Ñ");
		gotoxy(76, 33);
		printf("¢Ñ");
	}
	Sleep(1000);
	while (1) {
		gotoxy(2 * p1.posx + 2, p1.posy + 1);
		tc(cc_cyan);
		printf("¢Â");
		gotoxy(2 * p2.posx + 42, p2.posy + 1);
		tc(cc_red);
		printf("¢Â");
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