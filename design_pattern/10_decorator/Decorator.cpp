#include <iostream>
using namespace std;

class Component{
public:
    Component(){}
    virtual void operation()=0;
};

class Phone: public Component{
public:
    Phone(){}
    void operation(){
        cout << "手机" << endl;
    }
};

class Decorator: public Component{
private:
    Component* component;
public:
    void setComponent(Component* c){
        this->component=c;
    }
    Component* getComponent(){
        return this->component;
    }
    void operation(){
        this->component->operation();
    }
};

class DecoratorShell: public Decorator{
public:
    DecoratorShell(){}
    DecoratorShell(Component* c){
        this->setComponent(c);
    }
    void newBehavior(){
        cout << "装手机壳" << endl;
    }
    void operation(){
        this->getComponent()->operation();
        this->newBehavior();
    }
};

class DecoratorSticker: public Decorator{
public:
    DecoratorSticker(){}
    DecoratorSticker(Component* c){
        this->setComponent(c);
    }
    void newBehavior(){
        cout << "贴卡通贴纸" << endl;
    }
    void operation(){
        this->getComponent()->operation();
        this->newBehavior();
    }
};

class DecoratorRope: public Decorator{
public:
    DecoratorRope(){}
    DecoratorRope(Component* c){
        this->setComponent(c);
    }
    void newBehavior(){
        cout << "挂手机挂绳" << endl;
    }
    void operation(){
        this->getComponent()->operation();
        this->newBehavior();
    }
};

int main(){
    cout << "第一个手机" << endl;
    Component* c=new Phone();
    Component* com_Shell=new DecoratorShell(c);
    com_Shell->operation();

    cout << "第二个手机" << endl;
    Component* c2=new Phone();
    Component* com_Shell2=new DecoratorShell(c2);
    Component* com_Sticker=new DecoratorSticker(com_Shell2);
    com_Sticker->operation();

    cout << "第三个手机" << endl;
    Component* com_Rope=new DecoratorRope(com_Shell2);
    com_Rope->operation();
}