#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#ifndef _HEAD_H_
#define _HEAD_H_
/*ȫ�ֱ���*/
int iIndex = 0;
static TCHAR szHead[] = TEXT("        ��Ŀϸ��:");
static TCHAR szMoney[] = TEXT("��ʼ���");
static TCHAR szLocation[] = TEXT("��ʼ�ص�");
static TCHAR szAim[] = TEXT("��ʼĿ��");
static TCHAR szTime[] = TEXT("��ʼʱ��");
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);        //��������������Ϣ�ĺ���
BOOL CALLBACK Input1DlgProc(HWND, UINT, WPARAM, LPARAM);      //�������������½��ṹ��ĺ���
BOOL CALLBACK Input2DlgProc(HWND, UINT, WPARAM, LPARAM);      //������������ɾ��ָ����Ŀ�ĺ���
/*��ť������*/
#define NUM (sizeof (button)/sizeof (button[0]))
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


#endif // _HEAD_H_