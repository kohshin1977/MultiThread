// MultiThread01.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

//�L�ł��킩�� �}���`�X���b�h�@�V���[�Y ���ʌo�������̂ł��B

#include "stdafx.h"

#include <stdio.h>
#include <windows.h>
#include <process.h>

unsigned __stdcall mythread0(void *);
unsigned __stdcall mythread1(void *);
unsigned __stdcall mythread2(void *);

int main()
{
	int i;
	HANDLE hTh[3];
	unsigned int thID[3];

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

	hTh[2] = (HANDLE)_beginthreadex(
		NULL,
		0,
		mythread2,
		NULL,
		CREATE_SUSPENDED,
		&thID[2]
	);

	if (hTh[2] == 0) {
		printf("�X���b�h2�쐬���s\n");
		return -1;
	}

	for (i = 0; i < 3; i++)
		ResumeThread(hTh[i]);

	for (i = 0; i < 10; i++)
		printf("Main [%d]\n", i);

	WaitForMultipleObjects(3, hTh, TRUE, INFINITE);

	for (i = 0; i < 3; i++)
		CloseHandle(hTh[i]);

	return 0;
}

unsigned __stdcall mythread0(void *lpx)
{
	int i;
	for (i = 0; i < 10; i++)
		printf("�q�X���b�h0[%d]\n", i);

	printf("�q�X���b�h0�I��!\n");

	return 0;
}

unsigned __stdcall mythread1(void *lpx)
{
	int i;
	for (i = 0; i < 20; i++)
		printf("�q�X���b�h1[%d]\n", i);

	printf("�q�X���b�h1�I��!\n");

	return 0;
}

unsigned __stdcall mythread2(void *lpx)
{
	int i;
	for (i = 0; i < 5; i++)
		printf("�q�X���b�h2[%d]\n", i);

	printf("�q�X���b�h2�I��!\n");

	return 0;
}
