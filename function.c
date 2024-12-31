#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "settings.h"
#include "file_function.h"
#include "encapsulation_func.h"
#include <time.h>
#include "function.h"

/*创建新账单
 *返回 新帐单new_bill
 */
Bill createBill()
{
    Bill new_bill;
    printf("type your bill date in this order and format:\n");
    printf("year month day amount type\n");
    scanf("%d%d%d%d %c", &new_bill.year, &new_bill.month, &new_bill.day, &new_bill.amount, &new_bill.type);
    while (getchar() != '\n')
        ;

    printf("type your ps for this bill:\n"); // 给这份账目的的备注
    fgets(new_bill.ps, 100, stdin);
    int len = strlen(new_bill.ps); // 保证ps的末尾不是换行
    if (len > 0 && new_bill.ps[len - 1] == '\n')
    {
        new_bill.ps[len - 1] = '\0';
    }
    return new_bill;
}

/* 加载账目到链表尾部
 * 参数：账目new_bill
    void */
void loadBill(Bill new_bill)
{
    user.size++;
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->item = new_bill;
    new_node->next = NULL;
    if (user.head == NULL)
    { // 若首节点为空
        user.head = new_node;
        user.tail = new_node;
    }
    else
    {
        user.tail->next = new_node; // 尾节点的下一个节点指向新节点
        user.tail = new_node;       // 尾节点指向新节点
    }
}

/* 删除单个指定id的账目
 * 参数：账单id
   void
 */
Node *deleteBill(int id)
{

    Node *current = user.head;
    Node *previous = NULL; // 指向current的前节点
    while ( current != NULL && current->item.id != id) 
    {
        previous = current;
        current = current->next;
    }
    if (current == NULL)
    {
        printf("no such bill!\n");
        return NULL;
    }
    // current不可能为空且此时为指定id账目的节点，处理几种特殊情况
    Node *res = current->next;
    if (current == user.head)
    { // 如果要删除首账目
        user.head = current->next;
    }
    else if (current == user.tail) // 删除尾部账目
    {
        user.tail = previous;
        user.tail->next = NULL;
    }
    else // 删除首尾之外账目
    {
        previous->next = current->next;
    }
    user.size--;
    free(current);
    return res;
}

/* 修改单个指定的账目
 * 参数：账单bill，账单id
   void
 */
void modifyBill()
{

    printf("\ntype the bill's id if you want to modify:\n");
    int id;
    scanf("%d", &id);
    while (getchar() != '\n')
        ;
    Node *current = user.head;
    while ( current != NULL && current->item.id != id)
    {
        current = current->next;
    }
    if (current == NULL)
    {
        printf("no such bill!\n");
        return;
    }
    else
    {
        Bill new_bill = createBill();
        new_bill.id = current->item.id; // 继承原来的id
        current->item = new_bill;       // 修改新的账目
        printf("\nexpected bill have been successfully modified!\n");
        return;
    }
}

/* 有人干坏事了，ta要把那一天的账目全删掉
    void
 */
void deleteDayBill()
{
    Node *current = user.head;
    printf("\nare you sure to delete all bills of this day? think twice! (y/n)\n");
    char choice;
    scanf("%c", &choice); // 确定一下是否要删除，再根据选择来做操作
    while (getchar() != '\n')
        ;
    if (choice == 'n')
    {
        printf("ok,no bill have been deleted\n");
        return;
    }
    else if (choice == 'y')
    {
        printf("\ntype your bill date in this order and format:\nyear month day\n");
        int year, month, day, state = 0;
        scanf("%d%d%d", &year, &month, &day);
        while (getchar() != '\n')
            ;
        while (current != NULL)
        {
            if (current->item.year == year && current->item.month == month && current->item.day == day)
            {
                current = deleteBill(current->item.id); // 防止current被删除导致无法更新
                state = 1;
            }
            else
            {
                current = current->next;
            }
        }
        if (state == 0)
        {
            printf("\nno such bill of that day \n");
        }
        else
        {
            printf("\nall bills of that day have been deleted\n");
        }
    }
    else
    {
        printf("\nyou type a wrong choice,so no bill have been deleted\n");
        return;
    }
}

/*  显示指定日期的账目清单
    void
 */
void printBillByDate()
{
    Node *current = user.head;
    int state = 0; // 0表示未找到指定日期的账目，1表示找到了指定日期的账目
    // 输入期望的日期
    printf("\nwhat date's bills do you want to see?\ntype your date in this order and format:\nyear month day\n");
    int year, month, day;
    scanf("%d%d%d", &year, &month, &day);
    while (getchar() != '\n')
        ;
    // 遍历链表，打印指定日期的账目
    while (current != NULL)
    {
        if (current->item.year == year && current->item.month == month && current->item.day == day)
        {
            printf("id:%d\tamount:%d\ttype:%c\tps:%s\n", current->item.id, current->item.amount, current->item.type, current->item.ps);
            state = 1;
        }
        current = current->next;
    }
    if (state == 0)
    {
        printf("\nthere is no bill of %d-%d-%d\n", year, month, day);
        return;
    }
    else
    {
        printf("\nthat's all bills of %d-%d-%d\n", year, month, day);
        return;
    }
}

/* 显示指定id的账目
 * 参数：id 账单id
   void */
