// 基于多态的管理系统.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "workerManager.h"
#include"Boss.h"
using namespace std;

int main()
{
    
    while (true)
    {
        workerManager wM;
        wM.wMmuen();
        int choice = 0;
        cin >> choice;
        switch (choice)
        {
        case 0:
            wM.exitSystem();
            break;
        case 1:
            wM.addWorker();
            break;
        case 2:
            wM.showInfo();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        default:
            system("cls");
            break;
        }
        
    }
    
    return 0;
}

