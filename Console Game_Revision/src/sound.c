#include "sound.h"

// ��� �Ҹ� ���� (Canceling)
void stopAllSounds(int* dwID) {
	mciSendCommandW(*dwID, MCI_CLOSE, 0, NULL);
	PlaySound(NULL, 0, SND_PURGE);
}

// ������ �Ҹ� ���
void open_audio(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay) {
	mciOpen.lpstrElementName = "audio/Glacia1.mp3";
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
	*dwID = mciOpen.wDeviceID;
	mciSendCommand(*dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
}

// Ÿ��Ʋ ȭ�� �Ҹ� ���
// SND (ȿ������)�� MCI (�������) ���� ���
void title_audio(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay) {
	PlaySound(TEXT("audio/michun.wav"), 0, SND_FILENAME | SND_ASYNC);
	mciOpen.lpstrElementName = "audio/Glacia2.mp3";
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
	*dwID = mciOpen.wDeviceID;
	mciSendCommand(*dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
}

// ���� ȭ�� �Ҹ� ���
// SND (ȿ������)�� MCI (�������) ���� ���
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

// ���� �÷��� �� ���� ���
void play_audio(int* dwID, MCI_OPEN_PARMS mciOpen, MCI_PLAY_PARMS mciPlay) {
	mciOpen.lpstrElementName = "audio/dating_tense.mp3";
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
	*dwID = mciOpen.wDeviceID;
	mciSendCommand(*dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)& mciPlay);
}