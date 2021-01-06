//
// Created by whh on 2021/1/5.
//

#ifndef LEARN_CPP_SINGLETON_H
#define LEARN_CPP_SINGLETON_H

#include <iostream>
#include <string.h>
#include <mutex>
#include <thread>
using namespace std;

class Singleton{
public:
    static Singleton* getInstance(){
        m_mutex.lock();
        if(instance== nullptr){
            cout << "创建新的实例" << endl;
            instance = new Singleton();
        }
        m_mutex.unlock();
        return instance;
    }

private:
    Singleton(){};
    static Singleton* instance;
    static std::mutex m_mutex;
};

Singleton* Singleton::instance = nullptr;//实例对象instance是静态static的，也就是全局的，假设客户端实例化了两个Singleton，但instance只有一个（这就满足了第一个要点）​
std::mutex Singleton::m_mutex;

#endif //LEARN_CPP_SINGLETON_H
