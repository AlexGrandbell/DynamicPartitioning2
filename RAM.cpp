//
// Created by AlexGrandbell on 24-12-7.
//

#include "RAM.h"

//构造函数，初始化600大小
RAM::RAM(int size) : totalSize(size) {
    //添加初始化分区到 map
    PartitionSpace partitionSpace = PartitionSpace(0, totalSize);
    partitionSpacesVector.push_back(partitionSpace);
    //直接初始化空闲分区索引
    putFreePartitionSpacesOnce();
}

//更改大小
void RAM::ChangeSize(int size) {
    //安全性检查
    if (size<=0){
        size=600;
    }
    totalSize = size;
    partitionSpacesVector[0].assignedSize = totalSize;
}

//分配一个进程的内存
bool RAM::AllocateMemory(int processId, int needSize) {
    //查看进程id是否重复
    if(processesSet.find(processId) != processesSet.end()) {
        cout<<"错误: 该进程已存在"<<endl;
        return false;
    }
    //空闲分区索引在子类中实现排序，这里不断尝试前面的大小是否满足
    for(auto &partitionSpaceIndex: freePartitionSpacesIndexVector) {
        if (partitionSpacesVector[partitionSpaceIndex].assignedSize >= needSize) {
            //进程id加入集合
            processesSet.insert(processId);
            //分配内存
            partitionSpacesVector[partitionSpaceIndex].isFree = false;
            partitionSpacesVector[partitionSpaceIndex].processId = processId;
            //如果分区大小大于进程大小，分割分区，将新的分区放入map，并将编号插入链表
            if (partitionSpacesVector[partitionSpaceIndex].assignedSize > needSize) {
                PartitionSpace newPartitionSpace = PartitionSpace(
                        partitionSpacesVector[partitionSpaceIndex].startAddress + needSize,
                        partitionSpacesVector[partitionSpaceIndex].assignedSize - needSize);
                //插入当前的后面
                auto it = partitionSpacesVector.begin();
                while (it != partitionSpacesVector.end() && it->startAddress < newPartitionSpace.startAddress) {
                    it++;
                }
                partitionSpacesVector[partitionSpaceIndex].assignedSize = needSize;
                partitionSpacesVector.insert(it, newPartitionSpace);
            }
            //更新空闲分区索引
            updateFreePartitionSpacesIndex();
            return true;
        }
    }
    //寻找最大的空闲分区大小
    int maxFreeSize = 0;
    for(auto &freePartitionSpacesIndex: freePartitionSpacesIndexVector) {
        if(partitionSpacesVector[freePartitionSpacesIndex].assignedSize > maxFreeSize) {
            maxFreeSize = partitionSpacesVector[freePartitionSpacesIndex].assignedSize;
        }
    }
    cout<<"失败: 没有找到合适的分区放入此进程，此进程需要"<<needSize<<"的内存空间,而最大的空闲分区大小为"<<maxFreeSize<<endl;
    return false;//没有找到合适的分区大小而失败
}

//根据进程号释放内存
bool RAM::RecycleMemory(int processId) {
    //id是否存在
    if(processesSet.find(processId) == processesSet.end()) {
        cout<<"错误: 该进程不存在"<<endl;
        return false;
    }
    //遍历所有分区
    for(auto &partitionSpace: partitionSpacesVector) {
        //如果是id的进程则释放
        if(partitionSpace.processId == processId) {
            //修改为空白内存
            partitionSpace.isFree = true;
            partitionSpace.processId = -1;
            //合并空闲分区，包含更新空闲分区索引
            mergeFreePartitionSpacesOnce();
            //从集合中删除id
            processesSet.erase(processId);
            return true;
        }
    }
    return false;//不会执行到这里其实
}

//显示内存分配状态
void RAM::ShowMemoryStatus() {
    cout<<"当前内存分配状态为："<<endl;
    cout<<"分区序号:\t";
    for(int i=0; i < partitionSpacesVector.size(); i++) {
        cout<<i<<"\t";
    }
    cout<<"\n起始地址:\t";
    for(auto &partitionSpace: partitionSpacesVector) {
        cout << partitionSpace.startAddress << "\t";
    }
    cout<<"\n分区大小:\t";
    for(auto &partitionSpace: partitionSpacesVector) {
        cout << partitionSpace.assignedSize << "\t";
    }
    cout<<"\n结束地址:\t";
    for(auto &partitionSpace: partitionSpacesVector) {
        cout << partitionSpace.startAddress + partitionSpace.assignedSize - 1 << "\t";
    }
    cout<<"\n分区状态:\t";
    for(auto &partitionSpace: partitionSpacesVector) {
        cout << (partitionSpace.isFree ? "空" : "有" ) << "\t";
    }
    cout<<"\n进程编号:\t";
    for(auto &partitionSpace: partitionSpacesVector) {
        if (partitionSpace.isFree) {
            cout<<"-\t";
        }else{
            cout << partitionSpace.processId << "\t";
        }
    }
    cout<<endl;
}

//合并所有空闲分区
void RAM::mergeFreePartitionSpacesOnce() {
    //遍历分区索引，找到相邻的空闲分区
    for(auto it = partitionSpacesVector.begin(); it != partitionSpacesVector.end(); it++) {
        //如果是空闲分区
        if(it->isFree) {
            //找到下一个分区
            auto nextIt = it;
            nextIt++;
            //如果下一个分区是空闲分区
            if(nextIt != partitionSpacesVector.end() && nextIt->isFree) {
                //合并分区
                it->assignedSize += nextIt->assignedSize;
                //删除下一个分区
                partitionSpacesVector.erase(nextIt);
                //防止漏掉
                it--;
            }
        }
    }
    //更新空闲分区索引
    updateFreePartitionSpacesIndex();
}

//放入一轮空闲分区
void RAM::putFreePartitionSpacesOnce() {
    freePartitionSpacesIndexVector.clear();
    for (int i = 0; i < partitionSpacesVector.size(); i++) {
        if (partitionSpacesVector[i].isFree) {
            freePartitionSpacesIndexVector.push_back(i);
        }
    }
}