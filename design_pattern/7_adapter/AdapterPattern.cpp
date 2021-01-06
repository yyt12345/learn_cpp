/*
 * 适配器模式代码
 * 目标抽象类:Controller
 * 适配者类:DxfParser和PathPlanner
 * 适配者类（Adaptee）：适配器与适配者之间是关联关系
 *
 *
 */
#include <iostream>
using namespace std;
class Controller{
public:
    Controller(){}
    virtual void pathPlanning()=0;
};
class DxfParser{
public:
    DxfParser(){}
    void parseFile(){
        cout << "已成功读取文件" << endl;
    }
};
class PathPlanner{
public:
    PathPlanner(){}
    void calculate(){
        cout << "计算加工路径" << endl;
    }
};

class Adapter: public Controller{
private:
    DxfParser *dxfParser;
    PathPlanner* pathPlanner;
public:
    void pathPlanning(){
        dxfParser=new DxfParser();
        pathPlanner=new PathPlanner();
        dxfParser->parseFile();
        pathPlanner->calculate();
    }
};

int main(){
    Controller* controller = new Adapter();
    controller->pathPlanning();

    return 0;
}