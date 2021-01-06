#include <iostream>
using namespace std;
//抽象产品Logger
class Logger{
public:
    Logger(){};
    void writeLog(){};
};

//具体产品
class FileLogger: public Logger{
public:
    FileLogger(){
        writeLog();
    }
    void writeLog(){
        std::cout << "文件日志记录" << endl;
    }
};

class DatabaseLogger : public Logger{
public:
    DatabaseLogger(){
        writeLog();
    }
    void writeLog(){
        cout << "数据库日志记录" << endl;
    }
};

//抽象工厂LoggerFactory
//只有将其定义为抽象类，才能引用到子类方法中
class LoggerFactory{
public:
    virtual Logger* createLogger()=0;
};

//具体工厂
class FileLoggerFactory: public LoggerFactory{
public:
    FileLoggerFactory(){
        cout << "File Logger Factory" << endl;
//        createLogger();
    }
    Logger* createLogger(){
        //创建文件日志记录器对象
        return new FileLogger();
    }
};

class DatabaseLoggerFactory:public LoggerFactory{
public:
    DatabaseLoggerFactory(){
        cout << "Database Logger Factory" << endl;
//        createLogger();
    }
    Logger* createLogger(){
        return new DatabaseLogger();
    }
};

//客户端测试代码
int main(){
    LoggerFactory* factory= nullptr;
    Logger* logger= nullptr;

    factory = new FileLoggerFactory();
    logger=factory->createLogger();

    factory =  new DatabaseLoggerFactory();
    logger = factory->createLogger();

}

