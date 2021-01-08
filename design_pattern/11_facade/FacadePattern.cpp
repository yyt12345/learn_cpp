/*
 * 子系统类:Memory、CPU、HardDisk和OS
 * 外观类(Facade):
 */
#include <iostream>
using namespace std;
//子系统：Memory
class Memory{
public:
    Memory(){}
    void selfCheck(){
        cout << "---------内存自检--------" << endl;
    }
};
// 子系统：CPU
class CPU{
public:
    CPU(){}
    void run(){
        cout << "---------运行CPU---------" << endl;
    }
};

class HardDisk{
public:
    void read(){
        cout << "-----------读取硬盘--------" << endl;
    }
};

class OS{
public:
    void load(){
        cout << "------------载入操作系统------" << endl;
    }
};

class Facade{
public:
    Facade(){
        memory=new Memory();
        cpu=new CPU();
        hardDisk=new HardDisk();
        os=new OS();
    }
    void powerOn(){
        memory->selfCheck();
        cpu->run();
        hardDisk->read();
        os->load();
    }
private:
    Memory* memory;
    CPU* cpu;
    HardDisk* hardDisk;
    OS* os;
};

int main(){
    Facade* facade=new Facade();
    facade->powerOn();
}