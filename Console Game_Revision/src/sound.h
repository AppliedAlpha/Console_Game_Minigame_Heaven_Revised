#pragma once

void stopAllSounds(int* dwID);
void open_audio(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay);
void title_audio(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay);
void select_audio(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay);