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
	// 랜덤 난수 생성
	srand(time(NULL));

	// 콘솔창 초기화 및 오프닝 처리
	init_screen();
	open_audio(&dwID, mciOpen, mciPlay);
	open(getConsoleWindowHandle());

	// 타이틀 화면 처리
	waiting();
	title_audio(&dwID, mciOpen, mciPlay);
	maintitle(0);

	// 선택 및 메뉴 화면 처리
	stopAllSounds(&dwID);
	cls();
	select_audio(&dwID, mciOpen, mciPlay);
	enter_menu(&dwID, mciOpen, mciPlay);

	// 종료
	exit(0);
	int finish = getchar();
}