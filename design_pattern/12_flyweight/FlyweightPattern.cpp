#include <iostream>
#include <string>
#include <mutex>
#include <vector>
using namespace std;

class NetDevice{
public:
    NetDevice(){}
    virtual string getName()=0;
    void print(){
        cout << "NetDevice:" << getName() << endl;
    }
};

class Switch: public NetDevice{
public:
    Switch(){}
    string getName(){
        return "交换机";
    }
};

class Hub: public NetDevice{
public:
    Hub(){}
    string getName(){
        return "集线器";
    }
};

//享元工厂类
class NetDeviceFactory{
public:
    NetDevice* getNetDevice(char ch){
        if(ch=='S')
            return devicePool[1];
        else if(ch=='H')
            return devicePool[0];
        else
            cout << "error input" << endl;
        return nullptr;
    }
    static NetDeviceFactory* getFactory(){
        if(instance== nullptr){
            mutex_m.lock();
            if(instance== nullptr)
                instance = new NetDeviceFactory();
            mutex_m.unlock();
        }
        return instance;
    }
private:
    //单例————私有化构造函数
    NetDeviceFactory(){
        Hub* hub=new Hub();
        Switch* switcher=new Switch();
        devicePool.push_back(hub);
        devicePool.push_back(switcher);
    }
    static mutex mutex_m;
    static NetDeviceFactory* instance;
    vector<NetDevice*> devicePool;//享元池
};

NetDeviceFactory* NetDeviceFactory::instance= nullptr;
mutex NetDeviceFactory::mutex_m;

int main(){
    NetDeviceFactory* factory=NetDeviceFactory::getFactory();

    NetDevice *device1,*device2,*device3,*device4;

    device1=factory->getNetDevice('H');
    device1->print();

    device2=factory->getNetDevice('H');
    device2->print();

    cout << "判断两个hub是否为同一个" << endl;
    cout << device1 << " and " << device2 << endl;


}

