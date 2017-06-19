#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>
#include<locale.h>
#include<time.h>
#ifndef _HEAD_H_
#define _HEAD_H_
/*�򻯵��ַ�*/
#define pHead TheHeadofAnIncomeAndExpenseList 
#define pCur TheCurrentTerm 
#define pPre ThePreviousTerm  

/*�ṹ�������*/
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

typedef struct USER_AND_PASSWORD//�û���������Ľṹ��
{
	wchar_t wcID[20];
	int iPassWord[4];
	int iSwitch;//����ָʾ�û��Ƿ���Ҫ��������,����0��ʾ����������
}UAPW;
typedef UAPW* pUAPW;//ָ�� �û���������ṹ���ָ��

/*�Ժ���������*/
pINAEX ListInitialise(float, int, int, int);//��һ���ڵ�ĳ�ʼ��
void ListCreation(pINAEX); //�б�ͷ��ʼ��
void StructCreation(pINAEX);//���û�����һ���ڵ����Ϣ
void ListAddtion(pINAEX);//���һ���ڵ�
void ShowList(pINAEX head);//�������������������
void SaveData(pINAEX);//��������
void ReadData(pINAEX);//��ȡ����
void DeleteData(pINAEX);//ɾ��ĳ���ض��ڵĺ���
void ExitApplication(pINAEX);//�˳�����
void SearchData(pINAEX head);//��ѯ����
int Calendar(int, int, int);//�ж������Ƿ����
void SafeInput(wchar_t wcArray[],int );//ȷ��������ַ����ᳬ����������
float SumAll(pINAEX);//���㵱ǰ�����
void NodeSwap(pINAEX, pINAEX);//�����ڵ����ݺ���
void ListSort(pINAEX);//��������
void ShowDailyList(pINAEX);//��ѯ�������ڵ���֧���
void SearchForPeriod(pINAEX pHead);//ͳ��һ������������֧���
void CorrectData(pINAEX pHead);//�޸�������Ŀ
void ReadTime(int[3]);//��ȡ����ʱ��
void ExceedingValue(pINAEX pHead);//��ʾ���г���ĳ����޶ȵļ�¼(�����ƽ�����û��Լ�����)
void SearchOnDemand(pINAEX);//�����������ܵ��Ӳ˵�����
void CreateFile(void);//����һ�������û�����������ļ�����
void Key(int*);//������ܵĺ���
wchar_t* Identify(void);//��֤�û���ݵĺ���
void ChangeIDandPW(void);//�޸��û���������ĺ���
#endif // _HEAD_H_
