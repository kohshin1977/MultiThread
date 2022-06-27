// MultiThread01.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

//猫でもわかる マルチスレッド　シリーズ を写経したものです。

#include "stdafx.h"

#include <stdio.h>
#include <windows.h>
#include <process.h>

unsigned __stdcall mythread0(void *);
unsigned __stdcall mythread1(void *);

HANDLE hEvent[3];

int main()
{
	int i;
	HANDLE hTh[2];
	unsigned int thID[2];

	hTh[0] = (HANDLE)_beginthreadex(
		NULL,
		0,
		mythread0,
		NULL,
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
		NULL,
		CREATE_SUSPENDED,
		&thID[1]
	);
	if (hTh[1] == NULL) {
		printf("スレッド1作成失敗\n");
		return -1;
	}


	hEvent[0] = CreateEvent(NULL, TRUE, FALSE, _T("CH0"));
	hEvent[1] = CreateEvent(NULL, TRUE, FALSE, _T("CH1"));
	hEvent[2] = CreateEvent(NULL, TRUE, FALSE, _T("MAINEVENT"));

	//各スレッド実行開始
	for (i = 0; i < 2; i++)
		ResumeThread(hTh[i]);

	printf("イベント0をシグナル状態にします\n");
	SetEvent(hEvent[0]);

	WaitForSingleObject(hEvent[2], INFINITE);
	printf("親を終了します\n");
	for (i = 0; i < 2; i++)
		CloseHandle(hTh[i]);

	return 0;
}

unsigned __stdcall mythread0(LPVOID lpx)
{
	int i;

	WaitForSingleObject(hEvent[0], INFINITE);
	for (i = 0; i < 10; i++)
		printf("子スレッド0[%d]\n", i);

	printf("イベント1をシグナル状態にします\n");
	SetEvent(hEvent[1]);

	return 0;
}

unsigned __stdcall mythread1(LPVOID lpx)
{
	int i;

	WaitForSingleObject(hEvent[1], INFINITE);
	for (i = 0; i < 10; i++)
		printf("子スレッド1[%d]\n", i);

	printf("イベント2をシグナル状態にします\n");
	SetEvent(hEvent[2]);
	return 0;
}
