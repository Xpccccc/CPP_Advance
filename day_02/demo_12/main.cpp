#include <iostream>

using namespace std;

class A {
public:
    A() : m_iVal(0) { test(); }

    virtual void func() { std::cout << m_iVal << ' '; }

    void test() { //A* this
        func();//this->func  -- 多态调用
    }

public:
    int m_iVal;
};

class B : public A {
public:
    B() { test(); }

    virtual void func() {
        ++m_iVal;
        std::cout << m_iVal << ' ';
    }
};


// 多态调用的练习题 -- 建议分析一遍
int main(int argc, char *argv[]) {
    A *p = new B;
    p->test();// 普通调用
    return 0;
}
