#include"head.h"
#include<stdio.h>
#define NUMBER_OF_MENU 7//菜单函数的个数
void main(void)
{
	int iCommand,iJudgement;//用来记录用户输入的命令
	wchar_t wcID[20];
	void(*Menu[NUMBER_OF_MENU + 1])(pINAEX);//定义菜单指针数组
	Menu[0] = ListCreation;
	Menu[1] = ListAddtion;
	Menu[2] = DeleteData;
	Menu[3] = ReadData;
	Menu[4] = CorrectData;
	Menu[5] = SearchOnDemand;
	Menu[6] = ChangeIDandPW;
	Menu[7] = ExitApplication;

	void(*BKstage[2])(pINAEX);//执行程序时后台使用的函数
	BKstage[0] = ShowList;
	BKstage[1] = SaveData;

	setlocale(LC_ALL, "chs");//设置语言本地化 

	CreateFile();
	wcscpy(wcID, Identify());

	printf("欢迎使用记账本.\n");
	pINAEX pHead = ListInitialise(0, 0, 0, 0);
	Menu[3](pHead);//读取初始的数据
	for (;;)//开始一个循环
	{
		printf("*******************************\n");
		printf("您好，%ls\n", wcID);
		printf("当前余额为：  %10.2f\n", SumAll(pHead));//将当前的余额显示在当前的界面上
		printf("*******************************\n");
		printf("重新初始化请输入              0\n");
		printf("增加收支条目输入              1\n");
		printf("删除数据请按                  2\n");
		printf("重新读取数据请按              3\n");
		printf("修改某一条目                  4\n");
		printf("按要求查询历史记录            5\n");
		printf("设置用户名和密码              6\n");
		printf("退出程序请按                  7\n");
		printf("*******************************\n");
		printf("请输入您要进行的操作:\t");
		scanf("%d", &iCommand);
		if (iCommand<0 || iCommand>NUMBER_OF_MENU)
		{

			system("cls");
			setbuf(stdin, NULL);
			printf("输入了不合法的操作!请重新输入:\t\n");
			continue;
		}
		else
		{
			switch (iCommand)
			{
			case 1:
				system("cls");
				BKstage[0](pHead);
				Menu[iCommand](pHead);
				BKstage[1](pHead);
				break;
			case 2:
				BKstage[0](pHead);

				system("cls");
				Menu[iCommand](pHead);
				BKstage[1](pHead);
				BKstage[0](pHead);
				break;
			default:
				system("cls");
				Menu[iCommand](pHead);
				BKstage[1](pHead);
				break;
			}
		}

	}
}


/***********************************************************************************************************
*   完成内容：菜单函数、文件的读写、条目的增加、删除与显示、查询历史记录的功能                             *
*   最后修改时间：2017/6/8 12:16                                                                           *
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
*	2017/6/5  15: 00	 于文昊		完成了 增加删除数据时显示数据和放弃删除操作的功能					   *
*	2017/6/5  21: 21	 于文昊		完成了 读取本机时间函数与初始化和增加条目中时间的自动输入			   *
*	2017/6/8  12: 14	 于文昊		完成了 集成搜索功能的子菜单函数										   *
*	2017/6/9  15: 31	 王珊珊		完成了 显示所有超处某金额限度的记录									   *
*	2017/6/10 15: 44	 王珊珊		完成了 防止用户错误输入的情况										   *
*	2017/6/10 16: 52 于文昊、徐苏恒 完成了 增加用户名和密码功能											   *
*	2017/6/11 08: 27     刘子琦     完成了 修改了增加条目处的问题                               		   *
*	2017/6/11 08: 30     刘子琦     完成了 修改了查询历史记录的一些细节      		                       *
*	2017/6/11 08: 50     刘子琦     完成了 修改了在菜单中输入其他字符时进入死循环的问题                    *
*	2017/6/11 09: 00     刘子琦     完成了 修改了查询超出限额函数符号的问题                                *
*   历史文件保存在的位置  D:/data.txt                                                                      *
************************************************************************************************************/





