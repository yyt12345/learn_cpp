#include <iostream>
#include "BuilderPattern.h"
using namespace std;

int main(){
    House* house;

    Director* director=new Director();
    AbstractBuilder* builder;

    //制定建造者
    builder=new ConcreteBuildA();
    director->setBuilder(builder);
    //指挥者建造房子
    house = director->construct();
    house->printHouseInfo();

    builder=new ConcreteBuildB();
    director->setBuilder(builder);
    house = director->construct();
    house->printHouseInfo();

    return 0;


}