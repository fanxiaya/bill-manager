#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"settings.h"
#include"function.h"
#include"encapsulation_func.h"

int key;
List user;

int main()
{
    init();
    do
    {
        printMenu();
        switch (key)
        {
        case 1:
            addBill();
            break;
        case 2:
            delete ();
            break;
        case 3:
            modifyBill();
            break;
        case 4:
            search();
            break;
        case 5:
            review();
            break;
        case 6:
            help();
            break;
        }
    } while (key != 7);

    quitAndSave();
    return 0;
}
