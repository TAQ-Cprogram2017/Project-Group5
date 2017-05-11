#include"head.h"
#include<stdio.h>
void ListCreation(pINAEX pHead)//按要求创建一个作为某个链表开头的结构体的函数
{
	float fValue;
	int iYear;
	int iMonth;
	int iDay;
	printf("请输入初始金额.\n");
	scanf_s("%f", &fValue);
	printf("请输入初始年份.\n");
	scanf_s("%d", &iYear);

	for (;;)//判断月份是否存在
	{
		printf("请输入初始月份.\n");
		scanf("%d", &iMonth);
		if (iMonth<1 || iMonth>12)
			printf("输入的月份无效，请重新输入\n");
		else break;
	}

	for (;;)//判断日期是否存在
	{
		printf("请输入初始日期.\n");
		scanf("%d", &iDay);
		if (Calendar(iYear, iMonth, iDay))
		{
			printf("输入的日期无效，请重新输入\n");
		}
		else break;
	}

	pHead->fValue=fValue;
	pHead->iYearDate = iYear;
	pHead->iMonthDate = iMonth;
	pHead->iDayDate = iDay;
	pHead->pNext = NULL;
	if (!pHead)
		return;
	printf("条目创建成功.\n");
}

pINAEX ListInitialise(float Value,int BeginYear,int BeginMonth, int BeginDay)//创建一个以Value为初始金额有着初始时间的收支链表
{
	pINAEX pIncomeAndExpenseList;
	pIncomeAndExpenseList = (pINAEX)malloc(sizeof(INAEX));//给一些空间
	if (!pIncomeAndExpenseList)
	{
		printf("获取空间失败!\n");
		return NULL;
	}
	/*初始化表头*/
	pIncomeAndExpenseList->iNumber = 1;
	pIncomeAndExpenseList->fValue = Value;
	wcscpy(pIncomeAndExpenseList->szLocation,L"初始地点");
	wcscpy(pIncomeAndExpenseList->szKind,L"初始类型");
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
	printf("请输入本次的收支金额.\n");
	scanf("%f", &fValue);
	printf("请输入本项收支所在年份.\n");
	scanf("%d", &iYear);

	for (;;)//判断月份是否存在
	{
		printf("请输入本项收支所在月份.\n");
		scanf("%d", &iMonth);
		if (iMonth<1 || iMonth>12)
			printf("输入的月份无效，请重新输入\n");
		else break;
	}

	for (;;)//判断日期是否存在
	{
		printf("请输入本项收支所在日期.\n");
		scanf("%d", &iDay);
		if (Calendar(iYear, iMonth, iDay))
		{
			printf("输入的日期无效，请重新输入\n");
		}
		else break;
	}
	pHead->fValue = fValue;
	pHead->iDayDate = iDay;
	pHead->iMonthDate = iMonth;
	pHead->iYearDate = iYear;

	printf("请输入本项收支所在地点.(19字以内)\n");
	SafeInput(wcLocation, 20);
	wcscpy(pHead->szLocation, wcLocation);

	printf("请输入本项收支类型.(19字以内)\n");
	SafeInput(wcKind, 20);
	wcscpy(pHead->szKind, wcKind);
	printf("条目创建成功.请您进行下一项操作.\n");
}

void ListAddtion(pINAEX pHead)//创建链表中的下一项
{
	pINAEX pTheNext= ListInitialise(0, 0, 0, 0);
	StructCreation(pTheNext);
	pINAEX pTemp = pHead;
	while (pTemp->pNext)//从链表的头移到最后一个有数据的节点
		pTemp = pTemp->pNext;
	pTemp->pNext = pTheNext;//让最后一个有数据的节点的指针指向新创建的节点
	pTheNext->iNumber = pTemp->iNumber + 1;
}

void ShowList(pINAEX pHead)
{
	pINAEX pTemp = pHead;
	while (pTemp)
	{
		wprintf(L"第%d项收支金额:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d\n",pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
		pTemp = pTemp->pNext;
	}
}

void SaveData(pINAEX pHead)
{
	FILE *fp;
	if((fp = fopen("D:/data.txt", "wb+"))==NULL)//用逐项写入的方式打开一个名为data.txt的二进制的文件
	{
		printf("无法打开文件!\n");
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
		printf("无法打开文件,并已经重新创建文件!\n");
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

void DeleteData(pINAEX pHead)//删除指定节点条目的函数
{
	int iNum;//作为计数器
	pINAEX pPre = pHead;
	printf("请输入需要删除的条目的序号：\t");
	scanf("%d", &iNum);
	if(iNum==1)
	{
		printf( "无法删除第一条初始数据\n" );
		return;
	}
	pINAEX pTemp = pHead;
	while (pTemp->iNumber != iNum)//从链表的头移到需要删除的节点
	{
		if ((pTemp->pNext == NULL))//如果已经到了末尾，就回到主函数
		{
			printf("没有找到这项条目!\n");
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

void SearchData(pINAEX pHead)//查找某年某月某日所有收支信息的函数
{
	pINAEX pTemp;
	int iYear;
	int iMonth;
	int iDay;
	int iJudgement;
	iJudgement = 0;// 用于判断是否一条记录都没有查到的标志

		printf("请输入所查项的收支所在年份.\n");
		scanf("%d", &iYear);
		printf("请输入所查项的收支所在月份.\n");
		scanf("%d", &iMonth);
		printf("请输入所查项的收支所在日期.\n");
		scanf("%d", &iDay);
		pTemp = pHead;
		do
		{
			if (pTemp->iYearDate == iYear && pTemp->iMonthDate == iMonth && pTemp->iDayDate == iDay)
			{
				wprintf(L"所查项目为第%d项收支金额:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
				iJudgement = 1;// 如果查到了记录，就把变量judgement变量赋值为1
			}
			pTemp = pTemp->pNext;
		} while (pTemp != NULL);
		if(iJudgement ==0)
	   printf("没有找到这一天的记录.\n");
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

void SafeInput(wchar_t wcArray[],int iLimit)//检查输入的字符是否超出数组容量，用1代表超出
{
	int iNum = iLimit  * 2-1;//将宽字符的上限转换为英文字符的长度，预留一个字节储存空字符
	wchar_t c = 0;//用于清空缓冲区
	for (;;)
	{
		wscanf(L"%ls", wcArray);
		if ((strlen(wcArray)) > iNum)//比较数组长度与容量
		{
			printf("*************************\n");
			printf("超过字数上限，请重新输入\n");
			printf("*************************\n");
			while (c = getwchar() != L'\n'&&c != EOF);//清空缓冲区
		}
		else
			break;
	} 

}

float SumAll(pINAEX pHead)//计算当前所有余额
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

void ExitApplication(pINAEX pHead)//实现退出程序的函数
{
	exit(0);
}


