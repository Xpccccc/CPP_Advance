#include <iostream>

using namespace std;


// 菱形继承和菱形虚拟继承在多态情况下的对象模型

class A {
public:
    virtual void func1(){}
    int _a;
};

//class B :  public A {
class B : virtual public A {
public:
    virtual void func1() {}
    virtual void func2(){}
    int _b;
};

//class C :  public A {
class C : virtual public A {
public:
    virtual void func1() {}
    virtual void func3() {}
    int _c;
};

class D : public B, public C {
public:
    virtual void func1() {}
    int _d;
};

int main() {
    D d;
    d.B::_a = 1;
    d.C::_a = 2;
    d._b = 3;
    d._c = 4;
    d._d = 5;
    return 0;
}
