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