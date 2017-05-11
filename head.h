#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>
#include<locale.h>
#include<windows.h>
#ifndef _HEAD_H_
#define _HEAD_H_
/*��ť������*/
#define NUM (sizeof (button)/sizeof (button[0]))
struct
{
	int iStyle;
	TCHAR * szText;
}
button[] =
{
	BS_PUSHBUTTON,           TEXT("���³�ʼ��"),
	BS_PUSHBUTTON,           TEXT("��ʾȫ����¼"),
	BS_PUSHBUTTON,           TEXT("���¶�ȡ��¼"),
	BS_PUSHBUTTON,           TEXT("���浱ǰ��¼"),
	BS_PUSHBUTTON,           TEXT("����һ���¼"),
	BS_PUSHBUTTON,           TEXT("ɾ��ָ����¼"),
	BS_PUSHBUTTON,           TEXT("��ѯ��ʷ����")
};

/*���ݴ洢�ṹ�������*/
typedef struct _INCOME_AND_EXPENSE
{
	int iNumber;//���ڼ�¼���ǵڼ�����¼������֮��Ĳ���
	float fValue;//��֧����
	wchar_t szLocation[20];//���ѳ���
	wchar_t szKind[20];//��������
	int iYearDate;//��
	int iMonthDate;//��
	int iDayDate;//��
	struct _INCOME_AND_EXPENSE * pNext;//�������һ��Ԫ��
}INAEX;//�򻯽ṹ����
typedef INAEX * pINAEX;//����һ��INAEX���͵�ָ��

/*�Ժ���������*/
pINAEX ListInitialise(float, int, int, int);//��һ���ڵ�ĳ�ʼ��
void StructCreation(pINAEX);//���û�����һ���ڵ����Ϣ
void ListAddtion(pINAEX);//���һ���ڵ�
void SaveData(pINAEX);//��������
void ReadData(pINAEX);//��ȡ����
void DeleteData(pINAEX,int);//ɾ��ĳ���ض��ڵĺ���
void ExitApplication(pINAEX);//�˳�����
int Calendar(int, int, int);//�ж������Ƿ����
void SafeInput(wchar_t wcArray[], int);//ȷ��������ַ����ᳬ����������

#endif // _HEAD_H_