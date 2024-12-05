//
// Created by AlexGrandbell on 24-12-5.
//

#include "BestRAM.h"
//最佳适应法
//分配内存接口
bool BestRAM::AllocateMemory(Process process) {
    int minSize = totalSize;
    //遍历分区向量，找到最小合分区
    for (auto &partitionSpace: partitionSpacesMap) {
        if (partitionSpace.isFree && partitionSpace.assignedSize >= process.needSize && partitionSpace.assignedSize < minSize) {
            minSize = partitionSpace.assignedSize;
        }
    }
    //如果找到合适的分区
    if (minSize <= totalSize) {
        //分配内存
        for (auto &partitionSpace: partitionSpacesMap) {
            if (partitionSpace.isFree && partitionSpace.assignedSize == minSize) {
                partitionSpace.isFree = false;
                partitionSpace.processId = process.id;
                //如果分区大小大于进程大小，分割分区，将新的分区放入map，并将编号插入链表
                if (partitionSpace.assignedSize > process.needSize) {
                    PartitionSpace newPartitionSpace = PartitionSpace(partitionSpace.startAddress + process.needSize, partitionSpace.assignedSize - process.needSize);
                    //插入当前的后面
                    auto it = partitionSpacesMap.begin();
                    while (it != partitionSpacesMap.end() && it->startAddress < newPartitionSpace.startAddress) {
                        it++;
                    }
                    partitionSpace.assignedSize = process.needSize;
                    partitionSpacesMap.insert(it, newPartitionSpace);
                    //输出结果
                    ShowMemoryStatus();
                }
                return true;
            }
        }
    }
}

//释放内存
void BestRAM::RunOnceAndRecycle(int id) {
    //遍历所有分区
    for (auto &partitionSpace: partitionSpacesMap) {
        //如果是id的进程则释放
        if (partitionSpace.processId == id) {
            //修改为空白内存
            partitionSpace.isFree = true;
            partitionSpace.processId = -1;
            //合并空闲分区
            mergeFreePartitionSpacesOnce();
            break;
        }
    }
}

//显示内存分配状态
void BestRAM::ShowMemoryStatus() {
    cout << "当前内存分配状态为：" << endl;
    for (auto &partitionSpace: partitionSpacesMap) {
        cout << "分区起始地址：" << partitionSpace.startAddress << "，大小为" << partitionSpace.assignedSize << "，";
        if (partitionSpace.isFree) {
            cout << "空闲" << endl;
        } else {
            cout << "进程" << partitionSpace.processId << "占用" << endl;
        }
    }
    cout << endl;
}

//合并一次空闲分区
void BestRAM::mergeFreePartitionSpacesOnce() {
    //遍历分区表
    for (auto it = partitionSpacesMap.begin(); it != partitionSpacesMap.end(); it++) {
        //如果是空闲分区
        if (it->isFree) {
            //找到下一个分区
            auto nextIt = it;
            nextIt++;
            //如果下一个分区是空闲分区
            if (nextIt != partitionSpacesMap.end() && nextIt->isFree) {
                //合并分区
                it->assignedSize += nextIt->assignedSize;
                //删除下一个分区
                partitionSpacesMap.erase(nextIt);
            }
        }
    }
    ShowMemoryStatus();
}
