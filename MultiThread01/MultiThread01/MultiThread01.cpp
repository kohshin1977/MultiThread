// MultiThread01.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

//�L�ł��킩�� �}���`�X���b�h�@�V���[�Y ���ʌo�������̂ł��B

#include "stdafx.h"

#include <stdio.h>
#include <windows.h>
#include <process.h>

unsigned __stdcall mythread0(void *);
unsigned __stdcall mythread1(void *);

int n;
CRITICAL_SECTION cs;

int main()
{
	int i;
	HANDLE hTh[2];
	unsigned int thID[2];

	InitializeCriticalSection(&cs);

	hTh[0] = (HANDLE)_beginthreadex(
		NULL,
		0,
		mythread0,
		NULL,
		CREATE_SUSPENDED,
		&thID[0]
	);
	if (hTh[0] == 0) {
		printf("�X���b�h0�쐬���s\n");
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
	if (hTh[1] == 0) {
		printf("�X���b�h1�쐬���s\n");
		return -1;
	}

	for (i = 0; i < 2; i++)
		ResumeThread(hTh[i]);


	WaitForMultipleObjects(2, hTh, TRUE, INFINITE);

	for (i = 0; i < 2; i++)
		CloseHandle(hTh[i]);

	DeleteCriticalSection(&cs);

	return 0;
}

unsigned __stdcall mythread0(void *lpx)
{
	int esc = 0;

	while (1) {
		EnterCriticalSection(&cs);
		if (n < 20) {
			printf("mythread0 n = %d\n", n);
			n++;
		}
		else {
			esc = 1;
		}
		LeaveCriticalSection(&cs);
		if (esc)
			break;
	}

	return 0;
}

unsigned __stdcall mythread1(void *lpx)
{
	int esc = 0;

	while (1) {
		EnterCriticalSection(&cs);
		if (n < 20) {
			printf("mythread1 n = %d\n", n);
			n++;
		}
		else {
			esc = 1;
		}
		LeaveCriticalSection(&cs);
		if (esc)
			break;
	}

	return 0;
}
