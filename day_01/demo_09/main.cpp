#include <iostream>

using namespace std;

// 虚拟继承内存视图
class A {
public:
    int _a;
};

// class B : public A
class B : virtual public A {
public:
    int _b;
};

// class C : public A
class C : virtual public A {
public:
    int _c;
};

class D : public B, public C {
public:
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
