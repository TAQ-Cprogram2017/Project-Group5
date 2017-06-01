#include<windows.h>
#include"head.h"
#include"function.h"
#include"resource.h"
pINAEX pHead;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);        //��������������Ϣ�ĺ���
BOOL CALLBACK Input1DlgProc(HWND, UINT, WPARAM, LPARAM);      //�������������½��ṹ��ĺ���
BOOL CALLBACK Input2DlgProc(HWND, UINT, WPARAM, LPARAM);      //������������ɾ��ָ����Ŀ�ĺ���
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
	static TCHAR szTop[] = TEXT("         ��Ŀ���       ��֧���            ԭ���Ŀ��           �ص�            ʱ��   ");
	static HWND hwndList;//�б����
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
		hwndList = CreateWindow(//�����б���Ӵ���
			L"listbox",// �б���Ӵ��������
			NULL,
			WS_CHILD | WS_VISIBLE | LBS_STANDARD,//�б���Ӵ��������
			200 + cxChar, 3 * cyChar,//�б���Ӵ����λ��
			85 * cxChar, 22 * cyChar,//�б���Ӵ���Ĵ�С
			hwnd,//��������
			(HMENU)NUM + 1,//�Ӵ������
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),//�������
			NULL);//�������
		SendMessage(hwndList, WM_SETFONT, (WPARAM)hFont, 0);
		pHead = ListInitialise(0, 0, 0, 0);
		ReadData(pHead);
		MessageBox(hwnd, TEXT("��ӭʹ�ü��˱���"), TEXT("��ʼ���ɹ�"), MB_OK | MB_ICONINFORMATION);
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

	case WM_SETFOCUS://��������
		SetFocus(hwndList);
		break;

	case WM_COMMAND:     //��������ť�Ĳ���
		for (i = 0; i<NUM; i++)
			//�����ť���ƥ��  �ͽ�����Ӧ����
			if ((HWND)lParam == hwndButton[0])
			{
				pHead = ListInitialise(0, 0, 0, 0);
				break;
			}
			else if ((HWND)lParam == hwndButton[1])
			{
				MessageBox(hwnd, TEXT("��������δ����"), TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
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
				DialogBox(hInstance, L"InputBox1", hwnd, Input1DlgProc);
				break;
			}
			else if ((HWND)lParam == hwndButton[5])
			{
				DialogBox(hInstance, L"InputBox2", hwnd, Input2DlgProc);
				break;
			}
			else if ((HWND)lParam == hwndButton[6])
			{
				MessageBox(hwnd, TEXT("��������δ����"), TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
				break;
			}
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);        //DefWindowProc���������Զ������Ϣ������û�д�������Ϣ
}

BOOL CALLBACK Input1DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
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
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}