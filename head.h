#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#ifndef _HEAD_H_
#define _HEAD_H_
/*全局变量*/
static HWND hwndList[5];//列表框的句柄
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