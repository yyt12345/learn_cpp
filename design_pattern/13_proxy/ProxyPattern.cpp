#include <iostream>
#include <time.h>

using namespace std;

class Subject{
public:
    virtual void method()=0;
};

class RealSubject{
public:
    void method(){
        cout << "调用业务方法" << endl;
    }
};

class Log{
public:
    Log(){}
    string getTime(){
        time_t t=time(nullptr);
        char ch[64]={0};
        strftime(ch,sizeof(ch)-1,"%Y-%m-%d %H:%M:%S",localtime(&t));
        return ch;
    }
};

class Proxy: public Subject{
private:
    RealSubject* realSubject;
    Log* log;
public:
    Proxy(){
        realSubject= new RealSubject();
        log = new Log();
    }
    void preCallMethod(){
        cout << "方法method()被调用，调用时间" << log->getTime().c_str();
    }
    void method(){
        preCallMethod();
        realSubject->method();
        postCallMethod();
    }
    void postCallMethod(){
        cout << "方法method()调用成功" << endl;
    }
};

int main(){
    Subject* subject;
    subject=new Proxy();
    subject->method();

    return 0;
}