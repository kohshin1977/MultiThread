// MultiThread01.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

//猫でもわかる マルチスレッド　シリーズ を写経したものです。

#include "stdafx.h"

#include <stdio.h>
#include <windows.h>
#include <process.h>

unsigned __stdcall mythread(void *);

int main()
{
	unsigned int thID;
	DWORD dwExCode;

	HANDLE hTh;
	int i;

	hTh = (HANDLE)_beginthreadex(NULL, 0, mythread, NULL, 0, &thID);
	if (hTh == 0) {
		printf("スレッド作成失敗\n");
		return -1;
	}
	for (i = 0; i < 10; i++)
		printf("Main [%d]\n", i);


	while (1) {
		GetExitCodeThread(hTh, &dwExCode);
		if (dwExCode == STILL_ACTIVE) {
			printf("スレッド稼働中\n");
		}
		else {
			break;
		}
	}

	if (hTh != NULL) {
		CloseHandle(hTh);
		printf("ハンドルクローズしました\n");
	}

	return 0;
}

unsigned __stdcall mythread(void *lpx)
{
	int i;
	for (i = 0; i < 4; i++)
		printf("スレッドです[%d]\n", i);
	return 0;
}
