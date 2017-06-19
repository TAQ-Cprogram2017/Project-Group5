#include"head.h"
#include<stdio.h>
#define NUMBER_OF_SUBMENU 5//�Ӳ˵���������
void ListCreation(pINAEX pHead)//��Ҫ�󴴽�һ����Ϊĳ������ͷ�Ľṹ��ĺ���
{
	float fValue;
	int iTime[3];//���鴢�������������������
	int iSubCommand;
	printf("******************************************\n");
	printf("�˳����β����밴ESC���������밴����� \n");
	printf("******************************************\n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	};

	printf("�������ʼ���.\n");
	scanf_s("%f", &fValue);

	ReadTime(iTime);

	pHead->fValue = fValue;
	pHead->iYearDate = iTime[0];
	pHead->iMonthDate = iTime[1];
	pHead->iDayDate = iTime[2];
	pHead->pNext = NULL;
	if (!pHead)
		return;
	system("cls");
	printf("��Ŀ�����ɹ�.\n");
}

pINAEX ListInitialise(float Value,int BeginYear,int BeginMonth, int BeginDay)//����һ����ValueΪ��ʼ������ų�ʼʱ�����֧����
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
	wcscpy(pIncomeAndExpenseList->szLocation,L"��ʼ�ص�");
	wcscpy(pIncomeAndExpenseList->szKind,L"��ʼ����");
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
	int iTime[3];//�洢������
	int iJudge;//�ж��Ƿ�ֱ�������ȡ��ʱ��
	wchar_t wcLocation[20];
	wchar_t wcKind[20];

	printf("�����뱾�ε���֧���.��������ʾ���룬������ʾ�����\n");
	scanf("%f", &fValue);
	ReadTime(iTime);
	iYear = iTime[0];
	iMonth = iTime[1];
	iDay = iTime[2];
	printf("�����뱾����֧�������.\n����ǰ���%d����0���룩\n", iYear);
	scanf("%d", &iJudge);
	if (iJudge == 0);
	else iYear = iJudge;

	for (;;)//�ж��·��Ƿ����
	{
		printf("�����뱾����֧�����·�.\n����ǰ�·�%d,��0���룩\n", iMonth);
		scanf("%d", &iJudge);
		if (iJudge == 0);
		else iMonth = iJudge;
		if (iMonth<1 || iMonth>12)
			printf("������·���Ч������������\n");
		else break;
	}

	for (;;)//�ж������Ƿ����
	{
		printf("�����뱾����֧��������.\n����ǰ����%d,��0���룩\n", iDay);
		scanf("%d", &iJudge);
		if (iJudge == 0);
		else iDay = iJudge;
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
	system("cls");
	printf("��Ŀ�����ɹ�.����������һ�����.\n");
}

void ListAddtion(pINAEX pHead)//���������е���һ��
{
	int iSubCommand;
	printf("�˳����β����밴ESC���������밴����� \n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	};
	pINAEX pTheNext= ListInitialise(0, 0, 0, 0);
	StructCreation(pTheNext);
	pINAEX pTemp = pHead;
	while (pTemp->pNext)//�������ͷ�Ƶ����һ�������ݵĽڵ�
		pTemp = pTemp->pNext;
	pTemp->pNext = pTheNext;//�����һ�������ݵĽڵ��ָ��ָ���´����Ľڵ�
	pTheNext->iNumber = pTemp->iNumber + 1;
}

void ShowList(pINAEX pHead)
{
	ListSort(pHead);//sort list in time order
	pINAEX pTemp = pHead;
	printf("***********************************************************************\n");
	while (pTemp)
	{
		if (pTemp->fValue<0)
			wprintf(L"��%d��:֧��%.2fԪ ʱ��%d.%d.%d �ص�:%ls ����:%ls\n", pTemp->iNumber, -(pTemp->fValue), pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate, pTemp->szLocation, pTemp->szKind);
		else
			wprintf(L"��%d��:����%.2fԪ ʱ��%d.%d.%d �ص�:%ls ����:%ls\n", pTemp->iNumber, pTemp->fValue, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate, pTemp->szLocation, pTemp->szKind);
		pTemp = pTemp->pNext;
	}
	printf("***********************************************************************\n");
}

void SaveData(pINAEX pHead)
{
	FILE *fp;
	if((fp = fopen("D:/data.txt", "wb+"))==NULL)//������д��ķ�ʽ��һ����Ϊdata.txt�Ķ����Ƶ��ļ�
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
	int iSubCommand;
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

void DeleteData(pINAEX pHead)//ɾ��ָ���ڵ���Ŀ�ĺ���
{
	int iNum;//��Ϊ������
	pINAEX pPre = pHead;
	ShowList(pHead);

	printf("��������Ҫɾ������Ŀ����ţ�����0������������\t");
	scanf("%d", &iNum);

	if (iNum == 0)
		return;
	if (iNum == 1)
	{
		system("cls");
		printf("�޷�ɾ����һ����ʼ����\n");
		return;
	}
	pINAEX pTemp = pHead;
	while (pTemp->iNumber != iNum)//�������ͷ�Ƶ���Ҫɾ���Ľڵ�
	{
		if ((pTemp->pNext == NULL))//����Ѿ�����ĩβ���ͻص�������
		{
			system("cls");
			printf("û���ҵ�������Ŀ!\n");
			return;
		}
		pPre = pTemp;
		pTemp = pTemp->pNext;
		if ((pTemp->pNext == NULL) && (pTemp->iNumber == iNum))//�����Ҫɾ���ľ������һ���ִ��if��������ݣ������ء�
		{
			pPre->pNext = NULL;
			free(pTemp);
			system("cls");
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

void SearchData(pINAEX pHead)//����ĳ��ĳ��ĳ��������֧��Ϣ�ĺ���
{
	pINAEX pTemp;
	int iYear;
	int iMonth;
	int iDay;
	int iJudgement, iSubCommand;
	iJudgement = 0;// �����ж��Ƿ�һ����¼��û�в鵽�ı�־

	printf("******************************************\n");
	printf("�˳����β����밴ESC���������밴����� \n");
	printf("******************************************\n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	};

	printf("���������������֧�������.\n");
	scanf("%d", &iYear);
	for (;;)
	{
		printf("���������������֧�����·�.\n");
		scanf("%d", &iMonth);
		if (iMonth<1 || iMonth>12)
			printf("�����·���Ч,����������\n");
		else break;
	}
	for (;;)
	{
		printf("���������������֧��������.\n");
		scanf("%d", &iDay);
		if (Calendar(iYear, iMonth, iDay) == 1)
		{
			system("cls");
			printf("����������Ч,����������\n");
		}
		else
			break;
	}

	pTemp = pHead;
	printf("������ĿΪ:\n");
	do
	{
		if (pTemp->iYearDate == iYear && pTemp->iMonthDate == iMonth && pTemp->iDayDate == iDay)
		{
			wprintf(L"��%d����֧:%.2f �ص�:%ls ����:%ls ʱ��%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			iJudgement = 1;// ����鵽�˼�¼���Ͱѱ���judgement������ֵΪ1
		}
		pTemp = pTemp->pNext;
	} while (pTemp != NULL);
	if (iJudgement == 0)
		printf("û���ҵ���һ��ļ�¼.\n");
}

int Calendar(int iYear, int iMonth, int iDay)//�ж����������Ƿ���ڵĺ���,����ֵΪ1��ʾ������
{
	if (iMonth < 1 || iMonth>12)
		return 1;

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
	return 1;
}

void SafeInput(wchar_t wcArray[],int iLimit)//���������ַ��Ƿ񳬳�������������1������
{
	int iNum = iLimit  * 2-1;//�����ַ�������ת��ΪӢ���ַ��ĳ��ȣ�Ԥ��һ���ֽڴ�����ַ�
	wchar_t c = 0;//������ջ�����
	for (;;)
	{
		wscanf(L"%ls", wcArray);
		if ((strlen(wcArray)) > iNum)//�Ƚ����鳤��������
		{
			printf("*************************\n");
			printf("�����������ޣ�����������!\n");
			printf("*************************\n");
			while (c = getwchar() != L'\n'&&c != EOF);//��ջ�����
		}
		else
			break;
	} 

}

float SumAll(pINAEX pHead)//���㵱ǰ�������
{
	float fSum=0;
	pINAEX pTemp;
	pTemp = pHead;
	while(pTemp!=NULL)
	{
		fSum = fSum + pTemp->fValue;
		pTemp = pTemp->pNext;
	}
	return fSum;
}

void NodeSwap(pINAEX a, pINAEX b)//�ڽ���Ԫ��ʱ����iNumber
{
	pINAEX c = (pINAEX)malloc(sizeof(INAEX));
	if (!c)
	{
		printf("��ȡ�ռ�ʧ��!\n");
		return;
	}
	c-> fValue=a->fValue;
	strcpy(c->szLocation, a->szLocation);
	strcpy(c->szKind, a->szKind);
	c-> iYearDate=a->iYearDate;
	c-> iMonthDate=a->iMonthDate;
	c-> iDayDate=a->iDayDate;

	a->fValue = b->fValue;
	strcpy(a->szLocation,b->szLocation);
	strcpy(a->szKind, b->szKind);
	a->iYearDate = b->iYearDate;
	a->iMonthDate = b->iMonthDate;
	a->iDayDate = b->iDayDate;
	
	b->fValue = c->fValue;
	strcpy(b->szLocation, c->szLocation);
	strcpy(b->szKind, c->szKind);
	b->iYearDate = c->iYearDate;
	b->iMonthDate = c->iMonthDate;
	b->iDayDate = c->iDayDate;
	free(c);
}

void ListSort(pINAEX pHead)//ʱ��˳������Ա����� 
{
	pINAEX pTemp = pHead;
	while (pTemp->pNext) pTemp = pTemp->pNext;
	int num = pTemp->iNumber;
	while (--num)//ð������
	{
		pTemp = pHead;
		for (int i = 0; i < num; i++)
		{
			if ((pTemp->iYearDate>pTemp->pNext->iYearDate) || (pTemp->iYearDate == pTemp->pNext->iYearDate&&pTemp->iMonthDate > pTemp->pNext->iMonthDate) || (pTemp->iYearDate == pTemp->pNext->iYearDate&&pTemp->iMonthDate == pTemp->pNext->iMonthDate&&pTemp->iDayDate > pTemp->pNext->iDayDate))
			{
				NodeSwap(pTemp, pTemp->pNext);
			}
			pTemp = pTemp->pNext;
		}
	}
}

void ShowDailyList(pINAEX pHead)//��ѯ�������ڵ���֧���
{
	ListSort(pHead);//sort list in time order
	int year, month, day,curyear,curmonth,curday, iSubCommand;
	float total;

	printf("******************************************\n");
	printf("�˳����β����밴ESC���������밴����� \n");
	printf("******************************************\n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	};

	pINAEX pTemp = pHead;
	while (pTemp)
	{
		total = 0;
		curyear = pTemp->iYearDate;
		curmonth = pTemp->iMonthDate;
		curday = pTemp->iDayDate;
		do
		{
			if ((pTemp->iYearDate ==curyear) && (pTemp->iMonthDate == curmonth) && (pTemp->iDayDate == curday))
			{
				
				total = total + pTemp->fValue;
				pTemp = pTemp->pNext;
			}
			else
			{
				if(total>0)
					printf("%d��%d��%d��������%.2f\n", curyear, curmonth, curday, total);
				else
					printf("%d��%d��%d��֧����%.2f\n", curyear, curmonth, curday, -total);
				break;
			}
		} while (pTemp);
		
	}
	if (total>0)                                          //�������һ��ļ�¼
		printf("%d��%d��%d��������%.2f\n", curyear, curmonth, curday, total);
	else
		printf("%d��%d��%d��֧����%.2f\n", curyear, curmonth, curday, -total);
}

void SearchForPeriod(pINAEX pHead)
{
	int Y1, Y2, M1, M2, D1, D2;
	int iJudgement = 0, iSubCommand;
	float fSum = 0;

	printf("******************************************\n");
	printf("�˳����β����밴ESC���������밴����� \n");
	printf("******************************************\n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	};

	pINAEX pTemp;
	pTemp = pHead;
	printf("******************************************\n");
	while (1)
	{
		printf("����������ʱ�����֧�������ʼ���.\n");
		scanf("%d", &Y1);
		printf("����������ʱ�����֧�������ʼ�·�.\n");
		scanf("%d", &M1);
		printf("����������ʱ�����֧�������ʼ����.\n");
		scanf("%d", &D1);
		if(Calendar(Y1,M1,D1)==1)
		{
			printf("�������������Ч\n");
		}
		else break;
	}
	printf("******************************************\n");
	while (1)
	{
		printf("����������ʱ�����֧�������ֹ���.\n");
		scanf("%d", &Y2);
		printf("����������ʱ�����֧�������ֹ�·�.\n");
		scanf("%d", &M2);
		printf("����������ʱ�����֧�������ֹ����.\n");
		scanf("%d", &D2);
		if (Calendar(Y2, M2, D2) == 1)
		{
			printf("�������������Ч\n");
		}
		else
			break;
	}
	printf("******************************************\n");
	system("cls");
	printf("������ĿΪ%d.%d.%d��%d.%d.%d֮�����֧��¼:", Y1, M1, D1, Y2, M2, D2);
	while (pTemp != NULL)
	{
		if (pTemp->iYearDate > Y1 && pTemp->iYearDate < Y2)
		{
			fSum = fSum + pTemp->fValue;
			wprintf(L"��%d����֧:%.2f �ص�:%ls ����:%ls ʱ��%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			iJudgement = iJudgement + 1;
			pTemp = pTemp->pNext;
			continue;
		}
		else if (pTemp->iYearDate == Y1 && pTemp->iMonthDate > M1)
		{
			fSum = fSum + pTemp->fValue;
			wprintf(L"��%d����֧:%.2f �ص�:%ls ����:%ls ʱ��%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			iJudgement = iJudgement + 1;
			pTemp = pTemp->pNext;
			continue;
		}
		else if ((pTemp->iYearDate == Y1 && pTemp->iMonthDate == M1) && pTemp->iDayDate >= D1)
		{
			fSum = fSum + pTemp->fValue;
			wprintf(L"��%d����֧:%.2f �ص�:%ls ����:%ls ʱ��%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			iJudgement = iJudgement + 1;
			pTemp = pTemp->pNext;
			continue;
		}
		else if ((pTemp->iYearDate == Y2) && (pTemp->iMonthDate < M2))
		{
			fSum = fSum + pTemp->fValue;
			wprintf(L"��%d����֧:%.2f �ص�:%ls ����:%ls ʱ��%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			iJudgement = iJudgement + 1;
			pTemp = pTemp->pNext;
			continue;
		}

		else if ((pTemp->iYearDate == Y2 && pTemp->iMonthDate == M2) && pTemp->iDayDate <= D2)
		{
			fSum = fSum + pTemp->fValue;
			wprintf(L"��%d����֧:%.2f �ص�:%ls ����:%ls ʱ��%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			iJudgement = iJudgement + 1;
			pTemp = pTemp->pNext;
			continue;
		}
		else  pTemp = pTemp->pNext;
	}
	printf("******************************************\n");
	if (iJudgement == 0)
		printf("��ʱ�����û�����κμ�¼\n");
	else
	{

		if (fSum>0)
			printf("���ʱ��������%.2f\n", fSum);
		else
			printf("���ʱ��֧����%.2f\n",  -fSum);
	}
	printf("******************************************\n");
}
void CorrectData(pINAEX pHead)//����ĳһ��¼
{
	ShowList(pHead);

	int iNum, iJudgement, iSubCommand;
	iJudgement = 0;
	pINAEX pTemp;

	printf("******************************************\n");
	printf("�˳����β����밴ESC���������밴����� \n");
	printf("******************************************\n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	}
	else
		printf("\n");

	printf("��������Ҫ�޸ĵ���Ŀ�����:\t");
	scanf("%d", &iNum);
	pTemp = pHead;
	while (pTemp != NULL)
	{

		if (pTemp->iNumber != iNum)
			pTemp = pTemp->pNext;
		else
		{
			iJudgement = 1;
			printf("������ĿΪ:\n");
			printf("***************************************************************************\n");
			wprintf(L"��%d����֧:%.2f �ص�:%ls ����:%ls ʱ��%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			printf("��������ȷ�Ľ��\n");
			scanf("%f", &pTemp->fValue);
			printf("***************************************************************************\n");
			wprintf(L"��%d����֧:%.2f �ص�:%ls ����:%ls ʱ��%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			printf("��������ȷ�ĵص�\n");
			SafeInput(pTemp->szLocation, 20);
			printf("***************************************************************************\n");
			wprintf(L"��%d����֧:%.2f �ص�:%ls ����:%ls ʱ��%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			printf("��������ȷ������\n");
			SafeInput(pTemp->szKind, 20);
			printf("***************************************************************************\n");
			wprintf(L"��%d����֧:%.2f �ص�:%ls ����:%ls ʱ��%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			printf("��������ȷ�� ��\n");
			scanf("%d", &pTemp->iYearDate);
			printf("***************************************************************************\n");
			wprintf(L"��%d����֧:%.2f �ص�:%ls ����:%ls ʱ��%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			printf("��������ȷ�� ��\n");
			scanf("%d", &pTemp->iMonthDate);
			printf("***************************************************************************\n");
			wprintf(L"��%d����֧:%.2f �ص�:%ls ����:%ls ʱ��%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			printf("��������ȷ�� ��\n");
			scanf("%d", &pTemp->iDayDate);
			break;
			ListSort(pHead);
		}
	}
	system("cls");
	if (iJudgement == 0)
		printf("û���ҵ�������Ŀ\n");
	ShowList(pHead);
}

void ExceedingValue(pINAEX pHead)//��ʾ���г���ĳ����޶ȵļ�¼(�����ƽ�����û��Լ�����)
{
	int iJudgement = 0, iSubCommand;
	float fLimit, fExceeding;

	printf("******************************************\n");
	printf("�˳����β����밴ESC���������밴����� \n");
	printf("******************************************\n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	};

	pINAEX pTemp;
	pTemp = pHead;
	printf("�������������ƵĶ��\n");
	scanf("%f", &fLimit);
	printf("������ĿΪ:\n");
	printf("********************************************************************\n");
	while (pTemp != NULL)
	{
		if (- pTemp->fValue >= fLimit)
		{
			fExceeding = -fLimit-pTemp->fValue;
			wprintf(L"��%d����֧���:%.2f �ص�:%ls ����:%ls ʱ��%d.%d.%d,�����Ľ��Ϊ%.2f\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate, fExceeding);
			iJudgement = iJudgement + 1;
			pTemp = pTemp->pNext;
		}
		else pTemp = pTemp->pNext;
	}
	if (iJudgement == 0)
		printf("��ǰû�г����޶ȵļ�¼\n");
	printf("********************************************************************\n");
}

void ReadTime(int iTime[3])//��ȡ����ʱ�䣬�������δ洢������
{
	time_t rawtime;
	struct tm*timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	iTime[0] = timeinfo->tm_year + 1900;
	iTime[1] = timeinfo->tm_mon + 1;
	iTime[2] = timeinfo->tm_mday;
}

void SearchOnDemand(pINAEX pHead)
{
	int iSubCommand, iJudgement;
	void(*SubMenu[NUMBER_OF_SUBMENU])(pINAEX);
	SubMenu[0] = ShowList;
	SubMenu[1] = SearchData;
	SubMenu[2] = SearchForPeriod;
	SubMenu[3] = ShowDailyList;
	SubMenu[4] = ExceedingValue;
	for (;;)//��ʼһ��ѭ��
	{
		printf("*******************************\n");
		printf("��ǰ���Ϊ��  %10.2f\n", SumAll(pHead));//����ǰ�������ʾ�ڵ�ǰ�Ľ�����
		printf("*******************************\n");
		printf("�������˵��밴                0\n");
		printf("��ʾ��ǰȫ����¼�밴          1\n");
		printf("��ѯ�������ڵ���֧���        2\n");
		printf("ͳ��ĳʱ��ε���֧���������  3\n");
		printf("��ѯÿ�յ���֧���������      4\n");
		printf("��ѯ����ĳһ�޶ȵ����м�¼    5\n");
		printf("*******************************\n");
		printf("��������Ҫ���еĲ���:\t");
		scanf("%d", &iSubCommand);
		if (iSubCommand<0 || iSubCommand>NUMBER_OF_SUBMENU)
		{
			system("cls");
			setbuf(stdin, NULL);
			printf("�����˲��Ϸ��Ĳ���!����������:\t\n");
			continue;
		}
		else
		{
				switch (iSubCommand)
				{
				case 0:
					system("cls");
					return;
				default:
					system("cls");
					SubMenu[iSubCommand - 1](pHead);
					SaveData(pHead);
					break;
				}
		}
	}
}

void Key(int* b)//������ܵĺ���
{
	int a[4];
	int temp;
	const int iEncrypt[4][4] = { { 7,3,8,7 },{ 9,3,3,9 },{ 7,7,13,7 },{ 9,2,2,9 } };//���ܾ����������

	for (temp = 0; temp <= 3; temp++)
		a[temp] = *(b + temp);

	for (temp = 0; temp <= 3; temp++)//���ܣ�����˷�
	{
		for (int i = 0; i <= 3; i++)
		{
			*(b + temp) += a[i] * (iEncrypt[temp][i]);
		}
	};


}

void CreateFile(void)//���һ�������û�����������ļ��ĺ���������ʼ���û��������룬Ĭ�ϲ���������
{
	FILE *fp;
	UAPW user;
	pUAPW pTemp;
	pTemp = &user;
	if ((fp = fopen("D:/user.txt", "rb")) == NULL)                 /*������ļ�������*/
	{
		if ((fp = fopen("D:/user.txt", "wb+")) == NULL)
		{
			printf("�޷������ļ�\n");
			return;
		}
		else
		{
			wcscpy(user.wcID, L"�û�");
			user.iPassWord[0] = 0;
			user.iPassWord[1] = 0;
			user.iPassWord[2] = 0;
			user.iPassWord[3] = 0;
			user.iSwitch = 0;
			fwrite(pTemp, sizeof(UAPW), 1, fp);
		}

	}
	fclose(fp);
	return;
}

wchar_t* Identify(void)//��֤�û���ݵĺ���
{
	FILE*fp;
	UAPW user;
	int temp;//���룬ѭ��������
	int a[4];//������ܺ������

	if ((fp = fopen("D:/user.txt", "rb+")) == NULL)
	{
		printf("�ļ��޷���\n");
		return NULL;
	}

	else
	{
		fread(&user, sizeof(UAPW), 1, fp);
		if (user.iSwitch == 0)
			return user.wcID;
		else
		{
			for (;;)//���������Ƿ����Ҫ����λ���֣�
			{
				printf("*********************\n");
				wprintf(L"��ǰ�û�Ϊ��%ls\n", user.wcID);
				printf("*********************\n");
				wprintf(L"���������루Ĭ��0000����\t");
				scanf("%d", &temp);
                if (temp > 9999 || temp < 0)//�����Ƿ�Ϊ��λ
				{
					system("cls");
					setbuf(stdin, NULL);
					wprintf(L"�����������������\n");
				}
				else 
				{
					a[0] = temp % 10;//ȡ����
					a[1] = (temp - a[0]) % 100;
					a[2] = (temp - a[0] - a[1]) % 1000;
					a[3] = temp - a[0] - a[1] - a[2];

					Key(a);

					for (temp = 0; temp <= 3; temp++)//�Ƚ�
					{
						if (a[temp] == user.iPassWord[temp])
						{
							if (temp == 3)
							{
								fclose(fp);
								system("cls");
								return user.wcID;
							}
						}
						else
						{
							system("cls");
							wprintf(L"�������!����������\n");
							break;
						}
					}
				}
			}
		}
	}


}

void ChangeIDandPW(void)//�޸��û���������ĺ���
{
	FILE*fp;
	UAPW user;
	pUAPW pUser = &user;
	int a[4];
	int temp;//��ʱ����
	int iSubCommand;//��¼ָ��
	printf("******************************************\n");
	printf("�˳����β����밴ESC���������밴����� \n");
	printf("******************************************\n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	}

	fp = fopen("D:/user.txt", "rb+");
	fread(&user, sizeof(UAPW), 1, fp);
	Identify();
	system("cls");
	for (;;)
	{
		printf("*********************\n");
		wprintf(L"��ǰ�û�Ϊ��%s\n", user.wcID);
		printf("*********************\n");
		wprintf(L"������/�رա������밴  0\n");
		wprintf(L"�޸��û����밴         1\n");
		wprintf(L"�޸������밴           2\n");
		wprintf(L"�������˵��밴         3\n");
		printf("*********************\n");
		wprintf(L"�����������\t");
		scanf("%d", &iSubCommand);
		system("cls");
		switch (iSubCommand)
		{
		case 0:
			if (user.iSwitch == 0)
			{
				user.iSwitch = 1;
				wprintf(L"���뿪���ɹ���\n");
			}
			else
			{
				user.iSwitch = 0;
				wprintf(L"�����ѹرգ�\n");
			};
			break;
		case 1:
			wprintf(L"�������µ��û�����\t");
			wscanf(L"%ls", user.wcID);
			system("cls");
			break;
		case 2:
			for (;;)
			{
				wprintf(L"�������µ����루��λ����\t");
				scanf("%d", &temp);
				if (temp > 9999 || temp < 0)//�����Ƿ�Ϊ��λ
				{
					wprintf(L"���벻����Ҫ������������\n");
					setbuf(stdin, NULL);
					system("cls");
				}
				else break;
			};
			a[0] = temp % 10;//ȡ����
			a[1] = (temp - a[0]) % 100;
			a[2] = (temp - a[0] - a[1]) % 1000;
			a[3] = temp - a[0] - a[1] - a[2];
			Key(a);
			user.iPassWord[0] = a[0];
			user.iPassWord[1] = a[1];
			user.iPassWord[2] = a[2];
			user.iPassWord[3] = a[3];
			wprintf(L"�����޸ĳɹ���\n");
			break;
		case 3:
			fclose(fp);
			fp = fopen("D:/user.txt", "wb+");
			fwrite(pUser, sizeof(UAPW), 1, fp);
			fclose(fp);
			return;
		default:
			wprintf(L"��Ч�Ĳ���������������\n");
			setbuf(stdin, NULL);
			break;
		};
	}
}

void ExitApplication(pINAEX pHead)//ʵ���˳�����ĺ���
{
	int iSubCommand;
	printf("************************************\n");
	printf("ȷ���˳������𣿰�ESCȡ������������˳� \n");
	printf("************************************\n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	}
	exit(0);
}


