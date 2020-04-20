void guess_n9() {
	cls();
	normalbound(c_gray);
	halfbound(c_gray, 3);
	int sc1 = 0, sc2 = 0, rd1 = 0, rd2 = 0, rd3 = 0, rd4 = 0;
	{
		tc(cc_yellow);
		gotoxy(32, 7);
		printf("бс  бс    бсбсбс");
		gotoxy(32, 8);
		printf("бс  бс    бс    ");
		gotoxy(32, 9);
		printf("бс  бс    бсбсбс");
		gotoxy(32, 10);
		printf("бс  бс        бс");
		gotoxy(32, 11);
		printf("  бс      бсбсбс");
		tc(cc_green);
		gotoxy(32, 24);
		printf("бс  бс    бсбсбс");
		gotoxy(32, 25);
		printf("бс  бс    бс    ");
		gotoxy(32, 26);
		printf("бс  бс    бсбсбс");
		gotoxy(32, 27);
		printf("бс  бс        бс");
		gotoxy(32, 28);
		printf("  бс      бсбсбс");
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