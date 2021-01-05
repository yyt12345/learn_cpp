#include "PrototypePattern.h"
#include <iostream>

int main(){
    ConcreteWork* singleWork=new ConcreteWork("Single",1001,:"Single_Model");
    cout << "Singel的作业:" << endl;
    singleWork->printWorkInfo();

    ConcreteWork* jungleWork=singleWork;//浅拷贝
    ConcreteWork* jungleWork1=singleWork->clone();//深拷贝
}