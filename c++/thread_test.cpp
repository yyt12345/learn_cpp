#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

const int N=1000000;
int num=0;
mutex m;
void run(){
    for(int i=0;i<N;i++){
//        m.lock();
        num++;
//        m.unlock();
    }
}
int main(){
    clock_t start=clock();
    thread t1(run);
    t1.join();//阻塞当前线程(主线程）直至 *this 所标识的线程结束其执行。
    thread t2(run);
    t2.join();
    clock_t end=clock();
    cout << "num=" << num << ",用时" << end-start << "ms" << endl;
    return 0;
}