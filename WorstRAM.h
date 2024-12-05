//
// Created by AlexGrandbell on 24-12-5.
//

#ifndef DYNAMICPARTITIONING2_WORSTRAM_H
#define DYNAMICPARTITIONING2_WORSTRAM_H

#include "PartitionSpace.h"
#include "Process.h"
#include <list>
#include <queue>
#include <map>
#include <iostream>

using namespace std;

class WorstRAM {
public:
    int totalSize; //总大小

    //总进程列表，根据开始时间优先队列
    map<int, Process> processesMap;//所有进程对照表
    vector<PartitionSpace> partitionSpacesMap;//分区空间对照表

    WorstRAM(int size=600) : totalSize(size), processesMap() {
        //添加初始化分区到 map
        PartitionSpace partitionSpace = PartitionSpace(0, totalSize);
        partitionSpacesMap.push_back(partitionSpace);
    }

    //分配内存接口
    bool AllocateMemory(Process);
    //释放内存
    void RunOnceAndRecycle(int id);
    //显示内存分配状态
    void ShowMemoryStatus();
    //合并一次空闲分区
    void mergeFreePartitionSpacesOnce();
};


#endif //DYNAMICPARTITIONING2_WORSTRAM_H
