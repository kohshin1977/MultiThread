// MultiThread01.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

//�L�ł��킩�� �}���`�X���b�h�@�V���[�Y ���ʌo�������̂ł��B

#include "stdafx.h"

#include <stdio.h>
#include <windows.h>
#include <process.h>

unsigned __stdcall mythread(void *);

int main()
{
	int i;
	HANDLE hTh;
	unsigned int thID;

	hTh = (HANDLE)_beginthreadex(NULL, 0, mythread, NULL, 0, &thID);
	if (hTh == 0) {
		printf("�X���b�h�쐬���s\n");
		return -1;
	}

	for (i = 0; i < 10; i++)
		printf("Main [%d]\n", i);

	WaitForSingleObject(hTh, INFINITE);
	CloseHandle(hTh);

	return 0;
}

unsigned __stdcall mythread(void *lpx)
{
	int i;
	for (i = 0; i < 4; i++)
		printf("�X���b�h�ł�[%d]\n", i);
	return 0;
}
