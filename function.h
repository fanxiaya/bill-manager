#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "settings.h"
#include "file_function.h"

/*创建新账单
 *返回 新帐单new_bill(id未定义，默认为0)
 */
Bill createBill()
{
    Bill new_bill;
    printf("type your bill date in this order and format:\n");
    printf("year month day ±amount type\n");
    scanf("%d%d%d%d%c", &new_bill.year, &new_bill.month, &new_bill.day, &new_bill.amount, &new_bill.type);
    printf("type your ps for this bill:\n"); // 给这份账目的的备注
    scanf("%s", new_bill.ps);
    new_bill.id = 0; // 账单id默认0
    return new_bill;
}
/* 加载txt中的账目到链表尾部
 * 参数：帐单链表自身list
    void */
void loadBill(Bill new_bill)
{
    user.size++;
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->item = new_bill;
    new_node->next = NULL;
        if (user.head == NULL)
        { // 若首节点为空
            user.head->item = new_bill;
        }
        else
        { // 若首节点不为空
            user.tail->next = new_node;
            user.tail = new_node;
        }
}

/* 删除单个指定的账目
 * 参数：账单链表自身list，账单id
   返回：待删除的节点的下一个节点 Node*(供其他delete函数调用)
 */
Node *deleteBill(List list, int id)
{

    Node *current = list.head;
    Node *previous = NULL; // 指向current的前节点
    while (current->item.id != id)
    {
        if (current == NULL)
        {
            printf("no such bill!\n");
            return NULL;
        }
        previous = current;
        current = current->next;
    }
    // current不可能为空且此时为指定id账目的节点，处理几种特殊情况
    Node *res = current->next; // 获取返回值
    if (current->item.id == 1)
    { // 如果要删除首账目
        list.head = current->next;
    }
    else if (current->item.id == list.size) // 删除尾部账目
    {
        list.tail = previous;
        list.tail->next = NULL;
    }
    else // 删除首尾之外账目
    {
        previous->next = current->next;
    }
    list.size--;
    free(current);
    printf("expected bill have been successfully deleted!\n");
    return res;
}

/* 修改单个指定的账目
 * 参数：账单链表自身list，账单id
   返回：待删除的节点的下一个节点 Node*(供其他delete函数调用)
 */
Node *modifyBill(List list, int id, Bill new_bill)
{
    Node *current = list.head;
    while (current->item.id != id)
    {
        if (current == NULL)
        {
            printf("no such bill!\n");
            return NULL;
        }
        current = current->next;
    }
    current->item = new_bill;
    printf("expected bill have been successfully modified!\n");
}

/* 有人干坏事了，ta要把那一天的账目全删掉
    参数：账单链表自身list
    void
 */
void deleteDayBill(List list)
{
    Node *current = list.head;

    printf("are you sure to delete all bills of this day? think twice! (y/n)\n");
    char choice;

    scanf("n", &choice);

    if (choice == 'n')
    {
        printf("ok,no bill have been deleted\n");
        return;
    }

    else if (choice == 'y')
    {
        printf("type your bill date in this order and format:\nyear month day\n");
        int year, month, day, state = 0;
        scanf("%d%d%d", &year, &month, &day);
        while (current != NULL)
        {
            if (current->item.year == year && current->item.month == month && current->item.day == day)
            {
                current = deleteBill(list, current->item.id);
                state = 1;
            }
            else
            {
                current = current->next;
            }
        }
        if (state == 0)
        {
            printf("no such bill of that day \n");
        }
        else
        {
            printf("all bills of that day have been deleted\n");
        }
    }

    else
    {
        printf("you type a wrong choice,so no bill have been deleted\n");
        return;
    }
}

/*  显示指定日期的账目清单
    参数：账单链表自身 list
    void
 */
