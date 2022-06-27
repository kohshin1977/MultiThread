// MultiThread01.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

//猫でもわかる マルチスレッド　シリーズ を写経したものです。

#include "stdafx.h"

#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <conio.h>

#define MUTEXNAME _T("MYMUTEX")

unsigned __stdcall mythread0(void *);
unsigned __stdcall mythread1(void *);

HANDLE hEvent[2];

BOOL bThEnd = FALSE;
int i;

int main()
{
	int i;
	HANDLE hTh[2];
	unsigned int thID[2];
	HANDLE hMutex;

	hMutex = CreateMutex(NULL, FALSE, MUTEXNAME);
	if (hMutex == NULL) {
		printf("ミューテックス作成失敗\n");
		return -1;
	}
	hEvent[0] = CreateEvent(NULL, TRUE, FALSE, _T("CH0"));
	hEvent[1] = CreateEvent(NULL, TRUE, FALSE, _T("CH1"));


	hTh[0] = (HANDLE)_beginthreadex(
		NULL,
		0,
		mythread0,
		&hMutex,
		CREATE_SUSPENDED,
		&thID[0]
	);
	if (hTh[0] == NULL) {
		printf("スレッド0作成失敗\n");
		return -1;
	}

	hTh[1] = (HANDLE)_beginthreadex(
		NULL,
		0,
		mythread1,
		&hMutex,
		CREATE_SUSPENDED,
		&thID[1]
	);
	if (hTh[1] == NULL) {
		printf("スレッド1作成失敗\n");
		return -1;
	}

	//各スレッド実行開始
	for (i = 0; i < 2; i++)
		ResumeThread(hTh[i]);

	_getch();
	bThEnd = TRUE;

	WaitForMultipleObjects(2, hEvent, TRUE, INFINITE);
	for (i = 0; i < 2; i++) {
		if (CloseHandle(hTh[i])) {
			printf("hTh[%d]のクローズに成功\n", i);
		}
		else {
			printf("hTh[%d]のクローズ失敗\n", i);
		}
	}
	if (CloseHandle(hMutex)) {
		printf("ミューテックスハンドルのクローズに成功\n");
	}
	else {
		printf("ミューテックスハンドルのクローズに失敗\n");
	}
	printf("親を終了します\n");
	return 0;
}

unsigned __stdcall mythread0(LPVOID lpx)
{
	HANDLE hM;

	hM = *(HANDLE *)lpx;

	while (!bThEnd) {
		WaitForSingleObject(hM, INFINITE);
		printf("スレッド０が%dを表示\n", i++);
		ReleaseMutex(hM);
	}
	WaitForSingleObject(hM, INFINITE);
	printf("スレッド０終了\n");
	ReleaseMutex(hM);
	SetEvent(hEvent[0]);                                \
	return 0;
}

unsigned __stdcall mythread1(LPVOID lpx)
{
	HANDLE hM;

	hM = *(HANDLE *)lpx;

	while (!bThEnd) {
		WaitForSingleObject(hM, INFINITE);
		printf("スレッド１が%dを表示\n", i++);
		ReleaseMutex(hM);
	}
	WaitForSingleObject(hM, INFINITE);
	printf("スレッド１終了\n");
	ReleaseMutex(hM);
	SetEvent(hEvent[1]);
	return 0;

}

