//
// Created by AlexGrandbell on 24-12-5.
//

#ifndef DYNAMICPARTITIONING2_PROCESS_H
#define DYNAMICPARTITIONING2_PROCESS_H


class Process {
public:
    int id; //进程id
    int needSize; //进程大小

    Process(int id, int needSize): id(id), needSize(needSize) {}

    //重载比较时间开始运算符，以便在优先队列中使用
//    bool operator>(const Process &other) const {
//        return createTime> other.createTime;
//    }
//    bool operator<(const Process &other) const {
//        return createTime < other.createTime;
//    }
};


#endif //DYNAMICPARTITIONING2_PROCESS_H
