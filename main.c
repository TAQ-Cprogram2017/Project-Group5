#include"head.h"
#include<stdio.h>
#define NUMBER_OF_MENU 11//菜单函数的个数
void main(void)
{
	int iCommand;//用来记录用户输入的命令
	void (*Menu[NUMBER_OF_MENU+1])(pINAEX);//定义菜单指针数组
	Menu[0] = ListCreation;
	Menu[1] = ListAddtion;
	Menu[2] = DeleteData;
	Menu[3] = ShowList;
	Menu[4] = ShowDailyList;
	Menu[5] = ReadData;
	Menu[6] = SaveData;
	Menu[7] = SearchData;
	Menu[8] = SearchForPeriod;
	Menu[9] = ShowDailyList;
	Menu[10] = CorrectData;
	Menu[11] = ExitApplication;
	setlocale(LC_ALL, "chs");//设置语言本地化 
	printf("欢迎使用记账本.\n");
	pINAEX pHead = ListInitialise(0, 0, 0, 0);
	Menu[5](pHead);//读取初始的数据
	for(;;)//开始一个循环
	{
		printf("************************\n");
		printf("当前余额为：  %10.2f\n", SumAll(pHead));//将当前的余额显示在当前的界面上
		printf("重新初始化请输入              0\n");
		printf("增加收支条目输入              1\n");
		printf("删除数据请按                  2\n");
		printf("显示当前全部记录请按          3\n");
		printf("查询具体日期的收支情况        4\n");
		printf("重新读取数据请按              5\n");
		printf("保存当前数据请输入            6\n");
		printf("查询历史数据请输入            7\n");
		printf("统计某时间段的收支情况请输入  8\n");
		printf("查询每日的收支情况请输入      9\n");
		printf("修改某一条目                  10\n");
		printf("退出程序请按                  11\n");
		printf("************************\n");
		printf("请输入您要进行的操作:\t");
		scanf("%d", &iCommand);
		if(iCommand<0||iCommand>NUMBER_OF_MENU)
		{
			
			system("cls");
			printf("输入了不合法的操作!请重新输入:\t\n");
			continue;
		}
		else
		{
			switch (iCommand)
			{
			case 1:
				Menu[3](pHead);
				Menu[iCommand](pHead);
				Menu[6](pHead);
				system("cls");
				break;
			case 2:
				Menu[3](pHead);
				system("cls");
				Menu[iCommand](pHead);
				Menu[6](pHead);
				
				break;
			default:
				system("cls");
				Menu[iCommand](pHead);
				Menu[6](pHead);
				break;
			}
		}
	}
}


/***********************************************************************************************************
*   完成内容：菜单函数、文件的读写、条目的增加、删除与显示、查询历史记录的功能                             *
*   最后修改时间：2017/6/1  20：45                                                                           *
*   修改日志记录：                                                                                         *
*   2017/4/4  14：00     刘子琦     完成了 链表基础部分的结构                                              *
*	2017/4/4  24：00     徐苏恒     完成了 宽字符的中文输入，文件的存储和读出                              *
*	2017/4/5  08：04     徐苏恒     完成了 由指针数组构成的菜单函数                                        *
*   2017/4/5  12：30     徐苏恒     完成了 对指定链表节点的删除功能                                        *
*   2017/4/5  19：30 刘子琦、徐苏恒 完成了 调试、函数结构的修改、变量的规范化                              *                                                  *
*   2017/4/21 17：47     王珊珊     完成了 查找历史记录的函数											   *
*	2017/4/23 01: 31     于文昊     完成了 日历函数与函数的进一步安全化									   *
*   2017/5/3  20: 07     徐苏恒     完成了 在菜单界面显示了当前余额，用System调用清屏函数                  *
*   2017/5/4  20：13     刘子琦     完成了 菜单函数结构的优化                                              *
*   2017/5/17 18：53     季佳熠     完成了 链表按时间排序                                                  *
*   2017/5/17 18：53     季佳熠     完成了 合并每天收支，以天为单位展示收支情况                            *                       
*   2017/5/30 16：30     季佳熠     完成了 进行收入和支出的区分                                            *
*   2017/6/1  18：00     王珊珊     完成了 增加给定区间计算收支情况                                        *
*   2017/6/1  18：00     王珊珊     完成了 自动保存数据                                                    *
*   2017/6/1  20：45     徐苏恒     完成了 增加了修改条目函数，修改了删除条目时发生的bug                   *
*   历史文件保存在的位置  D:/data.txt                                                                      *
************************************************************************************************************/




