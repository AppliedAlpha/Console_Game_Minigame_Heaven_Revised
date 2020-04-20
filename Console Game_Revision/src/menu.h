#pragma once
#include "action.h"
#include "../game_src/game1.h"
#include "../game_src/game2.h"
#include "../game_src/game3.h"
#include "../game_src/game4.h"
#include "../game_src/game5.h"
#include "../game_src/game6.h"
#include "../game_src/game7.h"
#include "../game_src/game8.h"
#include "../game_src/game9.h"

int selectmenu(int selcheck);
void maintitle(int selcheck);
int again(int total1, int total2);

void normalgame(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay);
void selectgame(int sel, int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay);
void enter_menu(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay);