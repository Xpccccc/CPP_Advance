#include <iostream>

using namespace std;

// override关键字
class Person {
public:
    virtual void Print() {}
    virtual void Print1() final{}
};

class Student : public Person {
public:
    virtual void Print() override {} // 检查虚函数重写的语法
//    virtual void Print1() override {} // 检查虚函数重写的语法
};