#thread类

C++11 新标准中引入了四个头文件来支持多线程编程，他们分别是<atomic> ,<thread>,<mutex>,<condition_variable>和<future>。

##std::thread 构造
1. 默认构造函数，创建一个空的 thread 执行对象。
   
   `thread t;`
2. 初始化构造函数，创建一个 thread对象，该 thread对象可被 joinable，新产生的线程会调用 fn 函数，该函数的参数由 args 给出。
   
    `thread t(function);`
```c++
// thread example  
#include <iostream>       // std::cout  
#include <thread>         // std::thread  

void thr_function1()  
{  
    for (int i = 0; i != 10; ++i)  
    {  
        std::cout << "thread 1 print " << i << std::endl;  
    }  
}  

void thr_function2(int n)  
{  
    std::cout << "thread 1 print " << n << std::endl;  
}  

int main()  
{  
    std::thread t1(thr_function1);     // spawn new thread that calls foo()  
    std::thread t2(thr_function2, 111);  // spawn new thread that calls bar(0)  

    std::cout << "main, foo and bar now execute concurrently...\n";  

    // synchronize threads:  
    t1.join();                // pauses until first finishes  
    t2.join();               // pauses until second finishes  

    std::cout << "thread 1 and htread 2 completed.\n";  

    return 0;  
}  
```

3. 拷贝构造函数(被禁用)，意味着 thread 不可被拷贝构造。

4. move 构造函数，move 构造函数，调用成功之后 x 不代表任何 thread 执行对象。
```c++
// example for thread::operator=  
#include <iostream>       // std::cout  
#include <thread>         // std::thread, std::this_thread::sleep_for  
#include <chrono>         // std::chrono::seconds  

void pause_thread(int n)  
{  
    std::this_thread::sleep_for(std::chrono::seconds(n));//c++11 this_thread 类  
    std::cout << "pause of " << n << " seconds ended\n";  
}  

int main()  
{  
    std::thread threads[5];                         // default-constructed threads  

    std::cout << "Spawning 5 threads...\n";  
    for (int i = 0; i<5; ++i)  
        threads[i] = std::thread(pause_thread, i + 1);   // move-assign threads 这里调用move复制函数  

    std::cout << "Done spawning threads. Now waiting for them to join:\n";  
    for (int i = 0; i<5; ++i)  
        threads[i].join();  

    std::cout << "All threads joined!\n";  

    return 0;  
}
```


##成员类型和成员函数
![](../picture/test.jpg)
##异步

##多线程传递参数。

##join、detach
```c++
#include<thread>  
#include<array>  
using namespace std;  
void show()  
{  
    cout << "hello cplusplus!" << endl;  
}  
int main()  
{  
    array<thread, 3>  threads = { thread(show), thread(show), thread(show) };  
    for (int i = 0; i < 3; i++)  
    {  
        cout << threads[i].joinable() << endl;//判断线程是否可以join  
        threads[i].join();//主线程等待当前线程执行完成再退出  
    }  
    return 0;  
}  
运行结果:  
hello cplusplus!  
hello cplusplus!  
1  
hello cplusplus!  
1  
1
```
总结：
join 是让当前主线程等待所有的子线程执行完，才能退出。

```c++
#include<thread>  
using namespace std;  
void show()  
{  
    cout << "hello cplusplus!" << endl;  
}  
int main()  
{  
    thread th(show);  
    //th.join();   
    th.detach();//脱离主线程的绑定，主线程挂了，子线程不报错，子线程执行完自动退出。  
    //detach以后，子线程会成为孤儿线程，线程之间将无法通信。  
    cout << th.joinable() << endl;  
    return 0;  
}  
运行结果:  
hello cplusplus! 
```
##获取CPU核心个数
```c++
#include<thread>  
using namespace std;  
int main()  
{  
    auto n = thread::hardware_concurrency();//获取cpu核心个数  
    cout << n << endl;  
    return 0;  
}  
运行结果:  
8
```
##CPP原子变量与线程安全
```c++
**#include<thread>  
using namespace std;  
const int N = 100000000;  
int num = 0;  
void run()  
{  
    for (int i = 0; i < N; i++)  
    {  
        num++;  
    }  
}  
int main()  
{  
    clock_t start = clock();  
    thread t1(run);  
    thread t2(run);  
    t1.join();  
    t2.join();  
    clock_t end = clock();  
    cout << "num=" << num << ",用时 " << end - start << " ms" << endl;  
    return 0;  
}  
```
为了解决此问题，有以下方法：
1. 互斥量。通过互斥量后运算结果正确，但是计算速度很慢，原因主要是互斥量加解锁需要时间
```c++
mutex m;  //加入互斥量
void run()  
{  
    for (int i = 0; i < N; i++)  
    {  
        m.lock();  
        num++;  
        m.unlock();  
    }  
}  
```
2. 原子变量。不难发现，通过原子变量后运算结果正确，计算速度一般。
```c++
atomic_int num{ 0 };//不会发生线程冲突，线程安全  
void run()  
{  
    for (int i = 0; i < N; i++)  
    {  
        num++;  
    }  
}  
```
3. 加入join()
```c++
int main()  
{  
    clock_t start = clock();  
    thread t1(run);  
    t1.join();  
    thread t2(run);  
    t2.join();  
    clock_t end = clock();  
    cout << "num=" << num << ",用时 " << end - start << " ms" << endl;  
    return 0;  
}  
```

