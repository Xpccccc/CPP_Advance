#include <iostream>

using namespace std;


// 多态单继承对象模型

class Base {
public:
    virtual void Func1() {}

    virtual void Func2() {}

    void Func3() {}

protected:
private:
    int _b;
};

class Derive : public Base {
public:
    virtual void Func1() {}

    virtual void Func3() {}

    void Func4() {}

protected:
    int _d;
};

int main() {
    Base b;
    Derive d;

    cout << sizeof(b) << endl;
    return 0;
}

