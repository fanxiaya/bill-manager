#ifndef ENCAPSULATION_FUNC_H
#define ENCAPSULATION_FUNC_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"settings.h"
#include"file_function.h"
#include"function.h"

/*菜单add选项的封装，并询问 是否多次在程序添加账单 是否在txt中手动输入帐目
   void
 */
void addBill();

/*delete选项的封装： 1指定id删除多项目录 2指定日期删除多项目录 3全部删除
 */
void delete();

/*search选项的封装： 1.指定id查询账单 2.指定日期查询账单
 */
void search();

/*review选项的封装：1.按金额排序2.指定时间段内按金额给出统计信息3.指定单日内按金额给出信息
 */
void review();

/*help选项的封装：一些提示信息
 */
void help();

/* quit 和 save选项的封装： 1.保存账单文件 2.退出程序
 */
void quitAndSave();

#endif