void printBillByDate(List list)
{
    Node *current = list.head;
    int state = 0; // 0表示未找到指定日期的账目，1表示找到了指定日期的账目
    // 输入期望的日期
    printf("what date's bills do you want to see?\ntype your date in this order and format:\nyear month day\n");
    int year, month, day;
    scanf("%d%d%d", &year, &month, &day);
    printf("here you are the bills of %d-%d-%d:\n", year, month, day);

    // 遍历链表，打印指定日期的账目
    while (current != NULL)
    {
        if (current->item.year == year && current->item.month == month && current->item.day == day)
        {
            printf("bill id:%d\tamount:%d\ttype:%c\tps:%s\n", current->item.id, current->item.amount, current->item.type, current->item.ps);
            state = 1;
        }
        current = current->next;
    }
    if (state == 0)
    {
        printf("there is no bill of %d-%d-%d\n", year, month, day);
        return;
    }
    else
    {
        printf("that's all bills of %d-%d-%d\n", year, month, day);
        return;
    }
}

/* 显示指定id的账目
 * 参数：list 账单链表自身, id 账单id
   void */
void printBillById(List list, int id)
{
    Node *current = list.head;
    while (current != NULL)
    {
        if (current->item.id == id)
        {
            printf("bill id:%d\tamount:%d\ttype:%c\tps:%s\n", current->item.id, current->item.amount, current->item.type, current->item.ps);
            return;
        }
    }
    printf("no such bill!\n");
    return;
}

/* 根据每笔账单的金额进行排序(大到小)，改变链表自身顺序
 * 参数：list 账单链表自身
   void
 */
void sortBillByAmount(List list)
{
    Node *current = list.head;
    // 选择排序
    for (int i = 1; i <= list.size - 1; i++)
    {
        Node *temp = current->next;
        for (int j = 1; j <= list.size - i; j++)
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
 * 参数：list 账单链表自身
   void
*/

void printBillPeriod(List list)
{
    sortBillByAmount(list);
    printf("type the year you want to see\n");
    int year;
    scanf("%d", &year);
    printf("type the start and end date in this order and format:\nmonth1 day1 month2 day2\n");
    int month1, day1, month2, day2;
    scanf("%d%d%d%d", &month1, &day1, &month2, &day2);
    printf("which type of bill do you want to see?\n1.income\t2.expenditure\t3.all\n(type 1,2 or 3)\n");
    int choice;
    scanf("%d", &choice);
    Node *current = list.head;
    if (choice == 1)
    {
        int count_C = 0, count_D = 0; // 收入，分C,D两类
        while (current != NULL)
        {
            if (current->item.year == year && current->item.month >= month1 && current->item.month <= month2 && current->item.day >= day1 && current->item.day <= day2 && current->item.amount > 0)
            {
                if (current->item.type == 'A')
                {
                    count_C += current->item.amount;
                }
                else if (current->item.type == 'C' && current->item.amount > 0)
                {
                    count_D += current->item.amount;
                }

                printf("bill id:%d\tamount:%d\ttype:%c\tps:%s\n", current->item.id, current->item.amount, current->item.type, current->item.ps);
            }
            current = current->next;
        }
        printf("C income:%d\tD income:%d\n", count_C, count_D);
        printf("total income:%d\n", count_C + count_D);
        printf("that's all income bills you want\n");
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
                printf("bill id:%d\tamount:%d\ttype:%c\tps:%s\n", current->item.id, current->item.amount, current->item.type, current->item.ps);
            }
        }
        printf("A expenditure:%d\tB expenditure:%d\n", count_A, count_B);
        printf("total expenditure:%d\n", count_A + count_B);
        printf("that's all expenditure bills you want\n");
    }
    else if (choice == 3)
    {
        int count = 0;
        while (current != NULL)
        {
            if (current->item.year == year && current->item.month >= month1 && current->item.month <= month2 && current->item.day >= day1 && current->item.day <= day2)
            {
                count += current->item.amount;
                printf("bill id:%d\tamount:%d\ttype:%c\tps:%s\n", current->item.id, current->item.amount, current->item.type, current->item.ps);
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
    printf("1.Add your bill file\n");
    printf("2.Delete a bill\n");
    printf("3.Modify a bill\n");
    printf("4.Search your bill records\n");
    printf("5.Review your bill records\n");
    printf("6.Quit the program and save your bill file\n");
    printf("7.Some help information\n");
    printf("please input your choice:\n");
    scanf("%d", &key);
}