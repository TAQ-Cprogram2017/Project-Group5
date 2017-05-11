#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>
#include<locale.h>
#include<windows.h>
#ifndef _HEAD_H_
#define _HEAD_H_
/*按钮的数量*/
#define NUM (sizeof (button)/sizeof (button[0]))
struct
{
	int iStyle;
	TCHAR * szText;
}
button[] =
{
	BS_PUSHBUTTON,           TEXT("重新初始化"),
	BS_PUSHBUTTON,           TEXT("显示全部记录"),
	BS_PUSHBUTTON,           TEXT("重新读取记录"),
	BS_PUSHBUTTON,           TEXT("保存当前记录"),
	BS_PUSHBUTTON,           TEXT("新增一项记录"),
	BS_PUSHBUTTON,           TEXT("删除指定记录"),
	BS_PUSHBUTTON,           TEXT("查询历史数据")
};

/*数据存储结构体的声明*/
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
void StructCreation(pINAEX);//让用户输入一个节点的信息
void ListAddtion(pINAEX);//添加一个节点
void SaveData(pINAEX);//保存数据
void ReadData(pINAEX);//读取数据
void DeleteData(pINAEX,int);//删除某个特定节的函数
void ExitApplication(pINAEX);//退出程序
int Calendar(int, int, int);//判断日期是否存在
void SafeInput(wchar_t wcArray[], int);//确保输入的字符不会超出数组容量

#endif // _HEAD_H_