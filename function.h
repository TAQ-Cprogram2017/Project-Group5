#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>
#include<locale.h>
#include<windows.h>
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

pINAEX ListInitialise(float Value, int BeginYear, int BeginMonth, int BeginDay)//����һ����ValueΪ��ʼ������ų�ʼʱ�����֧����
{
	pINAEX pIncomeAndExpenseList;
	pIncomeAndExpenseList = (pINAEX)malloc(sizeof(INAEX));//��һЩ�ռ�
	if (!pIncomeAndExpenseList)
	{
		printf("��ȡ�ռ�ʧ��!\n");
		return NULL;
	}
	/*��ʼ����ͷ*/
	pIncomeAndExpenseList->iNumber = 1;
	pIncomeAndExpenseList->fValue = Value;
	wcscpy(pIncomeAndExpenseList->szLocation, L"��ʼ�ص�");
	wcscpy(pIncomeAndExpenseList->szKind, L"��ʼ����");
	pIncomeAndExpenseList->iYearDate = BeginYear;
	pIncomeAndExpenseList->iMonthDate = BeginMonth;
	pIncomeAndExpenseList->iDayDate = BeginDay;
	pIncomeAndExpenseList->pNext = NULL;//
	return pIncomeAndExpenseList;
}

void StructCreation(pINAEX pHead)//��Ҫ�󴴽�һ����֧�ṹ��ĺ���,
{
	float fValue;
	int iYear;
	int iMonth;
	int iDay;
	wchar_t wcLocation[20];
	wchar_t wcKind[20];
	printf("�����뱾�ε���֧���.\n");
	scanf("%f", &fValue);
	printf("�����뱾����֧�������.\n");
	scanf("%d", &iYear);

	for (;;)//�ж��·��Ƿ����
	{
		printf("�����뱾����֧�����·�.\n");
		scanf("%d", &iMonth);
		if (iMonth<1 || iMonth>12)
			printf("������·���Ч������������\n");
		else break;
	}

	for (;;)//�ж������Ƿ����
	{
		printf("�����뱾����֧��������.\n");
		scanf("%d", &iDay);
		if (Calendar(iYear, iMonth, iDay))
		{
			printf("�����������Ч������������\n");
		}
		else break;
	}
	pHead->fValue = fValue;
	pHead->iDayDate = iDay;
	pHead->iMonthDate = iMonth;
	pHead->iYearDate = iYear;

	printf("�����뱾����֧���ڵص�.(19������)\n");
	SafeInput(wcLocation, 20);
	wcscpy(pHead->szLocation, wcLocation);

	printf("�����뱾����֧����.(19������)\n");
	SafeInput(wcKind, 20);
	wcscpy(pHead->szKind, wcKind);
	printf("��Ŀ�����ɹ�.����������һ�����.\n");
}

void ListAddtion(pINAEX pHead)//���������е���һ��
{
	pINAEX pTheNext = ListInitialise(0, 0, 0, 0);
	StructCreation(pTheNext);
	pINAEX pTemp = pHead;
	while (pTemp->pNext)//�������ͷ�Ƶ����һ�������ݵĽڵ�
		pTemp = pTemp->pNext;
	pTemp->pNext = pTheNext;//�����һ�������ݵĽڵ��ָ��ָ���´����Ľڵ�
	pTheNext->iNumber = pTemp->iNumber + 1;
}


void SaveData(pINAEX pHead)
{
	FILE *fp;
	if ((fp = fopen("D:/data.txt", "wb+")) == NULL)//������д��ķ�ʽ��һ����Ϊdata.txt�Ķ����Ƶ��ļ�
	{
		printf("�޷����ļ�!\n");
		return;
	}
	pINAEX pTemp;
	pTemp = pHead;
	do
	{
		fwrite(pTemp, sizeof(INAEX), 1, fp);//����������
		pTemp = pTemp->pNext;
	} while (pTemp != NULL);//����������������ݴ����ļ���
	fclose(fp);
}