void printBillById(int id)
{
    Node *current = user.head;
    while ( current != NULL && current->item.id != id)
    {
        current = current->next;
    }
    if (current == NULL)
    {
        printf("no such bill!\n");
        return;
    }
    printf("date:%d %d %d\tid:%d\tamount:%d\ttype:%c\tps:%s\n",current->item.year, current->item.month, current->item.day,current->item.id, current->item.amount, current->item.type,current->item.ps);
}

/* 根据每笔账单的金额进行排序(大到小)，改变链表自身顺序
 * 参数：list 账单链表自身
   void
 */
void sortBillByAmount()
{
    Node *current = user.head;
    // 选择排序
    for (int i = 1; i <= user.size - 1; i++)
    {
        Node *temp = current->next;
        for (int j = 1; j <= user.size - i; j++)
        {
            if (current->item.amount < temp->item.amount)
            {
                Bill temp_bill = current->item;
                current->item = temp->item;
                temp->item = temp_bill;
            }
            temp = temp->next;
        }
        current = current->next;
    }
}

/* 打印指定日期内支出or收入or所有账单的情况（金额从大到小的账目清单）
   void
*/

void printBillPeriod()
{
    sortBillByAmount();
    printf("\ntype the year you want to see\n");
    int year;
    scanf("%d", &year);
    while (getchar() != '\n')
        ;
    printf("\ntype the start and end date in this order and format:\nmonth1 day1 month2 day2\n");
    int month1, day1, month2, day2;
    scanf("%d%d%d%d", &month1, &day1, &month2, &day2);
    while (getchar() != '\n')
        ;
    printf("\nwhich type of bill do you want to see?\n1.income\t2.expenditure\t3.all\n(type 1,2 or 3)\n");
    int choice;
    scanf("%d", &choice);
    while (getchar() != '\n')
        ;
    Node *current = user.head;
    if (choice == 1)
    {
        int count_C = 0, count_D = 0; // 收入，分C,D两类
        while (current != NULL)
        {
            if (current->item.year == year && current->item.month >= month1 && current->item.month <= month2 && current->item.day >= day1 && current->item.day <= day2 && current->item.amount > 0)
            {
                if (current->item.type == 'C')
                {
                    count_C += current->item.amount;
                }
                else if (current->item.type == 'D' && current->item.amount > 0)
                {
                    count_D += current->item.amount;
                }

                printf("date:%d %d %d\tid:%d\tamount:%d\ttype:%c\tps:%s\n", current->item.year, current->item.month, current->item.day, current->item.id, current->item.amount, current->item.type, current->item.ps);
            }
            current = current->next;
        }
        printf("\nC income:%d\tD income:%d\n", count_C, count_D);
        printf("total income:%d\n", count_C + count_D);
        printf("\nthat's all income bills you want\n");
    }
    else if (choice == 2)
    {
        int count_A = 0, count_B = 0; // A支出总数，B支出总数
        while (current != NULL)
        {
            if (current->item.year == year && current->item.month >= month1 && current->item.month <= month2 && current->item.day >= day1 && current->item.day <= day2 && current->item.amount < 0)
            {
                if (current->item.type == 'A')
                {
                    count_A += current->item.amount;
                }
                else if (current->item.type == 'B')
                {
                    count_B += current->item.amount;
                }
                printf("date:%d %d %d\tid:%d\tamount:%d\ttype:%c\tps:%s\n", current->item.year, current->item.month, current->item.day, current->item.id, current->item.amount, current->item.type, current->item.ps);
            }
        }
        printf("\nA expenditure:%d\tB expenditure:%d\n", count_A, count_B);
        printf("total expenditure:%d\n", count_A + count_B);
        printf("\nthat's all expenditure bills you want\n");
    }
    else if (choice == 3)
    {
        int count = 0;
        while (current != NULL)
        {
            if (current->item.year == year && current->item.month >= month1 && current->item.month <= month2 && current->item.day >= day1 && current->item.day <= day2)
            {
                count += current->item.amount;
                printf("date:%d %d %d\tid:%d\tamount:%d\ttype:%c\tps:%s\n", current->item.year, current->item.month, current->item.day, current->item.id, current->item.amount, current->item.type, current->item.ps);
            }
            current = current->next;
            printf("total amount:%d\n", count);
            printf("that's all bills you want\n");
        }
    }
    else
    {
        printf("you type a wrong choice,so no bill have been printed\n");
        return;
    }
}

/*
打印首页菜单（支持的功能）
并接收保存用户的选项（key）
void
 */
void printMenu()
{
    printf("------------------------------------------------------------------------------------------------\n");
    printf("1.Add a bill to the file\n");
    printf("2.Delete a bill\n");
    printf("3.Modify a bill\n");
    printf("4.Search your bill records\n");
    printf("5.Review your bill records\n");
    printf("6.Some help information\n");
    printf("7.Quit the program and save your bill file\n");
    printf("please input your choice:\n");
    printf("------------------------------------------------------------------------------------------------\n");
    scanf("%d", &key);
    while (getchar() != '\n')
        ;
}

/*初始化程序并给出提示
   void
 */
void init()
{
    initUser();
    printf("loading your bill file,maybe wait a moment...\n");
    loadBillsFromFile();
}

/* 初始化用户
 */
void initUser()
{
    user.size = 0;
    user.head = NULL;
    user.tail = NULL;
}

/*重置链表
 */
void freeList()
{
    Node *current = user.head;
    Node *next;

    // 遍历链表释放节点
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    // 重置链表
    user.head = NULL;
    user.tail = NULL;
    user.size = 0;
}