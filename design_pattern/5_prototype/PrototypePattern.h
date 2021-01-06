class WorkModel{
public:
    char* modelName;
    void setWorkModelName(char* iName){
        this->modelName=iName;
    }
};

//抽象原型类PrototypeWork
class PrototypeWork{
public:
    PrototypeWork(){};
    virtual PrototypeWork* clone()=0;
};

//具体原型类ConcreteWork
class ConcreteWork: public PrototypeWork{
public:
    ConcreteWork(){}
    ConcreteWork(char* iName,int iIdNum,char* modelName){
        this->name=iName;
        this->idNum=iIdNum;
        this->workModel=new WorkModel();
        this->workModel->setWorkModelName(modelName);
    }
    ConcreteWork* clone(){
        ConcreteWork* work=new ConcreteWork();
        work->setName(this->name);
        work->setIdNum(this->idNum);
        work->setModel(this->workModel);
        return work;
    }
    void setName(char* iName){
        this->name=iName;
    }
    void setIdNum(char* iIdNum){
        this->idNum=iIdNum;
    }
//    深拷贝
    void setModel(WorkModel* iWorkModel){
        this->workModel=new WorkModel();
        this->workModel->setWorkModelName(iWorkModel->modelName);
    }
    void printWorkInfo(){
        cout << "name:" << this->name << endl;
        cout << "idNum:" << this->idNum << endl;
        cout << "modelName:" << this->workModel->modelName << endl;
    }

private:
    char* name;
    int idNum;
    WorkModel* workModel;
};