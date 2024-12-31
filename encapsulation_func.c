#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"settings.h"
#include"function.h"
#include"file_function.h"
#include"encapsulation_func.h"
#include<time.h>

/*菜单add选项的封装，并询问 是否多次在程序添加账单 是否在txt中手动输入帐目
   void
 */

void addBill()
{
    int choice;
    printf("\nwhat kind of operation do you want to do?\n1.add bill from txt file\n2.add bill manually\n");
    scanf("%d", &choice);
    while (getchar() != '\n'); 
    char type = 'y';
    if (choice == 1)
    {
        printf("\nmake sure the txt file has been changed and saved\n");
        printf("type to make sure the txt file has been changed and saved correctly(y/n)\n");
        scanf("%c", &type);
        while (getchar() != '\n'); 
        if (type == 'y')
        {
            loadBillsFromFile();
        }
        else if (type == 'n')
        {
            printf("\nok,your bill record keeps unchanged\n");
        }
        else
        {
            printf("\nyou type a wrong choice,so no bill have been added\n");
        }
    }
    else if (choice == 2)
    {
        addBillRecord();
        printf("\ndo you want to add more bills?(y/n)\n");
        scanf("%c", &type);
        while (getchar() != '\n'); 
        while (type != 'n')
        {
            addBillRecord();
            printf("\nagain?(y/n)\n");
            scanf("%c", &type);
            while (getchar() != '\n'); 
        }
        printf("\nall new bills have been added\n");
    }
    return;
}

/*delete选项的封装： 1指定id删除多项目录 2指定日期删除多项目录 3全部删除
 */
void delete()
{
    int choice;
    printf("\nwhat kind of operation do you want to do?\n1.delete a bill by id\n2.delete bills by date\n3.delete all bills\n");
    scanf("%d", &choice);
    while (getchar() != '\n'); 
    if (choice == 1)
    {
        int id;
        char type = 'y';
        printf("type the id of the bill you want to delete:\n");
        scanf("%d", &id);
        while (getchar() != '\n'); 
        deleteBill(id);
        printf("\ndo you want to add more bills?(y/n)\n");
        scanf("%c", &type);
        while (getchar() != '\n'); 
        while (type != 'n')
        {
            printf("type the id of the bill you want to delete:\n");
            scanf("%d", &id);
            while (getchar() != '\n'); 
            deleteBill(id);
            printf("\nagain?(y/n)\n");
            scanf("%c", &type);
            while (getchar() != '\n'); 
        }
        printf("all bills you type have been deleted\n");
    }
    else if (choice == 2)
    {
        deleteDayBill();
    }
    else if (choice == 3)
    {
        printf("are you sure to delete all bills?\n");
        printf("if you wangt,just go to the txt file and delete all the content in it\n");
        printf("you can't delete all bill records in the program\n");
    }
}

/*search选项的封装： 1.指定id查询账单 2.指定日期查询账单
 */
void search()
{
    int choice;
    printf("\nwhat kind of operation do you want to do?\n1.search a bill by id\n2.search bills by date\n");
    scanf("%d", &choice);
    while (getchar() != '\n'); 
    if (choice == 1)
    {
        int id;
        printf("\ntype the id of the bill you want to search:\n");
        scanf("%d", &id);
        while (getchar() != '\n'); 
        printBillById(id);
    }
    else if (choice == 2)
    {
        printBillByDate();
    }
    else
    {
        printf("wrong choice!\n");
    }
}

/*review选项的封装：1.按金额排序2.指定时间段内按金额给出统计信息3.指定单日内按金额给出信息
 */
void review()
{
    int choice;
    printf("\nwhat kind of operation do you want to do?\n1.review bills by day\n2.review bills by period\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        sortBillByAmount();
        printBillByDate();
    }
    else if (choice == 2)
    {
        printBillPeriod();
    }
    else
    {
        printf("\nwrong choice!\n");
    }
}

/*help选项的封装：一些提示信息
 */
void help()
{
    printf("author:<Fansirui>\n");
    printf("Here are some tips if you are in error:\n");
    printf("\n1.keep your bill txt file's format :\ndate:year month day\tid:id\tamount:amount\ttype:type\tps:ps\n");
    printf("\nfor example:\ndate:1 1 1	id:24649	amount:1	type:A	ps:wdw ada(long blank is tab)\n");
    printf("\n2.Don't change your bill txt when your program is running except for adding new bills from txt file\n");
    printf("\n3.keep your input in the program in the correct format,follow the tips in the program\n");
    printf("\n4.there is a README file in the program's directory,maybe you can read it\n");
}

/* quit 和 save选项的封装： 1.保存账单文件 2.退出程序
 */
void quitAndSave()
{
    updateBillRecord();
    return;
}