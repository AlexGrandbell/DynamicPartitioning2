
#include "FirstRAM.h"
#include "BestRAM.h"
#include "WorstRAM.h"


int main() {
    int mode=1;//1-最先适应法 2-最佳适应法 3-最坏适应法
    int RAMSize=600;//内存大小
    FirstRAM firstRAM = FirstRAM();
    BestRAM bestRAM = BestRAM();
    WorstRAM worstRAM = WorstRAM();


    int choice;
    while (true) {
        cout<<"\n当前算法: ";
        switch (mode) {
            case 1:
                cout<<"最先适应法"<<endl;
                break;
            case 2:
                cout<<"最佳适应法"<<endl;
                break;
            default:
                cout<<"最坏适应法"<<endl;
                break;
        }
        cout<<"当前内存大小: "<<RAMSize<<"KB"<<endl;
        cout<<"/**---------菜单---------**\\"<<endl;
        cout << "1.选择算法" << endl;
        cout << "2.设置内存大小"<<endl;
        cout << "3.申请内存" << endl;
        cout << "4.释放内存" << endl;
        cout << "5.展示内存" << endl;
        cout << "0.退出" << endl;
        cout<<"/-**------菜单结束-------**\\"<<endl;
        cout << "请选择:";
        cin >> choice;
        switch (choice) {
            case 1:
            {
                cout << "请选择算法(1-最先适应法 2-最佳适应法 3-最坏适应法):";
                cin >> mode;
                break;
            }
            case 2:
            {
                cout << "请输入内存大小:";
                cin >> RAMSize;
                break;
            }
            case 3:
            {
                cout << "请输入进程id:";
                int id;
                cin >> id;
                cout << "请输入进程大小:";
                int needSize;
                cin >> needSize;

                switch (mode) {
                    case 1:
                        firstRAM.AllocateMemory(Process(id, needSize));
                        break;
                    case 2:
                        bestRAM.AllocateMemory(Process(id, needSize));
                        break;
                    case 3:
                        worstRAM.AllocateMemory(Process(id, needSize));
                        break;
                    default:
                        cout << "输入错误，请重新输入" << endl;
                }
                break;
            }
            case 4:
            {
                cout << "请输入进程id:";
                int id;
                cin >> id;
                switch (mode) {
                    case 1:
                        firstRAM.RunOnceAndRecycle(id);
                        break;
                    case 2:
                        bestRAM.RunOnceAndRecycle(id);
                        break;
                    case 3:
                        worstRAM.RunOnceAndRecycle(id);
                        break;
                    default:
                        cout << "输入错误，请重新输入" << endl;
                }
                break;
            }
            case 5:
            {
                switch (mode) {
                    case 1:
                        firstRAM.ShowMemoryStatus();
                        break;
                    case 2:
                        bestRAM.ShowMemoryStatus();
                        break;
                    case 3:
                        worstRAM.ShowMemoryStatus();
                        break;
                    default:
                        cout << "输入错误，请重新输入" << endl;
                }
                break;
            }
            case 0:
                return 0;
            default:
                cout << "输入错误，请重新输入" << endl;
        }
    }
    return 0;
};

