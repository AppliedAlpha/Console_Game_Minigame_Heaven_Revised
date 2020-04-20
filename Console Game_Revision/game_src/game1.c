#include "../src/action.h"

void click_n1(int* total1, int* total2, int* dwID) {
	cls();
	int i, j, sc1 = 0, sc2 = 0;
	{
		normalbound(c_gray);
		halfbound(c_gray, 0);
		for (i = 2; i <= 33; i++) {
			tc(c_white);
			gotoxy(18, i);
			printf("бсбс");
			gotoxy(58, i);
			printf("бсбс");
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
						printf("бс");
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
						printf("бс");
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
		p1_win(&total1, &total2, &dwID);
	}
	else if (sc2 > sc1) {
		winner(62, 2);
		p2_win(&total1, &total2, &dwID);
	}
	else tie(&dwID);
	Sleep(3000);
}
//edit 