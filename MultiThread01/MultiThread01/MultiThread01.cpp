// MultiThread01.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

//�L�ł��킩�� �}���`�X���b�h�@�V���[�Y ���ʌo�������̂ł��B

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
	if (hTh[1] == NULL) {
		printf("�X���b�h1�쐬���s\n");
		return -1;
	}


	hEvent[0] = CreateEvent(NULL, TRUE, FALSE, _T("CH0"));
	hEvent[1] = CreateEvent(NULL, TRUE, FALSE, _T("CH1"));
	hEvent[2] = CreateEvent(NULL, TRUE, FALSE, _T("MAINEVENT"));

	//�e�X���b�h���s�J�n
	for (i = 0; i < 2; i++)
		ResumeThread(hTh[i]);

	printf("�C�x���g0���V�O�i����Ԃɂ��܂�\n");
	SetEvent(hEvent[0]);

	WaitForSingleObject(hEvent[2], INFINITE);
	printf("�e���I�����܂�\n");
	for (i = 0; i < 2; i++)
		CloseHandle(hTh[i]);

	return 0;
}

unsigned __stdcall mythread0(LPVOID lpx)
{
	int i;

	WaitForSingleObject(hEvent[0], INFINITE);
	for (i = 0; i < 10; i++)
		printf("�q�X���b�h0[%d]\n", i);

	printf("�C�x���g1���V�O�i����Ԃɂ��܂�\n");
	SetEvent(hEvent[1]);

	return 0;
}

unsigned __stdcall mythread1(LPVOID lpx)
{
	int i;

	WaitForSingleObject(hEvent[1], INFINITE);
	for (i = 0; i < 10; i++)
		printf("�q�X���b�h1[%d]\n", i);

	printf("�C�x���g2���V�O�i����Ԃɂ��܂�\n");
	SetEvent(hEvent[2]);
	return 0;
}