void ReadData(pINAEX pHead)
{
	FILE *fp;
	if ((fp = fopen("D:/data.txt", "rb")) == NULL)//�ö�ȡ�ķ�ʽ��һ����Ϊdata.txt�Ķ����Ƶ��ļ�
	{
		printf("�޷����ļ�,���Ѿ����´����ļ�!\n");
		fp = fopen("D:/data.txt", "wb+");
		SaveData(pHead);
		return;
	}
	rewind(fp);//��֤���������д��ļ���ͷ��������
	pINAEX pPre, pCur;//��������ָ�룬��֮��Ķ�ȡ�����л�ʹ�õ�
	fread(pHead, sizeof(INAEX), 1, fp);//���ļ��п������ͷ����
	pPre = pHead;
	if (pHead->pNext != NULL)
	{
		pHead->pNext = pPre;
	}
	else
		pHead->pNext = NULL;
	while (pPre->pNext != NULL)
	{
		pCur = (pINAEX)malloc(sizeof(INAEX));//Ϊ�µĽڵ㿪��һ���µĿռ�
		pPre->pNext = pCur;//ʹ��֮ǰ�Ľڵ��е�ָ��ָ���µĽڵ�
		fread(pCur, sizeof(INAEX), 1, fp);//���ļ��п������ͷ����
		pPre = pCur;//��cur������pre��
	}
	fclose(fp);
}

void DeleteData(pINAEX pHead,int iIndex)//ɾ��ָ���ڵ���Ŀ�ĺ���
{
	int iNum = iIndex;
	pINAEX pPre = pHead;
	if (iNum == 1)
	{
		printf("�޷�ɾ����һ����ʼ����\n");
		return;
	}
	pINAEX pTemp = pHead;
	while (pTemp->iNumber != iNum)//�������ͷ�Ƶ���Ҫɾ���Ľڵ�
	{
		if ((pTemp->pNext == NULL))//����Ѿ�����ĩβ���ͻص�������
		{
			printf("û���ҵ�������Ŀ!\n");
			return;
		}
		pPre = pTemp;
		pTemp = pTemp->pNext;
		if ((pTemp->pNext == NULL) && (pTemp->iNumber == iNum))//�����Ҫɾ���ľ������һ���ִ��if��������ݣ������ء�
		{
			pPre->pNext = NULL;
			free(pTemp);
			return;
		}
	}
	pPre->pNext = pTemp->pNext;//���ӱ�ɾ���ڵ�ǰ��������ڵ�
	free(pTemp);//�ͷ���Ҫɾ���Ľڵ�
	pTemp = pPre->pNext;
	do//���ı�ɾ���ڵ�֮��ÿ���ڵ�����
	{
		pPre = pTemp;
		pTemp->iNumber--;
		pTemp = pTemp->pNext;
	} while (pPre->pNext != NULL);
}

int Calendar(int iYear, int iMonth, int iDay)//�ж����������Ƿ���ڵĺ���,����ֵΪ1��ʾ������
{
	if (iDay < 1 || iDay>31)//�ų������ڵ�����
		return 1;

	if (iMonth == 2)//�ж϶�������
		if (iYear % 4 == 0 && iYear % 400 != 0)//������
		{
			if (iDay > 29)
				return 1;
			else return 0;
		}
		else//��������
		{
			if (iDay > 28)
				return 1;
			else return 0;
		}
	if (iDay == 31)//���ִ�С��
	{
		if (iMonth == 4 || iMonth == 6 || iMonth == 9 || iMonth == 11)
			return 1;
		else return 0;
	};
	if (iDay <= 30)
		return 0;
}

void SafeInput(wchar_t wcArray[], int iLimit)//���������ַ��Ƿ񳬳�������������1������
{
	int iNum = iLimit * 2 - 1;//�����ַ�������ת��ΪӢ���ַ��ĳ��ȣ�Ԥ��һ���ֽڴ�����ַ�
	wchar_t c = 0;//������ջ�����
	for (;;)
	{
		wscanf(L"%ls", wcArray);
		if ((strlen(wcArray)) > iNum)//�Ƚ����鳤��������
		{
			printf("*************************\n");
			printf("�����������ޣ�����������\n");
			printf("*************************\n");
			while (c = getwchar() != L'\n'&&c != EOF);//��ջ�����
		}
		else
			break;
	}

}


#endif // _FUNCTION_H_

