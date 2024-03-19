#include <iostream>

using namespace std;

// 抽象类
class Car {
public:
    // 纯虚函数
    virtual void Drive() = 0;// 抽象类不能实例化
};

class Audi : public Car {
public:
    // 抽象类的子类必须重写父类的纯虚函数,不重写的话子类也不能实例化
    virtual void Drive() {
        cout << "商务" << endl;
    }
};

int main() {
//    Car c;
    Audi a;
    return 0;
}