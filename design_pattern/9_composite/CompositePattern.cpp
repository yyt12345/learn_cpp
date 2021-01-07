#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Component{
public:
    Component(){}
    Component(string iName){
        this->name=iName;
    }

    virtual void add(Component* c)=0;
    virtual void remove(Component* c)=0;
    virtual Component* getChild(int i)=0;
    virtual void operation()=0;
    string getName(){
        return name;
    }
private:
    string name;
};

//叶子构件：办公室office、行政办公室AdminOffice、教务办公室DeanOffice
class Office: public Component{
private:
    string name;
public:
    Office(string iName){
        this->name=iName;
    }
    void add(Component* c){
        cout << "leaf can't add Component" << endl;
    }
    void remove(Component* c){
        cout << "leaf can't remove Component" << endl;
    }
    Component* getChild(int i){
        cout << "leaf don't have child" << endl;
        return nullptr;
    }
    void operation(){
        cout << "-------Office:" << name << endl;
    }
};

class AdminOffice: public Component{
private:
    string name;
public:
    AdminOffice(string iName){
        this->name=iName;
    }
    void add(Component* c){
        cout << "leaf can't add Component" << endl;
    }
    void remove(Component* c){
        cout << "leaf can't remove Component" << endl;
    }
    Component* getChild(int i){
        cout << "leaf don't have child" << endl;
        return nullptr;
    }
    void operation(){
        cout << "-------Administration Office:" << name << endl;
    }
};

class DeanOffice: public Component{
private:
    string name;
public:
    DeanOffice(string iName){
        this->name=iName;
    }
    void add(Component* c){
        cout << "leaf can't add Component" << endl;
    }
    void remove(Component* c){
        cout << "leaf can't remove Component" << endl;
    }
    Component* getChild(int i){
        cout << "leaf don't have child" << endl;
        return nullptr;
    }
    void operation(){
        cout << "-------Dean Office:" << name << endl;
    }
};

//容器构件SubComponent
class SubComponent:public Component{
public:
    SubComponent(string iName){
        this->name=iName;
    }
    void add(Component* c){
        componentList.push_back(c);
    }
    void remove(Component* c){
        for(auto it=componentList.begin();it!=componentList.end();it++){
            if((*it)->getName()==c->getName()){
                componentList.erase(it);
                break;
            }
        }
    }
    Component* getChild(int i){
        return componentList[i];
    }
    void operation(){
        cout << this->name << endl;
        for(auto component:componentList){
            component->operation();
        }
    }
private:
    vector<Component*> componentList;
    string name;
};

int main(){
    Component* head=new SubComponent("总部");
    Component* sichuanOffice =new SubComponent("四川分部");
    Component* office1=new AdminOffice("行政办公室");
    Component* office2=new DeanOffice("教务办公室");

    Component* mianyangOffice=new SubComponent("绵阳分部");
    Component* chengduOffice = new SubComponent("成都分部");
    Component* office3=new AdminOffice("行政办公室");
    Component* office4=new DeanOffice("教务办公室");

    Component* office5=new AdminOffice("行政办公室");
    Component* office6=new DeanOffice("教务办公室");

    Component* office7=new AdminOffice("行政办公室");
    Component* office8=new DeanOffice("教务办公室");

    head->add(office1);
    head->add(office2);
    head->add(sichuanOffice);

    sichuanOffice->add(office3);
    sichuanOffice->add(office4);
    sichuanOffice->add(mianyangOffice);
    sichuanOffice->add(chengduOffice);

    mianyangOffice->add(office5);
    mianyangOffice->add(office6);

    chengduOffice->add(office7);
    chengduOffice->add(office8);

    head->operation();

    return 0;

}
