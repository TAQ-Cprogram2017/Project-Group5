#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#ifndef _HEAD_H_
#define _HEAD_H_
/*ȫ�ֱ���*/
static HWND hwndList[5];//�б��ľ��
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);        //��������������Ϣ�ĺ���
BOOL CALLBACK Input1DlgProc(HWND, UINT, WPARAM, LPARAM);      //�������������½��ṹ��ĺ���
BOOL CALLBACK Input2DlgProc(HWND, UINT, WPARAM, LPARAM);      //������������ɾ��ָ����Ŀ�ĺ���
/*��ť������*/
#define NUM (sizeof (button)/sizeof (button[0]))
/*�ṹ��*/
struct
{
	int iStyle;
	TCHAR * szText;
}
button[] =
{
	BS_PUSHBUTTON,           TEXT("�����ʾ��¼"),
	BS_PUSHBUTTON,           TEXT("���¶�ȡ��¼"),
	BS_PUSHBUTTON,           TEXT("���浱ǰ��¼"),
	BS_PUSHBUTTON,           TEXT("����һ���¼"),
	BS_PUSHBUTTON,           TEXT("ɾ��ָ����¼"),
};

void Empty(HWND hwnd)
{
   MessageBox(hwnd, TEXT("���ڱ��γ���Ҫ����ΪC���ԣ�������ܵ�ʵ���뱾ѧ�ڵ��ص�����󣬹��ݲ�������"), TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
}


#endif // _HEAD_H_