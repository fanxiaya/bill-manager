#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "settings.h"

/*
    手动输入的bill记录，写入到record.txt
    接收当前账目节点指针作为参数
    -1 添加失败  1 添加成功
 */
int addBillRecord()
{
    FILE *file = fopen("record.txt", "a+");
    // 手动输入bill信息
    Bill new_bill;
    printf("type this bill in this order and format:\tyear month day amount type");
    int year, month, day, amount;
    char type, ps[100];
    scanf("%d %d %d %d %c", &new_bill.year, &new_bill.month, &new_bill.day, &new_bill.amount, &new_bill.type);
    printf("type the ps of this bill:\n");
    scanf("%s", ps);

    int state = fprintf(file,"" );
    fclose(file);
    if (!state)
    {
        printf("Failed to write to file.\n");
        return -1;
    }
    else
    {
        printf("Bill record added successfully.\n");
        return 1;
    }
}

// 从文件中读取账单记录并转换为 Bill 结构体
Bill getBillFromRecord(char *line)
{
    Bill bill;
    // 读取每一行的数据
    sscanf(line, "date:%d %d %d\tid:%d\tamount:%d\ttype:%c\tps:%s",&bill.year, &bill.month, &bill.day, &bill.id, &bill.amount, &bill.type, bill.ps);
    return bill;
}

/* 加载txt的每一行，转化成Bill类型，并生成Node节点添加到链表中
 */
void loadBillsFromFile(List list)
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
        addBill(new_bill);
    }
    fclose(file);
    printf("Bills loaded successfully from file.\n");
}