#include<windows.h>
#include"head.h"
#include"resource.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("MyWindow");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;        //����һ�����������

	/*����Ϊ���������wndclass������*/
	wndclass.style = CS_HREDRAW | CS_VREDRAW;                         //������ʽ
	wndclass.lpszClassName = szAppName;                               //��������
	wndclass.lpszMenuName = NULL;                                     //���ڲ˵�:��
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);    //���ڱ�����ɫ
	wndclass.lpfnWndProc = WndProc;                                   //���ڴ�����
	wndclass.cbWndExtra = 0;                                          //����ʵ����չ:��
	wndclass.cbClsExtra = 0;                                          //��������չ:��
	wndclass.hInstance = hInstance;                                   //����ʵ�����
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);               //������С��ͼ��:ʹ��ȱʡͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);                 //���ڲ��ü�ͷ���
	if (!RegisterClass(&wndclass))
	{    //ע�ᴰ����, ���ע��ʧ�ܵ���������ʾ
		MessageBox(NULL, TEXT("�����ʼ��ʧ��."), TEXT("����!"), MB_OK | MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(           //��������
		szAppName,                 //��������
		TEXT("�ҵļ��˱�"),          //���ڱ���
		WS_OVERLAPPEDWINDOW,       //���ڵķ��
		CW_USEDEFAULT,             //���ڳ�ʼ��ʾλ��x:ʹ��ȱʡֵ
		CW_USEDEFAULT,             //���ڳ�ʼ��ʾλ��y:ʹ��ȱʡֵ
		CW_USEDEFAULT,             //���ڵĿ��:ʹ��ȱʡֵ
		CW_USEDEFAULT,             //���ڵĸ߶�:ʹ��ȱʡֵ
		NULL,                      //������:��
		NULL,                      //�Ӳ˵�:��
		hInstance,                 //�ô���Ӧ�ó����ʵ����� 
		NULL                       //
	);
	ShowWindow(hwnd, iCmdShow);        //��ʾ����
	UpdateWindow(hwnd);                //���´���
	while (GetMessage(&msg, NULL, 0, 0))        //����Ϣ�����л�ȡ��Ϣ
	{
		TranslateMessage(&msg);                 //���������Ϣת��Ϊ�ַ���Ϣ
		DispatchMessage(&msg);                  //�ַ����ص�����(���̺���)
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance;
	static HWND hwndButton[NUM];//��ť�Ӵ���ľ��
	static HFONT hFont;  //�����߼�����
	static RECT rect; //���νṹ
	static TCHAR szTop[] = TEXT("         ��֧��Ŀ       ��֧���            ԭ���Ŀ��            �ص�            ʱ��   ");
	static int cxChar, cyChar;//�����ַ��Ĵ�С
	int i;//��ť������
	HDC hdc;                //�豸�������
	PAINTSTRUCT ps;         //���ƽṹ

	switch (message)        //����õ�����Ϣ
	{
	case WM_CREATE:          //���ڴ������ʱ��������Ϣ
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;

		hFont = CreateFont(//�����߼�����
			-14, -7, //�ߺͿ�
			0, 0, 400, //һ�����ֵ��Ϊ400
			FALSE, //б�����
			FALSE,//�»������
			FALSE,//ɾ�������
			DEFAULT_CHARSET,
			OUT_CHARACTER_PRECIS, 
			CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY,
			FF_DONTCARE, 
			L"΢���ź�"//���õ�������
		    );
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());
		for (i = 0; i < NUM; i++)
		{
			hwndButton[i] = CreateWindow//������ť�Ӵ���
			(
				L"button",//��ť�Ӵ��������
				button[i].szText,//��ť�Ӵ�����ı�
				WS_CHILD | WS_VISIBLE | button[i].iStyle, //��ť�Ӵ��������
				30 + cxChar, 30 + 15 * i + cyChar*(1 + 2 * i),//��ť�Ӵ����λ��
				15 * cxChar, 2.5* cyChar, //��ť�Ӵ���Ĵ�С
				hwnd,//��������
				(HMENU)i, //�Ӵ������
				((LPCREATESTRUCT)lParam)->hInstance,//�������
				NULL//�������
			);
			SendMessage(hwndButton[i], WM_SETFONT, (WPARAM)hFont, 0);
		}
		for (i = 0; i < 5; i++)
		{
			int length[5] = { 15,15,26,15,15 };
			int sum[6];
			sum[0] = 0;
		    hwndList[i] = CreateWindow//������ť�Ӵ���
			(
				L"listbox",//�б���Ӵ��������
				NULL,
				WS_CHILD | WS_VISIBLE | LBS_STANDARD,//�б���Ӵ��������
				(25 + sum[i])* cxChar, 3 * cyChar,//�б���Ӵ����λ��
				(length[i]) * cxChar, 22 * cyChar,//�б���Ӵ���Ĵ�С
				hwnd,//��������
				(HMENU)NUM + i, //�Ӵ������
				(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),//�������
				NULL//�������
			);
			sum[i+1] = length[i] + sum[i];
			SendMessage(hwndList[i], WM_SETFONT, (WPARAM)hFont, 0);
		}
		return 0;
    
	case WM_SIZE://������νṹ���λ��
		rect.left = 15 * cxChar;
		rect.top = 2 * cyChar;
		rect.right = LOWORD(lParam);
		rect.bottom = HIWORD(lParam);
		return 0;
	case WM_PAINT://���ݾ��νṹ������ַ�
		InvalidateRect(hwnd,&rect,TRUE);
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 20 * cxChar, 10+cyChar, szTop, lstrlen(szTop));//����������鿪ͷ�����꣬���Լ�����
		EndPaint(hwnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:     //�������������������������µĲ���
		MessageBox(hwnd, TEXT("��Ч������"), TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
		return 0;
	case WM_DESTROY:         //����رմ��ڵĲ���
		PostQuitMessage(0);
		DeleteObject(hFont);
		return 0;

	case WM_COMMAND:     //��������ť�Ĳ���
		for (i = 0; i<NUM; i++)
			//�����ť���ƥ��  �ͽ�����Ӧ����
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
	return DefWindowProc(hwnd, message, wParam, lParam);        //DefWindowProc���������Զ������Ϣ������û�д�������Ϣ
}

BOOL CALLBACK Input1DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static TCHAR szInitial1[] = TEXT("����ʾ��:12.5/-12.5");
	static TCHAR szInitial2[] = TEXT("����ʾ��:��ʳ��");
	static TCHAR szInitial3[] = TEXT("����ʾ��:�緹");
	static TCHAR szInitial4[] = TEXT("����ʾ��:2017.10.03");
	static TCHAR szHead[] = TEXT("        ��Ŀϸ��:");
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