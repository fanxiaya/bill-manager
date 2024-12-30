#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "settings.h"

/*
    手动输入账目信息并添加到链表中
    void
 */
void addBillRecord()
{
    // 手动输入bill信息
    Bill new_bill;
    printf("type this bill in this order and format:\tyear month day amount type\n");
    int year, month, day, amount;
    char type, ps[100];
    scanf("%d %d %d %d %c", &new_bill.year, &new_bill.month, &new_bill.day, &new_bill.amount, &new_bill.type);
    printf("type the ps of this bill:\n");
    scanf("%s", new_bill.ps);

    loadBill(new_bill);     //加载到链表中
}

// 从文件中读取账单记录并转换为 Bill 结构体
Bill getBillFromRecord(char *line)
{
    Bill bill;
    // 读取每一行的数据
    sscanf(line, "date:%d %d %d\tid:%d\tamount:%d\ttype:%c\tps:%s\n",&bill.year, &bill.month, &bill.day, &bill.id, &bill.amount, &bill.type, bill.ps);
    return bill;
}

/*对一个bill结构体转化为对应格式字符串 
    参数：bill
 char* 返回指向字符串开头的字符指针
 */
char* convertBillToString(Bill bill){
    char res[100];
    sprintf(res, "date:%d %d %d\tid:%d\tamount:%d\ttype:%c\tps:%s\n", bill.year, bill.month, bill.day, bill.id, bill.amount, bill.type, bill.ps);
    return res;
}

/* 加载txt的每一行，转化成Bill类型，并生成 Node节点添加到链表中
 */
void loadBillsFromFile()
{
    FILE *file = fopen("record.txt", "r");
    if (file == NULL)
    {
        printf("Failed to open file.\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file))
    {
        // 解析每一行的数据并创建 Bill 结构体
        Bill new_bill = getBillFromRecord(line);

        // 创建新节点并添加到链表中,调用function.h中的addBill
        loadBill(new_bill);
    }
    fclose(file);
    printf("Bills loaded successfully from the file.\n");
}

/* 
    更新record.txt文件，讲所有节点重写写入文件中
 */ 
void updateBillRecord(){
    Node *current = user.head;
    FILE *file = fopen("record.txt", "w");
    fclose(file);
    FILE *file = fopen("record.txt", "a");
while (current!= NULL)  
{
    char* tep = convertBillToString(current->item);
    fwrite(tep, strlen(tep), 1, file);
    current = current->next;
}
fclose(file);
}
