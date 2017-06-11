#include<windows.h>
#include"head.h"
#include"resource.h"
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
	static HINSTANCE hInstance;
	static HWND hwndButton[NUM];//按钮子窗体的句柄
	static HFONT hFont;  //定义逻辑字体
	static RECT rect; //矩形结构
	static TCHAR szTop[] = TEXT("         收支条目       收支金额            原因或目的            地点            时间   ");
	static int cxChar, cyChar;//关于字符的大小
	int i;//按钮计数用
	HDC hdc;                //设备环境句柄
	PAINTSTRUCT ps;         //绘制结构

	switch (message)        //处理得到的消息
	{
	case WM_CREATE:          //窗口创建完成时发来的消息
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;

		hFont = CreateFont(//创建逻辑字体
			-14, -7, //高和宽
			0, 0, 400, //一般这个值设为400
			FALSE, //斜体与否
			FALSE,//下划线与否
			FALSE,//删除线与否
			DEFAULT_CHARSET,
			OUT_CHARACTER_PRECIS, 
			CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY,
			FF_DONTCARE, 
			L"微软雅黑"//调用的字体名
		    );
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());
		for (i = 0; i < NUM; i++)
		{
			hwndButton[i] = CreateWindow//创建按钮子窗体
			(
				L"button",//按钮子窗体的类名
				button[i].szText,//按钮子窗体的文本
				WS_CHILD | WS_VISIBLE | button[i].iStyle, //按钮子窗体的类型
				30 + cxChar, 30 + 15 * i + cyChar*(1 + 2 * i),//按钮子窗体的位置
				15 * cxChar, 2.5* cyChar, //按钮子窗体的大小
				hwnd,//父窗体名
				(HMENU)i, //子窗体参数
				((LPCREATESTRUCT)lParam)->hInstance,//案例句柄
				NULL//额外参数
			);
			SendMessage(hwndButton[i], WM_SETFONT, (WPARAM)hFont, 0);
		}
		for (i = 0; i < 5; i++)
		{
			int length[5] = { 15,15,26,15,15 };
			int sum[6];
			sum[0] = 0;
		    hwndList[i] = CreateWindow//创建按钮子窗体
			(
				L"listbox",//列表框子窗体的类名
				NULL,
				WS_CHILD | WS_VISIBLE | LBS_STANDARD,//列表框子窗体的类型
				(25 + sum[i])* cxChar, 3 * cyChar,//列表框子窗体的位置
				(length[i]) * cxChar, 22 * cyChar,//列表框子窗体的大小
				hwnd,//父窗体名
				(HMENU)NUM + i, //子窗体参数
				(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),//案例句柄
				NULL//额外参数
			);
			sum[i+1] = length[i] + sum[i];
			SendMessage(hwndList[i], WM_SETFONT, (WPARAM)hFont, 0);
		}
		return 0;
    
	case WM_SIZE://定义矩形结构体的位置
		rect.left = 15 * cxChar;
		rect.top = 2 * cyChar;
		rect.right = LOWORD(lParam);
		rect.bottom = HIWORD(lParam);
		return 0;
	case WM_PAINT://根据矩形结构体输出字符
		InvalidateRect(hwnd,&rect,TRUE);
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 20 * cxChar, 10+cyChar, szTop, lstrlen(szTop));//输出文字数组开头的坐标，名以及长度
		EndPaint(hwnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:     //处理在其他区域鼠标左键被按下的操作
		MessageBox(hwnd, TEXT("无效操作。"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
		return 0;
	case WM_DESTROY:         //处理关闭窗口的操作
		PostQuitMessage(0);
		DeleteObject(hFont);
		return 0;

	case WM_COMMAND:     //处理点击按钮的操作
		for (i = 0; i<NUM; i++)
			//如果按钮句柄匹配  就进行相应操作
			if ((HWND)lParam == hwndButton[0])
			{
				SendMessage(hwndList[0], LB_RESETCONTENT, 0, 0);
				SendMessage(hwndList[1], LB_RESETCONTENT, 0, 0);
				SendMessage(hwndList[2], LB_RESETCONTENT, 0, 0);
				SendMessage(hwndList[3], LB_RESETCONTENT, 0, 0);
				SendMessage(hwndList[4], LB_RESETCONTENT, 0, 0);
				break;
			}
			else if ((HWND)lParam == hwndButton[1])
			{
				Empty(hwnd);
				break;
			}
			else if ((HWND)lParam == hwndButton[2])
			{
				Empty(hwnd);
				break;
			}
			else if ((HWND)lParam == hwndButton[3])
			{
				DialogBox(hInstance, L"InputBox1", hwnd, Input1DlgProc);
				break;
			}
			else if ((HWND)lParam == hwndButton[4])
			{
				DialogBox(hInstance, L"InputBox2", hwnd, Input2DlgProc);
				break;
			}
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);        //DefWindowProc处理我们自定义的消息处理函数没有处理到的消息
}

BOOL CALLBACK Input1DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static TCHAR szInitial1[] = TEXT("输入示例:12.5/-12.5");
	static TCHAR szInitial2[] = TEXT("输入示例:新食堂");
	static TCHAR szInitial3[] = TEXT("输入示例:午饭");
	static TCHAR szInitial4[] = TEXT("输入示例:2017.10.03");
	static TCHAR szHead[] = TEXT("        条目细则:");
	static TCHAR szMoney[13]= TEXT("");
	static TCHAR szLocation[13] = TEXT("");
	static TCHAR szAim[13] = TEXT("");
	static TCHAR szTime[13] = TEXT("");
	switch (message)
	{
	case WM_INITDIALOG:
		SetWindowText(GetDlgItem(hDlg, 1001), szInitial1);
		SetWindowText(GetDlgItem(hDlg, 1002), szInitial2);
		SetWindowText(GetDlgItem(hDlg, 1003), szInitial3);
		SetWindowText(GetDlgItem(hDlg, 1004), szInitial4);
	return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			GetWindowText(GetDlgItem(hDlg, 1001), szMoney,10);
			GetWindowText(GetDlgItem(hDlg, 1002), szLocation,10);
			GetWindowText(GetDlgItem(hDlg, 1003), szAim,10);
			GetWindowText(GetDlgItem(hDlg, 1004), szTime,10);
			SendMessage(hwndList[0], LB_ADDSTRING, 0, (LPARAM)szHead);
			SendMessage(hwndList[1], LB_ADDSTRING, 0, (LPARAM)szMoney);
			SendMessage(hwndList[2], LB_ADDSTRING, 0, (LPARAM)szLocation);
			SendMessage(hwndList[3], LB_ADDSTRING, 0, (LPARAM)szAim);
			SendMessage(hwndList[4], LB_ADDSTRING, 0, (LPARAM)szTime);
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
BOOL CALLBACK Input2DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int iIndex = 0;
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
            iIndex = GetDlgItemInt(hDlg,1001, NULL, 0);
			SendMessage(hwndList[0], LB_DELETESTRING, iIndex-1, 0);
			SendMessage(hwndList[1], LB_DELETESTRING, iIndex-1, 0);
			SendMessage(hwndList[2], LB_DELETESTRING, iIndex-1, 0);
			SendMessage(hwndList[3], LB_DELETESTRING, iIndex-1, 0);
			SendMessage(hwndList[4], LB_DELETESTRING, iIndex-1, 0);
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}