#include<windows.h>
#include"head.h"
#include"function.h"
pINAEX pHead;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);        //声明用来处理消息的函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("MyWindow");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;        //声明一个窗口类对象

	/*以下为窗口类对象wndclass的属性*/
	wndclass.style = CS_HREDRAW | CS_VREDRAW;                         //窗口样式
	wndclass.lpszClassName = szAppName;                               //窗口类名
	wndclass.lpszMenuName = NULL;                                     //窗口菜单:无
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);    //窗口背景颜色
	wndclass.lpfnWndProc = WndProc;                                   //窗口处理函数
	wndclass.cbWndExtra = 0;                                          //窗口实例扩展:无
	wndclass.cbClsExtra = 0;                                          //窗口类扩展:无
	wndclass.hInstance = hInstance;                                   //窗口实例句柄
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);               //窗口最小化图标:使用缺省图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);                 //窗口采用箭头光标
	if (!RegisterClass(&wndclass))
	{    //注册窗口类, 如果注册失败弹出错误提示
		MessageBox(NULL, TEXT("程序初始化失败."), TEXT("错误!"), MB_OK | MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(           //创建窗口
		szAppName,                 //窗口类名
		TEXT("我的记账本"),          //窗口标题
		WS_OVERLAPPEDWINDOW,       //窗口的风格
		CW_USEDEFAULT,             //窗口初始显示位置x:使用缺省值
		CW_USEDEFAULT,             //窗口初始显示位置y:使用缺省值
		CW_USEDEFAULT,             //窗口的宽度:使用缺省值
		CW_USEDEFAULT,             //窗口的高度:使用缺省值
		NULL,                      //父窗口:无
		NULL,                      //子菜单:无
		hInstance,                 //该窗口应用程序的实例句柄 
		NULL                       //
	);
	ShowWindow(hwnd, iCmdShow);        //显示窗口
	UpdateWindow(hwnd);                //更新窗口
	while (GetMessage(&msg, NULL, 0, 0))        //从消息队列中获取消息
	{
		TranslateMessage(&msg);                 //将虚拟键消息转换为字符消息
		DispatchMessage(&msg);                  //分发到回调函数(过程函数)
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndButton[NUM];//按钮子窗体的句柄
	static RECT rect; //矩形结构
	static HWND hwndList;
	static TCHAR szTop[] = TEXT("         项目序号       收支金额            原因或目的           地点            时间   "),
		         szFormat[] = TEXT("%-16s%04W-%04X %04X-%04X"),
		         szBuffer[50];
	static int cxChar, cyChar;
	int i;
	HDC hdc;                //设备环境句柄
	PAINTSTRUCT ps;         //绘制结构
	switch (message)        //处理得到的消息
	{
	case WM_CREATE:          //窗口创建完成时发来的消息
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());
		for(i=0;i<NUM;i++)
			hwndButton[i]=CreateWindow//创建按钮子窗体
			(
			TEXT("button"),//按钮子窗体的类名
			button[i].szText,//按钮子窗体的文本
			WS_CHILD | WS_VISIBLE | button[i].iStyle, //按钮子窗体的类型
			30+cxChar, 30+15*i+cyChar*(1 + 2 * i),//按钮子窗体的位置
			15 * cxChar, 2.5* cyChar , //按钮子窗体的大小
			hwnd,//父窗体名
			(HMENU)i, //子窗体参数
			((LPCREATESTRUCT)lParam)->hInstance,//案例句柄
			NULL//额外参数
			);
		hwndList = CreateWindow(//创建列表框子窗体
			TEXT("listbox"),// 列表框子窗体的类名
			NULL,
			WS_CHILD | WS_VISIBLE | LBS_STANDARD,//列表框子窗体的类型
			200 + cxChar, 3 * cyChar,//列表框子窗体的位置
			85 * cxChar, 22 * cyChar,//列表框子窗体的大小
			hwnd,//父窗体名
			(HMENU)NUM + 1,//子窗体参数
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),//案例句柄
			NULL);//额外参数
		pHead = ListInitialise(0, 0, 0, 0);
		ReadData(pHead);
		MessageBox(hwnd, TEXT("欢迎使用记账本。"), TEXT("初始化成功"), MB_OK | MB_ICONINFORMATION);
		return 0;
    
	case WM_SIZE:
		rect.left = 15 * cxChar;
		rect.top = 2 * cyChar;
		rect.right = LOWORD(lParam);
		rect.bottom = HIWORD(lParam);
		return 0;
	case WM_PAINT:
		InvalidateRect(hwnd,&rect,TRUE);
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 20 * cxChar, 10+cyChar, szTop, lstrlen(szTop));//输出文字数组开头的坐标，名以及长度
		EndPaint(hwnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:     //处理鼠标左键被按下的操作
		MessageBox(hwnd, TEXT("无效操作。"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
		return 0;
	case WM_DESTROY:         //处理关闭窗口的操作
		PostQuitMessage(0);
		return 0;

	case WM_SETFOCUS:
		SetFocus(hwndList);
		break;

	case WM_COMMAND:     //处理点击按钮的操作
		for (i = 0; i<NUM; i++)
			//如果按钮句柄匹配  就进行相应操作
			if ((HWND)lParam == hwndButton[0])
			{
				pHead = ListInitialise(0, 0, 0, 0);
				break;
			}
			else if ((HWND)lParam == hwndButton[1])
			{
				pINAEX pTemp = pHead;
				int iIndex;
				TCHAR szString;
				while (pTemp)
				{
					iIndex = pTemp->iNumber;
					szString = "1";
					SendMessage(hwndList, LB_ADDSTRING, iIndex - 1, (LPARAM)szString);
					pTemp = pTemp->pNext;
				}
				break;
			}
			else if ((HWND)lParam == hwndButton[2])
				{
				ReadData(pHead);
					break;
				}
			else if ((HWND)lParam == hwndButton[3])
			{
				SaveData(pHead);
				break;
			}
			else if ((HWND)lParam == hwndButton[4])
			{

				break;
			}
			else if ((HWND)lParam == hwndButton[5])
			{
				int iIndex;
				
				DeleteData(pHead,iIndex);
				SendMessage(hwndList, LB_DELETESTRING, iIndex, 0);
				break;
			}
			else if ((HWND)lParam == hwndButton[6])
			{

				break;
			}
		return 0;
	}



	return DefWindowProc(hwnd, message, wParam, lParam);        //DefWindowProc处理我们自定义的消息处理函数没有处理到的消息
}

