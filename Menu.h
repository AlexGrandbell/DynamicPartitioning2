//
// Created by AlexGrandbell on 24-12-7.
//

#ifndef DYNAMICPARTITIONING2_MENU_H
#define DYNAMICPARTITIONING2_MENU_H

#include "CPU.h"
#include "FirstRAM.h"
#include "BestRAM.h"
#include "WorstRAM.h"

class Menu {
public:
    CPU cpu;
    int mode;//1-最先适应法 2-最佳适应法 3-最坏适应法
    int size;//内存大小

    Menu(): mode(1), size(600) {
        cpu = CPU(new FirstRAM(size));
    }

    void ShowMenu();
private:
    void chooseMode();//选择三种算法
    void setRAMSize();//设置内存大小
    void allocateMemory();//分配内存
    void recycleMemory();//回收内存
};


#endif //DYNAMICPARTITIONING2_MENU_H
