//
// Created by AlexGrandbell on 24-12-7.
//

#include "Menu.h"

//菜单
void Menu::ShowMenu() {
    int choice;
    while (true) {
        cout<<"\n当前算法: ";
        switch (mode) {
            case 1:
                cout<<"最先适应法"<<endl;
                break;
            case 2:
                cout<<"最佳适应法"<<endl;
                break;
            default:
                cout<<"最坏适应法"<<endl;
                break;
        }
        cout<<"当前内存大小: "<<cpu.ram->totalSize<<endl;
        cout<<"/**---------菜单---------**\\"<<endl;
        cout << "1.切换算法" << endl;
        cout << "2.设置内存大小"<<endl;
        cout << "3.分配内存" << endl;
        cout << "4.回收内存" << endl;
        cout << "0.退出" << endl;
        cout<<"/-**------菜单结束-------**\\"<<endl;
        cout << "请选择:";
        cin >> choice;
        switch (choice) {
            case 1:
                chooseMode();
                break;
            case 2:
                setRAMSize();
                break;
            case 3:
                allocateMemory();
                break;
            case 4:
                recycleMemory();
                break;
            default:
                return;
        }
    }
}

//选择算法
void Menu::chooseMode() {
    cout << "请选择算法(1-最先适应法 2-最佳适应法 3-最坏适应法):";
    cin >> mode;
    //更改CPU的RAM
    switch (mode) {
        case 1:
            cpu = CPU(new FirstRAM(size));
            break;
        case 2:
            cpu = CPU(new BestRAM(size));
            break;
        default:
            cpu = CPU(new WorstRAM(size));
            break;
    }
    cout<<"算法更改成功，已重新分配空的内存"<<endl;
}

//设置内存大小
void Menu::setRAMSize() {
    cout << "请输入内存大小:";
    cin >> size;
    if (size<=0){
        cout<<"失败: 内存大小不得为0，内存大小并未修改"<<endl;
        return;
    }
    //修改内存大小
    cpu.ram->totalSize = size;
}

//分配内存
void Menu::allocateMemory() {
    cout << "请输入进程id:";
    int id;
    cin >> id;
    cout << "请输入进程大小:";
    int needSize;
    cin >> needSize;
    cpu.ram->AllocateMemory(id, needSize);
    cpu.ram->ShowMemoryStatus();
}

//回收内存
void Menu::recycleMemory() {
    cout << "请输入进程id:";
    int id;
    cin >> id;
    cpu.ram->RecycleMemory(id);
    cpu.ram->ShowMemoryStatus();
}