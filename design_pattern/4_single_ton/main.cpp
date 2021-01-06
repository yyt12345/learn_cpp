#include <iostream>
#include "SingleTon.h"
#include <thread>
#include <chrono>

using namespace std;

//单线程
//int main(){
//    Singleton* s1=Singleton::getInstance();
//    Singleton* s2=Singleton::getInstance();
//    //只创建了一次实例
//
//    return 0;
//}

//多线程
void func(int n){
    Singleton* s=Singleton::getInstance();
    this_thread::sleep_for(chrono::seconds(1));
    cout << "线程编号为" << n << endl;
}
int main(){
    thread* t[5];
    int i=0;
    while(i<5){
        t[i]=new thread(func,i);
        i++;
    }
    for(int i=0;i<5;i++)
        t[i]->join();
    return 0;
}