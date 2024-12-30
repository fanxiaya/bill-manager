#ifndef SETTINGS_H
#define SETTINGS_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct bill // 账单定义
{
    int id;
    int year;
    int month;
    int day;
    int amount;
    char ps[100];
    char type; // A.衣食住行支出 B.吃喝玩乐支出 C.收入 D.其他
};
typedef struct bill Bill;

struct bill_node // 账单节点定义
{
    Bill item;
    struct bill_node *next;
};
typedef struct bill_node Node;

struct bill_list // 账单链表定义
{
    int size;   // 账目数量
    Node *head; // 头指针
    Node *tail; // 尾指针
};
typedef struct bill_list List;

/* 初始化用户 */
extern List user;  // 保存一个用户

extern int key; // 保存用户选择的菜单选项
#endif