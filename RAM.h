//
// Created by AlexGrandbell on 24-12-7.
//

#ifndef DYNAMICPARTITIONING2_RAM_H
#define DYNAMICPARTITIONING2_RAM_H

#include "PartitionSpace.h"
#include <list>
#include <queue>
#include <map>
#include <set>
#include <iostream>

using namespace std;

//内存类，抽象类
class RAM {
public:
    int totalSize; //总大小

protected:
    //总进程列表，根据开始时间优先队列
    set<int> processesSet;//所有进程对照表,用于查重
    vector<PartitionSpace> partitionSpacesVector;//分区空间
    vector<int> freePartitionSpacesIndexVector;//空闲分区索引(在子类中实现排序)

public:
    //构造函数，初始化600大小
    RAM(int size=600);

    //更改大小
    void ChangeSize(int size);

    //分配一个进程的内存——已实现
    bool AllocateMemory(int processId, int needSize);
    //根据进程号释放内存——已实现
    bool RecycleMemory(int processId);

    //显示内存分配状态——已实现
    void ShowMemoryStatus();
protected:
    //合并所有空闲分区——已实现
    void mergeFreePartitionSpacesOnce();
    //更新一次空闲分区索引——子类实现
    virtual void updateFreePartitionSpacesIndex() = 0;
    //放入一轮空闲分区
    void putFreePartitionSpacesOnce();
};


#endif //DYNAMICPARTITIONING2_RAM_H
