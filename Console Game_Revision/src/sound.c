#include "sound.h"

// 모든 소리 정지 (Canceling)
void stopAllSounds(int* dwID) {
	mciSendCommandW(*dwID, MCI_CLOSE, 0, NULL);
	PlaySound(NULL, 0, SND_PURGE);
}

// 오프닝 소리 출력
void open_audio(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay) {
	mciOpen.lpstrElementName = "audio/Glacia1.mp3";
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
	*dwID = mciOpen.wDeviceID;
	mciSendCommand(*dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
}

// 타이틀 화면 소리 출력
// SND (효과음용)와 MCI (배경음용) 동시 사용
void title_audio(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay) {
	PlaySound(TEXT("audio/michun.wav"), 0, SND_FILENAME | SND_ASYNC);
	mciOpen.lpstrElementName = "audio/Glacia2.mp3";
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
	*dwID = mciOpen.wDeviceID;
	mciSendCommand(*dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
}

// 선택 화면 소리 출력
// SND (효과음용)와 MCI (배경음용) 동시 사용
void select_audio(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay) {
	waiting();
	stopAllSounds(&dwID);
	PlaySound(TEXT("audio/select_mode.wav"), 0, SND_FILENAME | SND_ASYNC);
	Sleep(20);
	waiting();
	mciOpen.lpstrElementName = "audio/sunburst.mp3";
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
	*dwID = mciOpen.wDeviceID;
	mciSendCommand(*dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
}

// 게임 플레이 중 음악 출력
void play_audio(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay) {
	mciOpen.lpstrElementName = "audio/dating_tense.mp3";
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
	*dwID = mciOpen.wDeviceID;
	mciSendCommand(*dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)& mciPlay);
}