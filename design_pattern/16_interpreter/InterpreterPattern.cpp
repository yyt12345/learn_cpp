/* 
 * 终结符表达式角色：值节点
 * 终结符表达式：运算符节点
 * 非终结符表达式：句子节点  （句子节点有 左值节点+运算符节点+右值节点）
 * 上下文类角色：处理器
 *
 */

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

class AbstractNode{
public:
	AbstractNode(){}
	virtual char interpret()=0;	
};

class ValueNode:public AbstractNode{
private:
	int value;
public:
	ValueNode(){}
	ValueNode(int iValue){
		this->value=iValue;
	}
	char interpret(){
		return value;
	}
};

class OperatorNode:public AbstractNode{
private:
	string op;
public:
	OperatorNode(){}
	OperatorNode(string iOp){
		this->op=iOp;
	}
	char interpret(){
		if(op=="or")
			return '|';
		else if(op=="and")
			return '&';
	}
};

class SentenceNode:public AbstractNode{
private:
	AbstractNode* leftNode,*rightNode,*operatorNode;
public:
	SentenceNode(){}
	SentenceNode(AbstractNode* left,AbstractNode* operators,AbstractNode* right){
		this->leftNode=left;
		this->operatorNode=operators;
		this->rightNode=right;
	}
	char interpret(){
		if(operatorNode->interpret()=='|'){
			return leftNode->interpret() | rightNode->interpret();
		}else if(operatorNode->interpret()=='&')
			return leftNode->interpret() & rightNode->interpret();
		return 0;
	}

};

class Handler{
private:
	string input;
	char result;
public:
	Handler(){}
	void setInput(string iInput){
		this->input=iInput;
	}
	void handle(){
		AbstractNode *left=nullptr;
		AbstractNode* right=nullptr;
		AbstractNode* op=nullptr;
		AbstractNode* sentence=nullptr;
		string iInput=this->input;
		vector<string> inputList;
		char* inputCh=const_cast<char*>(iInput.c_str());
		char* token=strtok(inputCh," ");
		while(token!=nullptr){
			inputList.push_back(token);
			token=strtok(nullptr," ");
		}
		for(int i=0;i<inputList.size()-2;i+=2){
			left=new ValueNode(*(inputList[i].c_str()));
			op=new OperatorNode(inputList[i+1]);
			right=new ValueNode(*(inputList[i+2].c_str()));
			sentence =new SentenceNode(left,op,right);
			inputList[i+2]=string(1,sentence->interpret());
		}
		string tmpRes=inputList[inputList.size()-1];
		if(tmpRes=="1")	result='1';
		else if(tmpRes=="0") result='0';
		else result =-1;

		this->output();
	}
	void output(){
		cout << input << "=" << result << endl;
	}
}; 

int main(){

	Handler *handler = new Handler();

	string input_1 = "1 and 1";
	string input_2 = "1 and 0";
	string input_3 = "0 and 1";
	string input_4 = "0 and 0";
	string input_5 = "0 or 0";
	string input_6 = "0 or 1";
	string input_7 = "1 or 0";
	string input_8 = "1 or 1";
	string input_9 = "1 and 0 or 1";
	string input_10 = "0 or 0 and 1";
	string input_11 = "1 or 1 and 1 and 0";
	string input_12 = "0 and 1 and 1 and 1";
	string input_13 = "0 and 1 and 1 and 1 or 1 or 0 and 1";
	handler->setInput(input_1); handler->handle();
	handler->setInput(input_2); handler->handle();
	handler->setInput(input_3); handler->handle();
	handler->setInput(input_4); handler->handle();
	handler->setInput(input_5); handler->handle();
	handler->setInput(input_6); handler->handle();
	handler->setInput(input_7); handler->handle();
	handler->setInput(input_8); handler->handle();
	handler->setInput(input_9); handler->handle();
	handler->setInput(input_10); handler->handle();
	handler->setInput(input_11); handler->handle();
	handler->setInput(input_12); handler->handle();
	handler->setInput(input_13); handler->handle();

	printf("\n\n");
	system("pause");

}
