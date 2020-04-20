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
	printf("¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");
	gotoxy(16, 19);
	printf("¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");
	tc(c_black);
	gotoxy(18, 18);
	printf("¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");
	rd1[0] = rand() % 11 + 20;
	rd1[1] = rand() % 31 + 170;
	rd1[2] = rand() % 61 + 270;
	rd2[0] = rand() % 11 + 20;
	rd2[1] = rand() % 31 + 170;
	rd2[2] = rand() % 61 + 270;
	while (sc1 <= 5000 && sc2 <= 5000) {
		tc(cc_green);
		gotoxy(18, 18);
		printf("¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");
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
		printf("¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");
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