/*
 * 抽象工厂模式实例:
 * Jungle想要进行户外运动，它可以选择打篮球和踢足球。但这次Jungle不想弄脏原本穿的T恤，所以Jungle还需要穿球衣，打篮球就穿篮球衣，踢足球就穿足球衣。篮球保管室可以提供篮球和篮球衣，足球保管室可以提供足球和足球衣。Jungle只要根据心情去某个保管室，就可以换上球衣、拿上球，然后就可以愉快地玩耍了。
 * 抽象产品类：AbstractBall、Shirt
 * 具体产品类：Basketball、Football    BasketballShirt、FootballShirt
 * 抽象工厂：AbstractFactory
 * 具体工厂类：BasketballFactory ShirtFactory
 */
#include <iostream>
using namespace std;
//抽象产品类：AbstractBall、Shirt
class AbstractBall{
public:
    virtual void play()=0;
};

class AbstractShirt{
public:
    virtual void wearShirt()=0;
};

//具体产品类：Basketball、Football    BasketballShirt、FootballShirt
class Basketball: public AbstractBall{
public:
    Basketball(){
        cout << "Jungle get a basketball" << endl;
    }
    void play(){
        cout << "Jungle is playing basketball" << endl;
    }
};

class Football: public AbstractBall{
public:
    Football(){
        cout << "Jungle get a football" << endl;
    }
    void play(){
        cout << "Jungle is playing football" << endl;
    }
};

class BasketballShirt:public AbstractShirt{
public:
    BasketballShirt(){
        wearShirt();
    }
    void wearShirt(){
        cout << "Jungle wear basketball shirt" << endl;
    }
};

class FootballShirt: public AbstractShirt{
public:
    FootballShirt(){
        wearShirt();
    }
    void wearShirt(){
        cout << "Jungle wear football shirt" << endl;
    }
};

//抽象工厂：AbstractFactory
class AbstractFactory{
public:
    virtual AbstractBall* getBall()=0;
    virtual AbstractShirt* getShirt()=0;
};

//具体工厂类：BasketballFactory FootballFactory
class BasketballFactory:public AbstractFactory{
public:
    BasketballFactory(){
        cout << "Basketball Factory" << endl;
    }
    AbstractBall* getBall(){
        return new Basketball();
    }
    AbstractShirt* getShirt(){
        return new BasketballShirt();
    }
};

class FootballFactory:public AbstractFactory{
public:
    FootballFactory(){
        cout << "Football Factory" << endl;
    }
    AbstractBall* getBall(){
        return new Football();
    }
    AbstractShirt* getShirt(){
        return new FootballShirt();
    }
};


//客户端使用方法示例
int main(){
    AbstractBall* ball= nullptr;
    AbstractShirt* shirt= nullptr;
    AbstractFactory* factory= nullptr;

    factory=new BasketballFactory();
    ball=factory->getBall();
    shirt=factory->getShirt();

    factory=new FootballFactory();
    ball=factory->getBall();
    shirt=factory->getShirt();

}