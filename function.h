#ifndef FUNCTION_H
#define FUNCTION_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"settings.h"
#include"file_function.h"
#include"encapsulation_func.h"


/*创建新账单
 *返回 新帐单new_bill(id未定义，默认为0)
 */
Bill createBill();

/* 加载账目到链表尾部
 * 参数：账目new_bill
    void */
void loadBill(Bill new_bill);

/* 删除单个指定id的账目
 * 参数：账单id
   void
 */
Node *deleteBill(int id);
/* 修改单个指定的账目
 * 参数：账单bill，账单id
   void
 */

void modifyBill();

/* 有人干坏事了，ta要把那一天的账目全删掉
    void
 */
void deleteDayBill();

/*  显示指定日期的账目清单
    void
 */
void printBillByDate();

/* 显示指定id的账目
 * 参数：id 账单id
   void */
void printBillById(int id);

/* 根据每笔账单的金额进行排序(大到小)，改变链表自身顺序
 * 参数：list 账单链表自身
   void
 */
void sortBillByAmount();

/* 打印指定日期内支出or收入or所有账单的情况（金额从大到小的账目清单）
   void
*/
void printBillPeriod();

/*
打印首页菜单（支持的功能）
并接收保存用户的选项（key）
void
 */
void printMenu();

/*初始化程序并给出提示
   void
 */
void init();

/* 初始化用户
 */
void initUser();

/*重置链表 
 */
void freeList();

#endif