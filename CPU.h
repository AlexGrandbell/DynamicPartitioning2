//
// Created by AlexGrandbell on 24-12-7.
//

#ifndef DYNAMICPARTITIONING2_CPU_H
#define DYNAMICPARTITIONING2_CPU_H

#include "RAM.h"

using namespace std;

//CPU类，模拟调度
class CPU {
public:
    RAM *ram; //内存

    CPU(RAM *ram): ram(ram) {}
    CPU(): ram(nullptr) {}
};

#endif //DYNAMICPARTITIONING2_CPU_H
