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
	HANDLE hTh;
	int i;

	hTh = (HANDLE)_beginthreadex(NULL, 0, mythread, NULL, 0, &thID);

	for (i = 0; i < 20; i++) {
		printf("Mainです[%d]\n", i);
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
