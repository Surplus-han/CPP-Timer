#include <iostream>
#include "Timer/timer.h"
using namespace hanjr::core;
void foo()
{
    std::cout << "foo" << std::endl;
}


void bar(const std::string & name){
    std::cout << "bar" << name << std::endl;
}
int main() {
    Timer t1(3);
    t1.start(1000,foo);


    std::getchar(); // 阻塞等待输入

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
