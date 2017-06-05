#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#ifndef _HEAD_H_
#define _HEAD_H_
/*全局变量*/
int iIndex = 0;
static TCHAR szHead[] = TEXT("        条目细则:");
static TCHAR szMoney[] = TEXT("初始金额");
static TCHAR szLocation[] = TEXT("初始地点");
static TCHAR szAim[] = TEXT("初始目的");
static TCHAR szTime[] = TEXT("初始时间");
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);        //声明用来处理消息的函数
BOOL CALLBACK Input1DlgProc(HWND, UINT, WPARAM, LPARAM);      //声明用来处理新建结构体的函数
BOOL CALLBACK Input2DlgProc(HWND, UINT, WPARAM, LPARAM);      //声明用来处理删除指定条目的函数
/*按钮的数量*/
#define NUM (sizeof (button)/sizeof (button[0]))
struct
{
	int iStyle;
	TCHAR * szText;
}
button[] =
{
	BS_PUSHBUTTON,           TEXT("清空显示记录"),
	BS_PUSHBUTTON,           TEXT("重新读取记录"),
	BS_PUSHBUTTON,           TEXT("保存当前记录"),
	BS_PUSHBUTTON,           TEXT("新增一项记录"),
	BS_PUSHBUTTON,           TEXT("删除指定记录"),
};


#endif // _HEAD_H_