#include"head.h"
#include<stdio.h>
#define NUMBER_OF_SUBMENU 5//子菜单函数个数
void ListCreation(pINAEX pHead)//按要求创建一个作为某个链表开头的结构体的函数
{
	float fValue;
	int iTime[3];//数组储存的三项依次是年月日
	int iSubCommand;
	printf("******************************************\n");
	printf("退出本次操作请按ESC键，继续请按任意键 \n");
	printf("******************************************\n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	};

	printf("请输入初始金额.\n");
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
	int iTime[3];//存储年月日
	int iJudge;//判断是否直接输入读取的时间
	wchar_t wcLocation[20];
	wchar_t wcKind[20];

	printf("请输入本次的收支金额.（正数表示收入，负数表示输出）\n");
	scanf("%f", &fValue);
	ReadTime(iTime);
	iYear = iTime[0];
	iMonth = iTime[1];
	iDay = iTime[2];
	printf("请输入本项收支所在年份.\n（当前年份%d，按0输入）\n", iYear);
	scanf("%d", &iJudge);
	if (iJudge == 0);
	else iYear = iJudge;

	for (;;)//判断月份是否存在
	{
		printf("请输入本项收支所在月份.\n（当前月份%d,按0输入）\n", iMonth);
		scanf("%d", &iJudge);
		if (iJudge == 0);
		else iMonth = iJudge;
		if (iMonth<1 || iMonth>12)
			printf("输入的月份无效，请重新输入\n");
		else break;
	}

	for (;;)//判断日期是否存在
	{
		printf("请输入本项收支所在日期.\n（当前日期%d,按0输入）\n", iDay);
		scanf("%d", &iJudge);
		if (iJudge == 0);
		else iDay = iJudge;
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
	system("cls");
	printf("条目创建成功.请您进行下一项操作.\n");
}

void ListAddtion(pINAEX pHead)//创建链表中的下一项
{
	int iSubCommand;
	printf("退出本次操作请按ESC键，继续请按任意键 \n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	};
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
	ListSort(pHead);//sort list in time order
	pINAEX pTemp = pHead;
	printf("***********************************************************************\n");
	while (pTemp)
	{
		if (pTemp->fValue<0)
			wprintf(L"第%d项:支出%.2f元 时间%d.%d.%d 地点:%ls 类型:%ls\n", pTemp->iNumber, -(pTemp->fValue), pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate, pTemp->szLocation, pTemp->szKind);
		else
			wprintf(L"第%d项:收入%.2f元 时间%d.%d.%d 地点:%ls 类型:%ls\n", pTemp->iNumber, pTemp->fValue, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate, pTemp->szLocation, pTemp->szKind);
		pTemp = pTemp->pNext;
	}
	printf("***********************************************************************\n");
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
	int iSubCommand;
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
	ShowList(pHead);

	printf("请输入需要删除的条目的序号（输入0放弃操作）：\t");
	scanf("%d", &iNum);

	if (iNum == 0)
		return;
	if (iNum == 1)
	{
		system("cls");
		printf("无法删除第一条初始数据\n");
		return;
	}
	pINAEX pTemp = pHead;
	while (pTemp->iNumber != iNum)//从链表的头移到需要删除的节点
	{
		if ((pTemp->pNext == NULL))//如果已经到了末尾，就回到主函数
		{
			system("cls");
			printf("没有找到这项条目!\n");
			return;
		}
		pPre = pTemp;
		pTemp = pTemp->pNext;
		if ((pTemp->pNext == NULL) && (pTemp->iNumber == iNum))//如果需要删除的就是最后一项，就执行if语句后的内容，并返回。
		{
			pPre->pNext = NULL;
			free(pTemp);
			system("cls");
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
	int iJudgement, iSubCommand;
	iJudgement = 0;// 用于判断是否一条记录都没有查到的标志

	printf("******************************************\n");
	printf("退出本次操作请按ESC键，继续请按任意键 \n");
	printf("******************************************\n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	};

	printf("请输入所查项的收支所在年份.\n");
	scanf("%d", &iYear);
	for (;;)
	{
		printf("请输入所查项的收支所在月份.\n");
		scanf("%d", &iMonth);
		if (iMonth<1 || iMonth>12)
			printf("输入月份无效,请重新输入\n");
		else break;
	}
	for (;;)
	{
		printf("请输入所查项的收支所在日期.\n");
		scanf("%d", &iDay);
		if (Calendar(iYear, iMonth, iDay) == 1)
		{
			system("cls");
			printf("输入日期无效,请重新输入\n");
		}
		else
			break;
	}

	pTemp = pHead;
	printf("所查项目为:\n");
	do
	{
		if (pTemp->iYearDate == iYear && pTemp->iMonthDate == iMonth && pTemp->iDayDate == iDay)
		{
			wprintf(L"第%d项收支:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			iJudgement = 1;// 如果查到了记录，就把变量judgement变量赋值为1
		}
		pTemp = pTemp->pNext;
	} while (pTemp != NULL);
	if (iJudgement == 0)
		printf("没有找到这一天的记录.\n");
}

int Calendar(int iYear, int iMonth, int iDay)//判断输入日期是否存在的函数,返回值为1表示不存在
{
	if (iMonth < 1 || iMonth>12)
		return 1;

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
	return 1;
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
			printf("超过字数上限，请重新输入!\n");
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

void NodeSwap(pINAEX a, pINAEX b)//在交换元素时保留iNumber
{
	pINAEX c = (pINAEX)malloc(sizeof(INAEX));
	if (!c)
	{
		printf("获取空间失败!\n");
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

void ListSort(pINAEX pHead)//时间顺序对线性表排序 
{
	pINAEX pTemp = pHead;
	while (pTemp->pNext) pTemp = pTemp->pNext;
	int num = pTemp->iNumber;
	while (--num)//冒泡排序
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

void ShowDailyList(pINAEX pHead)//查询具体日期的收支情况
{
	ListSort(pHead);//sort list in time order
	int year, month, day,curyear,curmonth,curday, iSubCommand;
	float total;

	printf("******************************************\n");
	printf("退出本次操作请按ESC键，继续请按任意键 \n");
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
					printf("%d年%d月%d日收入了%.2f\n", curyear, curmonth, curday, total);
				else
					printf("%d年%d月%d日支出了%.2f\n", curyear, curmonth, curday, -total);
				break;
			}
		} while (pTemp);
		
	}
	if (total>0)                                          //输出最新一天的记录
		printf("%d年%d月%d日收入了%.2f\n", curyear, curmonth, curday, total);
	else
		printf("%d年%d月%d日支出了%.2f\n", curyear, curmonth, curday, -total);
}

void SearchForPeriod(pINAEX pHead)
{
	int Y1, Y2, M1, M2, D1, D2;
	int iJudgement = 0, iSubCommand;
	float fSum = 0;

	printf("******************************************\n");
	printf("退出本次操作请按ESC键，继续请按任意键 \n");
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
		printf("请输入所查时间段收支情况的起始年份.\n");
		scanf("%d", &Y1);
		printf("请输入所查时间段收支情况的起始月份.\n");
		scanf("%d", &M1);
		printf("请输入所查时间段收支情况的起始日期.\n");
		scanf("%d", &D1);
		if(Calendar(Y1,M1,D1)==1)
		{
			printf("您输入的日期无效\n");
		}
		else break;
	}
	printf("******************************************\n");
	while (1)
	{
		printf("请输入所查时间段收支情况的终止年份.\n");
		scanf("%d", &Y2);
		printf("请输入所查时间段收支情况的终止月份.\n");
		scanf("%d", &M2);
		printf("请输入所查时间段收支情况的终止日期.\n");
		scanf("%d", &D2);
		if (Calendar(Y2, M2, D2) == 1)
		{
			printf("您输入的日期无效\n");
		}
		else
			break;
	}
	printf("******************************************\n");
	system("cls");
	printf("所查项目为%d.%d.%d至%d.%d.%d之间的收支记录:", Y1, M1, D1, Y2, M2, D2);
	while (pTemp != NULL)
	{
		if (pTemp->iYearDate > Y1 && pTemp->iYearDate < Y2)
		{
			fSum = fSum + pTemp->fValue;
			wprintf(L"第%d项收支:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			iJudgement = iJudgement + 1;
			pTemp = pTemp->pNext;
			continue;
		}
		else if (pTemp->iYearDate == Y1 && pTemp->iMonthDate > M1)
		{
			fSum = fSum + pTemp->fValue;
			wprintf(L"第%d项收支:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			iJudgement = iJudgement + 1;
			pTemp = pTemp->pNext;
			continue;
		}
		else if ((pTemp->iYearDate == Y1 && pTemp->iMonthDate == M1) && pTemp->iDayDate >= D1)
		{
			fSum = fSum + pTemp->fValue;
			wprintf(L"第%d项收支:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			iJudgement = iJudgement + 1;
			pTemp = pTemp->pNext;
			continue;
		}
		else if ((pTemp->iYearDate == Y2) && (pTemp->iMonthDate < M2))
		{
			fSum = fSum + pTemp->fValue;
			wprintf(L"第%d项收支:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			iJudgement = iJudgement + 1;
			pTemp = pTemp->pNext;
			continue;
		}

		else if ((pTemp->iYearDate == Y2 && pTemp->iMonthDate == M2) && pTemp->iDayDate <= D2)
		{
			fSum = fSum + pTemp->fValue;
			wprintf(L"第%d项收支:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			iJudgement = iJudgement + 1;
			pTemp = pTemp->pNext;
			continue;
		}
		else  pTemp = pTemp->pNext;
	}
	printf("******************************************\n");
	if (iJudgement == 0)
		printf("该时间段您没有做任何记录\n");
	else
	{

		if (fSum>0)
			printf("这段时间收入了%.2f\n", fSum);
		else
			printf("这段时间支出了%.2f\n",  -fSum);
	}
	printf("******************************************\n");
}
void CorrectData(pINAEX pHead)//更改某一记录
{
	ShowList(pHead);

	int iNum, iJudgement, iSubCommand;
	iJudgement = 0;
	pINAEX pTemp;

	printf("******************************************\n");
	printf("退出本次操作请按ESC键，继续请按任意键 \n");
	printf("******************************************\n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	}
	else
		printf("\n");

	printf("请输入需要修改的条目的序号:\t");
	scanf("%d", &iNum);
	pTemp = pHead;
	while (pTemp != NULL)
	{

		if (pTemp->iNumber != iNum)
			pTemp = pTemp->pNext;
		else
		{
			iJudgement = 1;
			printf("所查项目为:\n");
			printf("***************************************************************************\n");
			wprintf(L"第%d项收支:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			printf("请输入正确的金额\n");
			scanf("%f", &pTemp->fValue);
			printf("***************************************************************************\n");
			wprintf(L"第%d项收支:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			printf("请输入正确的地点\n");
			SafeInput(pTemp->szLocation, 20);
			printf("***************************************************************************\n");
			wprintf(L"第%d项收支:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			printf("请输入正确的类型\n");
			SafeInput(pTemp->szKind, 20);
			printf("***************************************************************************\n");
			wprintf(L"第%d项收支:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			printf("请输入正确的 年\n");
			scanf("%d", &pTemp->iYearDate);
			printf("***************************************************************************\n");
			wprintf(L"第%d项收支:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			printf("请输入正确的 月\n");
			scanf("%d", &pTemp->iMonthDate);
			printf("***************************************************************************\n");
			wprintf(L"第%d项收支:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate);
			printf("请输入正确的 日\n");
			scanf("%d", &pTemp->iDayDate);
			break;
			ListSort(pHead);
		}
	}
	system("cls");
	if (iJudgement == 0)
		printf("没有找到这条条目\n");
	ShowList(pHead);
}

void ExceedingValue(pINAEX pHead)//显示所有超处某金额限度的记录(该限制金额由用户自己输入)
{
	int iJudgement = 0, iSubCommand;
	float fLimit, fExceeding;

	printf("******************************************\n");
	printf("退出本次操作请按ESC键，继续请按任意键 \n");
	printf("******************************************\n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	};

	pINAEX pTemp;
	pTemp = pHead;
	printf("请输入您所限制的额度\n");
	scanf("%f", &fLimit);
	printf("所查项目为:\n");
	printf("********************************************************************\n");
	while (pTemp != NULL)
	{
		if (- pTemp->fValue >= fLimit)
		{
			fExceeding = -fLimit-pTemp->fValue;
			wprintf(L"第%d项收支金额:%.2f 地点:%ls 类型:%ls 时间%d.%d.%d,超出的金额为%.2f\n", pTemp->iNumber, pTemp->fValue, pTemp->szLocation, pTemp->szKind, pTemp->iYearDate, pTemp->iMonthDate, pTemp->iDayDate, fExceeding);
			iJudgement = iJudgement + 1;
			pTemp = pTemp->pNext;
		}
		else pTemp = pTemp->pNext;
	}
	if (iJudgement == 0)
		printf("当前没有超出限度的记录\n");
	printf("********************************************************************\n");
}

void ReadTime(int iTime[3])//读取本机时间，数组依次存储年月日
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
	for (;;)//开始一个循环
	{
		printf("*******************************\n");
		printf("当前余额为：  %10.2f\n", SumAll(pHead));//将当前的余额显示在当前的界面上
		printf("*******************************\n");
		printf("返回主菜单请按                0\n");
		printf("显示当前全部记录请按          1\n");
		printf("查询具体日期的收支情况        2\n");
		printf("统计某时间段的收支情况请输入  3\n");
		printf("查询每日的收支情况请输入      4\n");
		printf("查询超出某一限度的所有记录    5\n");
		printf("*******************************\n");
		printf("请输入您要进行的操作:\t");
		scanf("%d", &iSubCommand);
		if (iSubCommand<0 || iSubCommand>NUMBER_OF_SUBMENU)
		{
			system("cls");
			setbuf(stdin, NULL);
			printf("输入了不合法的操作!请重新输入:\t\n");
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

void Key(int* b)//密码加密的函数
{
	int a[4];
	int temp;
	const int iEncrypt[4][4] = { { 7,3,8,7 },{ 9,3,3,9 },{ 7,7,13,7 },{ 9,2,2,9 } };//加密矩阵（奇异矩阵）

	for (temp = 0; temp <= 3; temp++)
		a[temp] = *(b + temp);

	for (temp = 0; temp <= 3; temp++)//加密，矩阵乘法
	{
		for (int i = 0; i <= 3; i++)
		{
			*(b + temp) += a[i] * (iEncrypt[temp][i]);
		}
	};


}

void CreateFile(void)//检查一个储存用户名和密码的文件的函数，并初始化用户名和密码，默认不开启密码
{
	FILE *fp;
	UAPW user;
	pUAPW pTemp;
	pTemp = &user;
	if ((fp = fopen("D:/user.txt", "rb")) == NULL)                 /*如果此文件不存在*/
	{
		if ((fp = fopen("D:/user.txt", "wb+")) == NULL)
		{
			printf("无法建立文件\n");
			return;
		}
		else
		{
			wcscpy(user.wcID, L"用户");
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

wchar_t* Identify(void)//验证用户身份的函数
{
	FILE*fp;
	UAPW user;
	int temp;//密码，循环计数器
	int a[4];//储存加密后的数字

	if ((fp = fopen("D:/user.txt", "rb+")) == NULL)
	{
		printf("文件无法打开\n");
		return NULL;
	}

	else
	{
		fread(&user, sizeof(UAPW), 1, fp);
		if (user.iSwitch == 0)
			return user.wcID;
		else
		{
			for (;;)//检验密码是否符合要求（四位数字）
			{
				printf("*********************\n");
				wprintf(L"当前用户为：%ls\n", user.wcID);
				printf("*********************\n");
				wprintf(L"请输入密码（默认0000）：\t");
				scanf("%d", &temp);
                if (temp > 9999 || temp < 0)//检验是否为四位
				{
					system("cls");
					setbuf(stdin, NULL);
					wprintf(L"密码错误，请重新输入\n");
				}
				else 
				{
					a[0] = temp % 10;//取数字
					a[1] = (temp - a[0]) % 100;
					a[2] = (temp - a[0] - a[1]) % 1000;
					a[3] = temp - a[0] - a[1] - a[2];

					Key(a);

					for (temp = 0; temp <= 3; temp++)//比较
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
							wprintf(L"密码错误!请重新输入\n");
							break;
						}
					}
				}
			}
		}
	}


}

void ChangeIDandPW(void)//修改用户名和密码的函数
{
	FILE*fp;
	UAPW user;
	pUAPW pUser = &user;
	int a[4];
	int temp;//临时变量
	int iSubCommand;//记录指令
	printf("******************************************\n");
	printf("退出本次操作请按ESC键，继续请按任意键 \n");
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
		wprintf(L"当前用户为：%s\n", user.wcID);
		printf("*********************\n");
		wprintf(L"【开启/关闭】密码请按  0\n");
		wprintf(L"修改用户名请按         1\n");
		wprintf(L"修改密码请按           2\n");
		wprintf(L"返回主菜单请按         3\n");
		printf("*********************\n");
		wprintf(L"请输入操作：\t");
		scanf("%d", &iSubCommand);
		system("cls");
		switch (iSubCommand)
		{
		case 0:
			if (user.iSwitch == 0)
			{
				user.iSwitch = 1;
				wprintf(L"密码开启成功！\n");
			}
			else
			{
				user.iSwitch = 0;
				wprintf(L"密码已关闭！\n");
			};
			break;
		case 1:
			wprintf(L"请输入新的用户名：\t");
			wscanf(L"%ls", user.wcID);
			system("cls");
			break;
		case 2:
			for (;;)
			{
				wprintf(L"请输入新的密码（四位）：\t");
				scanf("%d", &temp);
				if (temp > 9999 || temp < 0)//检验是否为四位
				{
					wprintf(L"密码不符合要求，请重新输入\n");
					setbuf(stdin, NULL);
					system("cls");
				}
				else break;
			};
			a[0] = temp % 10;//取数字
			a[1] = (temp - a[0]) % 100;
			a[2] = (temp - a[0] - a[1]) % 1000;
			a[3] = temp - a[0] - a[1] - a[2];
			Key(a);
			user.iPassWord[0] = a[0];
			user.iPassWord[1] = a[1];
			user.iPassWord[2] = a[2];
			user.iPassWord[3] = a[3];
			wprintf(L"密码修改成功！\n");
			break;
		case 3:
			fclose(fp);
			fp = fopen("D:/user.txt", "wb+");
			fwrite(pUser, sizeof(UAPW), 1, fp);
			fclose(fp);
			return;
		default:
			wprintf(L"无效的操作，请重新输入\n");
			setbuf(stdin, NULL);
			break;
		};
	}
}

void ExitApplication(pINAEX pHead)//实现退出程序的函数
{
	int iSubCommand;
	printf("************************************\n");
	printf("确定退出程序吗？按ESC取消，按任意键退出 \n");
	printf("************************************\n");
	iSubCommand = getch();
	if (iSubCommand == 0x1b)
	{
		system("cls");
		return;
	}
	exit(0);
}


