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