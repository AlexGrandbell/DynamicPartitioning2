//
// Created by AlexGrandbell on 24-12-5.
//

#ifndef DYNAMICPARTITIONING2_PARTITIONSPACE_H
#define DYNAMICPARTITIONING2_PARTITIONSPACE_H

//分区空间类
class PartitionSpace {
public:
    int startAddress; //起始地址
    int assignedSize; //分区大小
    bool isFree; //是否空闲
    int processId; //进程id

    PartitionSpace(int startAddress, int assignedSize): startAddress(startAddress), assignedSize(assignedSize), isFree(true), processId(-1){}

};


#endif //DYNAMICPARTITIONING2_PARTITIONSPACE_H
