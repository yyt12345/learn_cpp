//
// Created by whh on 2021/1/5.
//

#ifndef LEARN_CPP_BUILDERPATTERN_H
#define LEARN_CPP_BUILDERPATTERN_H

#include <string>
using namespace std;

//产品类House
class House{
private:
    string floor;
    string wall;
    string roof;
public:
    void setFloor(string iFloor){
        this->floor=iFloor;
    }
    void setWall(string iWall){
        this->wall=iWall;
    }
    void setRoof(string iRoof){
        this->roof=iRoof;
    }
    void printHouseInfo(){
        cout << "Floor:" << this->floor << endl;
        cout << "Wall:" << this->wall << endl;
        cout << "Roof:" << this->roof << endl;
    }
};

//抽象建造者AbstractBuilder
class AbstractBuilder{
public:
    AbstractBuilder(){
        house = new House();
    }
    House* house;
    virtual void buildFloor()=0;
    virtual void buildWall()=0;
    virtual void buildRoof()=0;
    virtual House* getHouse()=0;
};

//具体建造者ConcreteBuilderA ConcreteBuildB
class ConcreteBuildA : public AbstractBuilder{
public:
    ConcreteBuildA(){
        cout << "ConcreteBuildA" << endl;
    }
    void buildFloor(){
        this->house->setFloor("Floor_A");
    }
    void buildWall(){
        this->house->setWall("Wall_A");
    }
    void buildRoof(){
        this->house->setRoof("Root_A");
    }
    House* getHouse(){
        return this->house;
    }
};

class ConcreteBuildB : public AbstractBuilder{
public:
    ConcreteBuildB(){
        cout << "ConcreteBuildA" << endl;
    }
    void buildFloor(){
        this->house->setFloor("Floor_B");
    }
    void buildWall(){
        this->house->setWall("Wall_B");
    }
    void buildRoof(){
        this->house->setRoof("Root_B");
    }
    House* getHouse(){
        return this->house;
    }
};

//指挥者（Director）
class Director{
private:
    AbstractBuilder* builder;
public:
    Director(){}
    void setBuilder(AbstractBuilder* iBuilder){
        this->builder=iBuilder;
    }
    House* construct(){
        this->builder->buildFloor();
        this->builder->buildWall();
        this->builder->buildRoof();
        return this->builder->getHouse();
    }
};

#endif //LEARN_CPP_BUILDERPATTERN_H
