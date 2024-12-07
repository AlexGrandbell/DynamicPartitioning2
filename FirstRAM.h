//
// Created by AlexGrandbell on 24-12-5.
//

#ifndef DYNAMICPARTITIONING2_FIRSTRAM_H
#define DYNAMICPARTITIONING2_FIRSTRAM_H

#include "RAM.h"

//最先适应法
class FirstRAM: public RAM {
public:
    FirstRAM(int size=600) : RAM(size) {}

protected:
    //更新空闲分区索引
    void updateFreePartitionSpacesIndex() override {
        putFreePartitionSpacesOnce();
    }
};


#endif //DYNAMICPARTITIONING2_FIRSTRAM_H
