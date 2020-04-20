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

void main() {
	srand(time(NULL));

	init_screen();
	//open_audio(&dwID, mciOpen, mciPlay);
	//open(getConsoleWindowHandle());

	waiting();
	title_audio(&dwID, mciOpen, mciPlay);
	maintitle(0);

	stopAllSounds(&dwID);
	cls();
	select_audio(&dwID, mciOpen, mciPlay);
	enter_menu(&dwID, mciOpen, mciPlay);

	exit(0);
	int finish = getchar();
}