//
// Created by whh on 2021/1/4.
//
/*
 *  简单工厂模式代码实例:
 *  Jungle想要进行户外运动，它可以选择打篮球、踢足球或者玩排球。它需要凭票去体育保管室拿，票上写着一个具体球类运动的名字，比如“篮球”。体育保管室负责人根据票上的字提供相应的体育用品。然后Jungle就可以愉快地玩耍了。
 *  具体产品：篮球、足球和排球
 *  抽象产品：运动球类产品SportProduct
 */
#include <iostream>
#include <string>
using namespace std;
//抽象产品类AbstractProduct
class AbstractSportProduct{
public:
    AbstractSportProduct(){

    }
    //抽象方法
    void printName(){};
    void play(){};
};

//具体产品类
class Basketball: public AbstractSportProduct{
public:
    Basketball(){
        printName();
        play();
    }
    //具体实现方法
    void printName(){
        std::cout << "Jungle get Basketball" << std::endl;
    }
    void play() {
        std::cout << "Jungle is playing Basketball" << std::endl;
    }
};

class Football: public AbstractSportProduct{
public:
    Football(){
        printName();
        play();
    }
    void printName(){
        std::cout << "Jungle get Football" << std::endl;
    }
    void play(){
        std::cout << "Jungle is playing Football" << std::endl;
    }
};

class Volleyball: public AbstractSportProduct{
public:
    Volleyball(){
        printName();
        play();
    }
    void printName(){
        std::cout << "Jungle get Volleyball" << std::endl;
    }
    void play(){
        std::cout << "Jungle is playing Volleyball" << std::endl;
    }
};

class Factory{
public:
    AbstractSportProduct *getSportProduct(std::string productName){
        AbstractSportProduct *pro= nullptr;
        if(productName=="Basketball") pro=new Basketball();
        if(productName=="Football") pro=new Football();
        if(productName=="Volleyball") pro=new Volleyball();
        return pro;
    }
};

//客户端使用方法示例
int main(){
    std::cout << "简单工厂模式" << std::endl;

    Factory* factory=new Factory();
    AbstractSportProduct* product= nullptr;
    product=factory->getSportProduct("Basketball");
    product=factory->getSportProduct("Football");
    product=factory->getSportProduct("Volleyball");

    system("pause");
    return 0;
}

