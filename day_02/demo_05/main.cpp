#include <iostream>

using namespace std;

//final关键字
class Car {
public:
    virtual void Drive() final {}// final：修饰虚函数，表示该虚函数不能再被重写

};

class Audi : public Car {
public:
    //    virtual void Drive() {}// 不可以再重写
};

//final 修饰类表示这个类不可再被继承
class Person final {
};
//class Student:public Person{};

