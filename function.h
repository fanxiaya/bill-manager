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
    printf("year month day amount type\n");
    scanf("%d%d%d%d%c", &new_bill.year, &new_bill.month, &new_bill.day, &new_bill.amount, &new_bill.type);
    printf("type your ps for this bill:\n"); // 给这份账目的的备注
    scanf("%s", new_bill.ps);
    new_bill.id = 0; // 账单id默认0
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
            user.head=new_node;
            user.tail=new_node;
        }
        else
        {user.tail->next=new_node; // 尾节点的下一个节点指向新节点
        user.tail = new_node; // 尾节点指向新节点
        }
}

/* 删除单个指定id的账目
 * 参数：账单id
   void
 */
Node* deleteBill(int id)
{

    Node *current = user.head;
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
    Node *res = current->next;
    if (current==user.head) 
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
    printf("expected bill have been successfully deleted!\n");
    return res;
}

/* 修改单个指定的账目
 * 参数：账单bill，账单id
   void
 */
void modifyBill( int id, Bill new_bill)
{
    Node *current = user.head;
    while (current->item.id != id)
    {
        if (current == NULL)
        {
            printf("no such bill!\n");
            return ;
        }
        current = current->next;
    }
    current->item = new_bill;
    printf("expected bill have been successfully modified!\n");
    return;
}

/* 有人干坏事了，ta要把那一天的账目全删掉
    void
 */
void deleteDayBill()
{
    Node *current = user.head;
    printf("are you sure to delete all bills of this day? think twice! (y/n)\n");
    char choice;
    scanf("n", &choice);//确定一下是否要删除，再根据选择来做操作

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
                current = deleteBill(current->item.id);         //防止current被删除导致无法更新
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
    void
 */
void printBillByDate()
{
    Node *current = user.head;
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
            printf("id:%d\tamount:%d\ttype:%c\tps:%s\n", current->item.id, current->item.amount, current->item.type, current->item.ps);
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
 * 参数：id 账单id
   void */
void printBillById(int id)
{
    Node *current = user.head;
    while (current != NULL)
    {
        if (current->item.id == id)
        {
            printf("date:%d %d %d\tid:%d\tamount:%d\ttype:%c\tps:%s\n",current->item.year,current->item.month, current->item.day, current->item.id, current->item.amount,current->item.type, current->item.ps);
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
    printf("type the year you want to see\n");
    int year;
    scanf("%d", &year);
    printf("type the start and end date in this order and format:\nmonth1 day1 month2 day2\n");
    int month1, day1, month2, day2;
    scanf("%d%d%d%d", &month1, &day1, &month2, &day2);
    printf("which type of bill do you want to see?\n1.income\t2.expenditure\t3.all\n(type 1,2 or 3)\n");
    int choice;
    scanf("%d", &choice);
    Node *current = user.head;
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

                printf("date:%d %d %d\tid:%d\tamount:%d\ttype:%c\tps:%s\n",current->item.year,current->item.month, current->item.day, current->item.id, current->item.amount,current->item.type, current->item.ps);
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
                printf("date:%d %d %d\tid:%d\tamount:%d\ttype:%c\tps:%s\n",current->item.year,current->item.month, current->item.day, current->item.id, current->item.amount,current->item.type, current->item.ps);
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
                printf("date:%d %d %d\tid:%d\tamount:%d\ttype:%c\tps:%s\n",current->item.year,current->item.month, current->item.day, current->item.id, current->item.amount,current->item.type, current->item.ps);
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
    printf("6.Some help information\n");
    printf("7.Quit the program and save your bill file\n");
    printf("please input your choice:\n");
    scanf("%d", &key);
}

/*初始化程序并给出提示
   void
 */
void init(){
    initUser();
    printf("loading your bill file,maybe wait a moment...\n");
    loadBillFile();
}

/*菜单add选项的封装，并询问 是否多次在程序添加账单 是否在txt中手动输入帐目
   void
 */

void addBill(){
    int choice;
    printf("what kind of operationdu you want to do?\n1.add bill from txt file\n2.add bill manually)\n");
    scanf("%d", &choice);
    char type = 'y';
    if (choice == 1)
    {
        printf("make sure the txt file has been changed and saved\n");
        printf("type to make sure the txt file has been changed and saved correctly(y/n)\n");
        scanf("%c", &type);
        if (type=='y')
        {
            loadBillsFromFile();
        }
        else if (type=='n')
        {
            printf("ok,your bill record keeps unchanged\n");
        }
        else
        {
            printf("you type a wrong choice,so no bill have been added\n");
        }
    }
    else if (choice == 2)
    {
        addBillRecord();
        printf("do you want to add more bills?(y/n)\n");
        scanf("%c", &type);
        while (type!='n')
        {
            addBillRecord();
            printf("again?(y/n)\n");
            scanf("%c", &type);
        }
        printf("all new bills have been added\n");
        }
        return;        
    }

/*delete选项的封装： 1指定id删除多项目录 2指定日期删除多项目录 3全部删除
 */
void delete(){
    int choice;
    printf("what kind of operation do you want to do?\n1.delete a bill by id\n2.delete bills by date\n3.delete all bills\n");
    scanf("%d", &choice);    
    if (choice == 1){
        int id;
        char type = 'y';
        printf("type the id of the bill you want to delete:\n");
        scanf("%d", &id);
        deleteBill(id);

        printf("do you want to add more bills?(y/n)\n");
        scanf("%c", &type);
        while (type!='n')
        {
            printf("type the id of the bill you want to delete:\n");
            scanf("%d", &id);
            deleteBill(id);
            printf("again?(y/n)\n");
            scanf("%c", &type);
        }
        printf("all bills you type have been deleted\n");
    }else if (choice == 2)
    {
        deleteDayBill();
    }else if (choice == 3)
    {
        printf("are you sure to delete all bills?\n");
        printf("if you wangt,just go to the txt file and delete all the content in it\n");
        printf("you can't delete all bill records in the program\n");
    }
    
    
}