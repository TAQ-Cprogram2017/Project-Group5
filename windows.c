#include<windows.h>
#include"head.h"
#include"function.h"
pINAEX pHead;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);        //��������������Ϣ�ĺ���
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
	static HWND hwndButton[NUM];//��ť�Ӵ���ľ��
	static RECT rect; //���νṹ
	static HWND hwndList;
	static TCHAR szTop[] = TEXT("         ��Ŀ���       ��֧���            ԭ���Ŀ��           �ص�            ʱ��   "),
		         szFormat[] = TEXT("%-16s%04W-%04X %04X-%04X"),
		         szBuffer[50];
	static int cxChar, cyChar;
	int i;
	HDC hdc;                //�豸�������
	PAINTSTRUCT ps;         //���ƽṹ
	switch (message)        //����õ�����Ϣ
	{
	case WM_CREATE:          //���ڴ������ʱ��������Ϣ
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());
		for(i=0;i<NUM;i++)
			hwndButton[i]=CreateWindow//������ť�Ӵ���
			(
			TEXT("button"),//��ť�Ӵ��������
			button[i].szText,//��ť�Ӵ�����ı�
			WS_CHILD | WS_VISIBLE | button[i].iStyle, //��ť�Ӵ��������
			30+cxChar, 30+15*i+cyChar*(1 + 2 * i),//��ť�Ӵ����λ��
			15 * cxChar, 2.5* cyChar , //��ť�Ӵ���Ĵ�С
			hwnd,//��������
			(HMENU)i, //�Ӵ������
			((LPCREATESTRUCT)lParam)->hInstance,//�������
			NULL//�������
			);
		hwndList = CreateWindow(//�����б���Ӵ���
			TEXT("listbox"),// �б���Ӵ��������
			NULL,
			WS_CHILD | WS_VISIBLE | LBS_STANDARD,//�б���Ӵ��������
			200 + cxChar, 3 * cyChar,//�б���Ӵ����λ��
			85 * cxChar, 22 * cyChar,//�б���Ӵ���Ĵ�С
			hwnd,//��������
			(HMENU)NUM + 1,//�Ӵ������
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),//�������
			NULL);//�������
		pHead = ListInitialise(0, 0, 0, 0);
		ReadData(pHead);
		MessageBox(hwnd, TEXT("��ӭʹ�ü��˱���"), TEXT("��ʼ���ɹ�"), MB_OK | MB_ICONINFORMATION);
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
		TextOut(hdc, 20 * cxChar, 10+cyChar, szTop, lstrlen(szTop));//����������鿪ͷ�����꣬���Լ�����
		EndPaint(hwnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:     //���������������µĲ���
		MessageBox(hwnd, TEXT("��Ч������"), TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
		return 0;
	case WM_DESTROY:         //����رմ��ڵĲ���
		PostQuitMessage(0);
		return 0;

	case WM_SETFOCUS:
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



	return DefWindowProc(hwnd, message, wParam, lParam);        //DefWindowProc���������Զ������Ϣ������û�д�������Ϣ
}

