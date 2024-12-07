//
// Created by AlexGrandbell on 24-12-5.
//

#ifndef DYNAMICPARTITIONING2_WORSTRAM_H
#define DYNAMICPARTITIONING2_WORSTRAM_H

#include "RAM.h"

using namespace std;

//最坏适应法
class WorstRAM: public RAM {
public:
    WorstRAM(int size=600) : RAM(size) {}

protected:
    //更新空闲分区索引
    void updateFreePartitionSpacesIndex() override {
        putFreePartitionSpacesOnce();
        //按大小排序
        sort(freePartitionSpacesIndexVector.begin(), freePartitionSpacesIndexVector.end(), [this](int a, int b) {
            return partitionSpacesVector[a].assignedSize > partitionSpacesVector[b].assignedSize;
        });
    }
};


#endif //DYNAMICPARTITIONING2_WORSTRAM_H
