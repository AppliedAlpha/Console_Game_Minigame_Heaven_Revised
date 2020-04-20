#include "sound.h"

void stopAllSounds(int* dwID) {
	mciSendCommandW(*dwID, MCI_CLOSE, 0, NULL);
	PlaySound(NULL, 0, SND_PURGE);
}

void open_audio(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay) {
	mciOpen.lpstrElementName = "audio/Glacia1.mp3";
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
	*dwID = mciOpen.wDeviceID;
	mciSendCommand(*dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
}

void title_audio(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay) {
	PlaySound(TEXT("michun.wav"), 0, SND_FILENAME | SND_ASYNC); //미천합니다 Sound
	mciOpen.lpstrElementName = "audio/Glacia2.mp3"; //배경음
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
	*dwID = mciOpen.wDeviceID;
	mciSendCommand(*dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay); //배경음 플레이
}

void select_audio(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay) {
	waiting();
	stopAllSounds(&dwID);
	PlaySound(TEXT("select_mode.wav"), 0, SND_FILENAME | SND_ASYNC);
	Sleep(20);
	waiting();
	mciOpen.lpstrElementName = "sunburst.mp3";
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
	*dwID = mciOpen.wDeviceID;
	mciSendCommand(*dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
}