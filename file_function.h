#ifndef FILE_FUNCTION_H
#define FILE_FUNCTION_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"settings.h"
#include"function.h"

/*
    手动输入账目信息并添加到链表中
    void
 */
void addBillRecord();

/*  从文件中读取一行账单记录并转换为 Bill 结构体
    参数：line 指向一行字符串的指针
    返回值：Bill类型
*/
Bill getBillFromRecord(char *line);


/*对一个bill结构体转化为对应格式字符串 
    参数：bill
 char* 返回指向字符串开头的字符指针
 */
char *convertBillToString(Bill bill);

/* 加载txt的每一行，转化成Bill类型，并生成 Node节点添加到链表中
 */
void loadBillsFromFile();

/* 
    更新record.txt文件，讲所有节点重写写入文件中
 */
void updateBillRecord();
#endif