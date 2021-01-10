#include <iostream>
#include <string>
#include <mutex>
#include <vector>
using namespace std;

class NetDevice{
public:
    NetDevice(){}
    virtual string getName()=0;
    virtual void print()=0;
};

class Switch:public NetDevice{
public:
    static Switch* getSwitch(){
        if(instance2== nullptr){
            mutex_m2.lock();
            if(instance2== nullptr){
                instance2=new Switch();
                cout << "创建一个Switch" << endl;
            }
            mutex_m2.unlock();
        }else{
            cout << "Switch已经被创建了" << endl;
        }
        return instance2;
    }
    string getName(){
        return "交换机";
    }
    void print(){
        cout << "NetDevice:" << getName() << endl;
    }
private:
    Switch(){}
    static Switch* instance2;
    static mutex mutex_m2;
};

class Hub: public NetDevice{
public:
    static Hub* getHub(){
        if(instance == nullptr){
            mutex_m.lock();
            if(instance == nullptr){
                instance=new Hub();
                cout << "创建一个Hub" << endl;
            }
            mutex_m.unlock();
        }else{
            cout << "Hub已经被创建了" << endl;
        }
        return instance;
    }
    string getName(){
        return "集线器";
    }
    void print(){
        cout << "NetDevice:" << getName() << endl;
    }
private:
    Hub(){}
    static Hub* instance;
    static mutex mutex_m;
};


Switch* Switch::instance2= nullptr;
mutex Switch::mutex_m2;
Hub* Hub::instance= nullptr;
mutex Hub::mutex_m;

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
    NetDeviceFactory(){
        Switch* switcher=Switch::getSwitch();
        Hub* hub =Hub::getHub();
        devicePool.push_back(hub);
        devicePool.push_back(switcher);
    }
private:
    vector<NetDevice*> devicePool;//享元池
};


int main(){
    cout << "start" << endl;
    NetDeviceFactory* factory=new NetDeviceFactory();

    NetDevice *device1,*device2,*device3,*device4;

    device1=factory->getNetDevice('H');
    device1->print();
    device2=factory->getNetDevice('S');
    device2->print();

    NetDeviceFactory* factory2=new NetDeviceFactory();
    device3=factory2->getNetDevice('H');
    device4=factory2->getNetDevice('S');
    device3->print();
    device4->print();




}

