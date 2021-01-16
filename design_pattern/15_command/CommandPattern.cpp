/*
 * 命令模式
 * 描述：房间中的开关（Button）就是命令模式的一个实现，本例使用命令模式来模拟开关功能，可控制的对象
 *      包括电灯（Lamp）和风扇（Fan）。用户每次触摸（touch）开关，都可以打开或者关闭电灯或者电扇。
 * 调用者：Button
 * 具体命令类：LampCommand FanCommand （将接收者（Receiver）的动作action()绑定其中）
 * 接收者：Lamp Fan
 */
#include <iostream>
using namespace std;
class Command{
public:
    Command(){}
    virtual void execute()=0;
};

class Lamp{
private:
    bool lanpState;
public:
	Lamp():lanpState(false){}
    void on(){
	lanpState=true;
        cout << "打开灯" << endl;
    }

    void off(){
	lanpState=false;
    	cout << "关上灯" << endl;
    }
    bool getLampState(){
    	return lanpState;
    }
};

class Fan{
private:
	bool fanState;
public:
	Fan():fanState(false){}
	void on(){
		fanState=true;
		cout << "打开风扇" << endl;
	}
	void off(){
		fanState=false;
		cout << "关上风扇" << endl;
	}	
	bool getFanState(){
		return fanState;
	}
};

class LampCommand:public Command{
private:
	Lamp* lamp;
public:
	LampCommand(){
		lamp=new Lamp();		
	}
	void execute(){
		if(lamp->getLampState())
			lamp->off();
		else
			lamp->on();
	}

};


class FanCommand:public Command{
private:
	Fan* fan;
public:
	FanCommand(){
		fan=new Fan();	
	}
	void execute(){
		if(fan->getFanState())
			fan->off();
		else 
			fan->on();
	}
};

class Button{
private:
	Command* command;
public:
	Button(){}
	void setCommand(Command* cmd){
		this->command=cmd;
	}
	void touch(){
		command->execute();
	}
};

int main(){
	Button* button1=new Button();
	Button* button2=new Button();

	button1->setCommand(new LampCommand());
	button2->setCommand(new FanCommand());

	button1->touch();
	button1->touch();
	button1->touch();
	button2->touch();

	return 0;
}
