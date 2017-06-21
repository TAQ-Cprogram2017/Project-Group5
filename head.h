#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>
#include<locale.h>
#include<time.h>
#ifndef _HEAD_H_
#define _HEAD_H_
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

typedef struct USER_AND_PASSWORD//用户名和密码的结构体
{
	wchar_t wcID[20];
	int iPassWord[4];
	int iSwitch;//用来指示用户是否需要设置密码,等于0表示不开启密码
}UAPW;
typedef UAPW* pUAPW;//指向 用户名和密码结构体的指针

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
void ReadTime(int[3]);//读取本机时间
void ExceedingValue(pINAEX pHead);//显示所有超处某金额限度的记录(该限制金额由用户自己输入)
void SearchOnDemand(pINAEX);//集成搜索功能的子菜单函数
void CreateFile(void);//创建一个储存用户名和密码的文件函数
void Key(int*);//密码加密的函数
wchar_t* Identify(void);//验证用户身份的函数
void ChangeIDandPW(void);//修改用户名和密码的函数
#endif // _HEAD_H_
