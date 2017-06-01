#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>
#include<locale.h>
#ifndef _HEAD_H_
#define _HEAD_H_
/*预设的几种消费类型*/
#define BLE BasicLifeExpense
#define DLE DevelopedLifeExpense
#define ME MentalExpense
#define IFP IncomeFromParents
#define IFE IncomeFromEarning
/*简化的字符*/
#define pHead TheHeadofAnIncomeAndExpenseList 
#define pCur TheCurrentTerm 
#define pPre ThePreviousTerm  

/*结构体的声明*/
typedef struct _INCOME_AND_EXPENSE
{
	int iNumber;//用于记录这是第几条记录，便于之后的操作
	float fValue;//收支数额
	wchar_t szLocation[20];//消费场所
    wchar_t szKind[20];//消费类型
    int iYearDate;//年
	int iMonthDate;//月
	int iDayDate;//日
	struct _INCOME_AND_EXPENSE * pNext;//链表的下一个元素
}INAEX;//简化结构体名
typedef INAEX * pINAEX;//创建一个INAEX类型的指针

/*对函数的声明*/
pINAEX ListInitialise(float, int, int, int);//对一个节点的初始化
void ListCreation(pINAEX); //列表头初始化
void StructCreation(pINAEX);//让用户输入一个节点的信息
void ListAddtion(pINAEX);//添加一个节点
void ShowList(pINAEX head);//遍历整个链表并输出数据
void SaveData(pINAEX);//保存数据
void ReadData(pINAEX);//读取数据
void DeleteData(pINAEX);//删除某个特定节的函数
void ExitApplication(pINAEX);//退出程序
void SearchData(pINAEX head);//查询数据
int Calendar(int, int, int);//判断日期是否存在
void SafeInput(wchar_t wcArray[],int );//确保输入的字符不会超出数组容量
float SumAll(pINAEX);//计算当前的余额
void NodeSwap(pINAEX, pINAEX);//交换节点数据函数
void ListSort(pINAEX);//链表排序
void ShowDailyList(pINAEX);//查询具体日期的收支情况
void SearchForPeriod(pINAEX pHead);//统计一个给定区间收支情况
void CorrectData(pINAEX pHead);//修改输错的条目
#endif // _HEAD_H_