##lambda与多线程
```c++
#include<thread>  
using namespace std;  
int main()  
{  
    auto fun = [](const char *str) {cout << str << endl; };  
    thread t1(fun, "hello world!");  
    thread t2(fun, "hello beijing!");  
    return 0;  
}  
运行结果：  
hello world!  
hello beijing
```

##时间等待相关问题
```c++
#include<thread>  
#include<chrono>  
using namespace std;  
int main()  
{  
    thread th1([]()  
    {  
        //让线程等待3秒  
        this_thread::sleep_for(chrono::seconds(3));  
        //让cpu执行其他空闲的线程  
        this_thread::yield();  
        //线程id  
        cout << this_thread::get_id() << endl;  
    });  
    return 0;  
}
```
##线程功能拓展
```c++
#include<thread>  
using namespace std;  
class MyThread :public thread   //继承thread  
{  
public:  
    //子类MyThread()继承thread()的构造函数  
    MyThread() : thread()  
    {  
    }  
    //MyThread()初始化构造函数  
    template<typename T, typename...Args>  
    MyThread(T&&func, Args&&...args) : thread(forward<T>(func), forward<Args>(args)...)  
    {  
    }  
    void showcmd(const char *str)  //运行system  
    {  
        system(str);  
    }  
};  
int main()  
{  
    MyThread th1([]()  
    {  
        cout << "hello" << endl;  
    });  
    th1.showcmd("calc"); //运行calc  
    //lambda  
    MyThread th2([](const char * str)  
    {  
        cout << "hello" << str << endl;  
    }, " this is MyThread");  
    th2.showcmd("notepad");//运行notepad  
    return 0;  
}  
运行结果:  
hello  
//运行calc  
hello this is MyThread  
//运行notepad
```

##多线程可变参数
```c++
#include<thread>  
#include<cstdarg>  
using namespace std;  
int show(const char *fun, ...)  
{  
    va_list ap;//指针  
    va_start(ap, fun);//开始  
    vprintf(fun, ap);//调用  
    va_end(ap);  
    return 0;  
}  
int main()  
{  
    thread t1(show, "%s    %d    %c    %f", "hello world!", 100, 'A', 3.14159);  
    return 0;  
}  
运行结果：  
hello world!    100    A    3.14159
```

##线程交换
```c++
#include<thread>  
using namespace std;  
int main()  
{  
    thread t1([]()  
    {  
        cout << "thread1" << endl;  
    });  
    thread t2([]()  
    {  
        cout << "thread2" << endl;  
    });  
    cout << "thread1' id is " << t1.get_id() << endl;  
    cout << "thread2' id is " << t2.get_id() << endl;  

    cout << "swap after:" << endl;  
    swap(t1, t2);//线程交换  
    cout << "thread1' id is " << t1.get_id() << endl;  
    cout << "thread2' id is " << t2.get_id() << endl;  
    return 0;  
}  
运行结果:  
thread1  
thread2  
thread1' id is 4836  
thread2' id is 4724  
swap after:  
thread1' id is 4724  
thread2' id is 4836
```
##线程移动
```c++
#include<thread>  
using namespace std;  
int main()  
{  
    thread t1([]()  
    {  
        cout << "thread1" << endl;  
    });  
    cout << "thread1' id is " << t1.get_id() << endl;  
    thread t2 = move(t1);;  
    cout << "thread2' id is " << t2.get_id() << endl;  
    return 0;  
}  
运行结果:  
thread1  
thread1' id is 5620  
thread2' id is 5620
```
