// MultiThread01.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

//�L�ł��킩�� �}���`�X���b�h�@�V���[�Y ���ʌo�������̂ł��B

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
		printf("�~���[�e�b�N�X�쐬���s\n");
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
		printf("�X���b�h0�쐬���s\n");
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
		printf("�X���b�h1�쐬���s\n");
		return -1;
	}

	//�e�X���b�h���s�J�n
	for (i = 0; i < 2; i++)
		ResumeThread(hTh[i]);

	_getch();
	bThEnd = TRUE;

	WaitForMultipleObjects(2, hEvent, TRUE, INFINITE);
	for (i = 0; i < 2; i++) {
		if (CloseHandle(hTh[i])) {
			printf("hTh[%d]�̃N���[�Y�ɐ���\n", i);
		}
		else {
			printf("hTh[%d]�̃N���[�Y���s\n", i);
		}
	}
	if (CloseHandle(hMutex)) {
		printf("�~���[�e�b�N�X�n���h���̃N���[�Y�ɐ���\n");
	}
	else {
		printf("�~���[�e�b�N�X�n���h���̃N���[�Y�Ɏ��s\n");
	}
	printf("�e���I�����܂�\n");
	return 0;
}

unsigned __stdcall mythread0(LPVOID lpx)
{
	HANDLE hM;

	hM = *(HANDLE *)lpx;

	while (!bThEnd) {
		WaitForSingleObject(hM, INFINITE);
		printf("�X���b�h�O��%d��\��\n", i++);
		ReleaseMutex(hM);
	}
	WaitForSingleObject(hM, INFINITE);
	printf("�X���b�h�O�I��\n");
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
		printf("�X���b�h�P��%d��\��\n", i++);
		ReleaseMutex(hM);
	}
	WaitForSingleObject(hM, INFINITE);
	printf("�X���b�h�P�I��\n");
	ReleaseMutex(hM);
	SetEvent(hEvent[1]);
	return 0;

}

