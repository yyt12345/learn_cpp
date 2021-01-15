#include <iostream>
#include <string>

using namespace std;

class Bill{
private:
    int id;
    string name;
    double account;
public:
    Bill(){}
    Bill(int iId,string iName,double iAccount){
        this->id=iId;
        this->name=iName;
        this->account=iAccount;
    }
    double getAccount(){
        return this->account;
    }
    void print(){
        cout << "ID: " << id;
        cout << " Name: " << name;
        cout << " Account: " << account << endl;
    }
};

class Approver{
public:
    Approver(){}
    Approver(string iName){
        setName(iName);
    }
    void setSuperior(Approver* iSuperior){
        this->superior=iSuperior;
    }
    string getName(){
        return name;
    }
    void setName(string iName){
        this->name=iName;
    }
    virtual void handleRequest(Bill* bill)=0;

protected:
    Approver* superior;
private:
    string name;
};

// 具体处理者：组长
class GroupLeader:public Approver{
public:
    GroupLeader(){}
    GroupLeader(string iName){
        setName(iName);
    }
    void handleRequest(Bill* bill){
        if(bill->getAccount()<10){
            cout << "组长" << getName() << "处理了该票据，票据信息：";
            bill->print();
        }else{
            cout << "组长无权处理，转交上级……" << endl;
            superior->handleRequest(bill);
        }
        return;
    }
};

// 具体处理者：主管
class Head:public Approver{
public:
    Head(){}
    Head(string iName){
        setName(iName);
    }
    void handleRequest(Bill* bill){
        if(bill->getAccount()<30){
            cout << "组长" << getName() << "处理了该票据，票据信息：";
            bill->print();
        }else{
            cout << "组长无权处理，转交上级……" << endl;
            superior->handleRequest(bill);
        }
    }
};

//经理
class Manager:public Approver{
public:
    Manager(string iName){
        setName(iName);
    }
    void handleRequest(Bill* bill){
        if(bill->getAccount()<60){
            cout << "组长" << getName() << "处理了该票据，票据信息：";
            bill->print();
        }else{
            cout << "组长无权处理，转交上级……" << endl;
            superior->handleRequest(bill);
        }
    }
};

class Boss:public Approver{
public:
    Boss(string iName){
        setName(iName);
    }
    void handleRequest(Bill* bill){
        cout << "组长" << getName() << "处理了该票据，票据信息：";
        bill->print();
    }
};

int main(){
    Approver *zuzhang=new GroupLeader("孙大哥");
    Approver *bingge=new Head("兵哥");
    Approver *chunzong=new Manager("春总");
    Approver *laoban=new Boss("张老板");

    zuzhang->setSuperior(bingge);
    bingge->setSuperior(chunzong);
    chunzong->setSuperior(laoban);

    Bill *bill1=new Bill(1,"Jungle",8);
    Bill *bill2=new Bill(2,"Lucy",14.2);
    Bill *bill3=new Bill(3,"Jack",35);
    Bill *bill4=new Bill(4,"Tom",93);

    zuzhang->handleRequest(bill1);
    zuzhang->handleRequest(bill2);
    zuzhang->handleRequest(bill3);
    zuzhang->handleRequest(bill4);

    return 0;
}