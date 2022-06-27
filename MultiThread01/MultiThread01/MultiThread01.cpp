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
	unsigned int thID;
	HANDLE hTh;
	int i;

	hTh = (HANDLE)_beginthreadex(NULL, 0, mythread, NULL, 0, &thID);

	for (i = 0; i < 20; i++) {
		printf("Main�ł�[%d]\n", i);
	}

	if (hTh != NULL) {
		CloseHandle(hTh);
		printf("�n���h���N���[�Y���܂���\n");
	}

    return 0;
}

unsigned __stdcall mythread(void *lpx)
{
	int i;
	for (i = 0; i < 4; i++)
		printf("�X���b�h�ł�[%d]\n", i);
	return 0;
}
