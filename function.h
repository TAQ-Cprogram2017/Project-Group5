#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>
#include<locale.h>
#include<windows.h>
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

pINAEX ListInitialise(float Value, int BeginYear, int BeginMonth, int BeginDay)//创建一个以Value为初始金额有着初始时间的收支链表
{
	pINAEX pIncomeAndExpenseList;
	pIncomeAndExpenseList = (pINAEX)malloc(sizeof(INAEX));//给一些空间
	if (!pIncomeAndExpenseList)
	{
		return NULL;
	}
	/*初始化表头*/
	pIncomeAndExpenseList->iNumber = 1;
	pIncomeAndExpenseList->fValue = Value;
	wcscpy(pIncomeAndExpenseList->szLocation, L"初始地点");
	wcscpy(pIncomeAndExpenseList->szKind, L"初始类型");
	pIncomeAndExpenseList->iYearDate = BeginYear;
	pIncomeAndExpenseList->iMonthDate = BeginMonth;
	pIncomeAndExpenseList->iDayDate = BeginDay;
	pIncomeAndExpenseList->pNext = NULL;//
	return pIncomeAndExpenseList;
}

void StructCreation(pINAEX pHead)//按要求创建一个收支结构体的函数,
{
	float fValue;
	int iYear;
	int iMonth;
	int iDay;
	wchar_t wcLocation[20];
	wchar_t wcKind[20];
	scanf("%f", &fValue);
	scanf("%d", &iYear);

	for (;;)//判断月份是否存在
	{
		scanf("%d", &iMonth);
		if (iMonth < 1 || iMonth>12);
		else break;
	}

	for (;;)//判断日期是否存在
	{
		scanf("%d", &iDay);
		if (Calendar(iYear, iMonth, iDay))
		{
		}
		else break;
	}
	pHead->fValue = fValue;
	pHead->iDayDate = iDay;
	pHead->iMonthDate = iMonth;
	pHead->iYearDate = iYear;
	SafeInput(wcLocation, 20);
	wcscpy(pHead->szLocation, wcLocation);
	SafeInput(wcKind, 20);
	wcscpy(pHead->szKind, wcKind);
}

void ListAddtion(pINAEX pHead)//创建链表中的下一项
{
	pINAEX pTheNext = ListInitialise(0, 0, 0, 0);
	StructCreation(pTheNext);
	pINAEX pTemp = pHead;
	while (pTemp->pNext)//从链表的头移到最后一个有数据的节点
		pTemp = pTemp->pNext;
	pTemp->pNext = pTheNext;//让最后一个有数据的节点的指针指向新创建的节点
	pTheNext->iNumber = pTemp->iNumber + 1;
}


void SaveData(pINAEX pHead)
{
	FILE *fp;
	if ((fp = fopen("D:/data.txt", "wb+")) == NULL)//用逐项写入的方式打开一个名为data.txt的二进制的文件
	{
		return;
	}
	pINAEX pTemp;
	pTemp = pHead;
	do
	{
		fwrite(pTemp, sizeof(INAEX), 1, fp);//块输入数据
		pTemp = pTemp->pNext;
	} while (pTemp != NULL);//遍历这个链表，将数据存入文件中
	fclose(fp);
}

void ReadData(pINAEX pHead)
{
	FILE *fp;
	if ((fp = fopen("D:/data.txt", "rb")) == NULL)//用读取的方式打开一个名为data.txt的二进制的文件
	{
		fp = fopen("D:/data.txt", "wb+");
		SaveData(pHead);
		return;
	}
	rewind(fp);//保证在流输入中从文件开头读入数据
	pINAEX pPre, pCur;//建立两个指针，在之后的读取数据中会使用到
	fread(pHead, sizeof(INAEX), 1, fp);//从文件中块输入表头数据
	pPre = pHead;
	if (pHead->pNext != NULL)
	{
		pHead->pNext = pPre;
	}
	else
		pHead->pNext = NULL;
	while (pPre->pNext != NULL)
	{
		pCur = (pINAEX)malloc(sizeof(INAEX));//为新的节点开辟一个新的空间
		pPre->pNext = pCur;//使得之前的节点中的指针指向新的节点
		fread(pCur, sizeof(INAEX), 1, fp);//从文件中块输入表头数据
		pPre = pCur;//将cur保存在pre中
	}
	fclose(fp);
}

void DeleteData(pINAEX pHead,int iIndex)//删除指定节点条目的函数
{
	int iNum = iIndex;
	pINAEX pPre = pHead;
	if (iNum == 1)
	{
		return;
	}
	pINAEX pTemp = pHead;
	while (pTemp->iNumber != iNum)//从链表的头移到需要删除的节点
	{
		if ((pTemp->pNext == NULL))//如果已经到了末尾，就回到主函数
		{
			return;
		}
		pPre = pTemp;
		pTemp = pTemp->pNext;
		if ((pTemp->pNext == NULL) && (pTemp->iNumber == iNum))//如果需要删除的就是最后一项，就执行if语句后的内容，并返回。
		{
			pPre->pNext = NULL;
			free(pTemp);
			return;
		}
	}
	pPre->pNext = pTemp->pNext;//连接被删除节点前后的两个节点
	free(pTemp);//释放需要删除的节点
	pTemp = pPre->pNext;
	do//更改被删除节点之后每个节点的序号
	{
		pPre = pTemp;
		pTemp->iNumber--;
		pTemp = pTemp->pNext;
	} while (pPre->pNext != NULL);
}

int Calendar(int iYear, int iMonth, int iDay)//判断输入日期是否存在的函数,返回值为1表示不存在
{
	if (iDay < 1 || iDay>31)//排除不存在的日期
		return 1;

	if (iMonth == 2)//判断二月日期
		if (iYear % 4 == 0 && iYear % 400 != 0)//是闰年
		{
			if (iDay > 29)
				return 1;
			else return 0;
		}
		else//不是闰年
		{
			if (iDay > 28)
				return 1;
			else return 0;
		}
	if (iDay == 31)//区分大小月
	{
		if (iMonth == 4 || iMonth == 6 || iMonth == 9 || iMonth == 11)
			return 1;
		else return 0;
	};
	if (iDay <= 30)
		return 0;
}

void SafeInput(wchar_t wcArray[], int iLimit)//检查输入的字符是否超出数组容量，用1代表超出
{
	int iNum = iLimit * 2 - 1;//将宽字符的上限转换为英文字符的长度，预留一个字节储存空字符
	wchar_t c = 0;//用于清空缓冲区
	for (;;)
	{
		wscanf(L"%ls", wcArray);
		if ((strlen(wcArray)) > iNum)//比较数组长度与容量
		{
			while (c = getwchar() != L'\n'&&c != EOF);//清空缓冲区
		}
		else
			break;
	}
}


#endif // _FUNCTION_H_

