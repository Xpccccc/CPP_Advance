#include <iostream>

using namespace std;

class Person {
public:
    virtual void BuyTicket() {
        cout << "票价--全票" << endl;
    }
};

class Student : public Person {
public:
    //void BuyTicket() {// 也是可以的
    virtual void BuyTicket() {
        cout << "票价--半票" << endl;
    }
};

class Children : public Person {
public:
    virtual void BuyTicket() {
        cout << "票价--免费" << endl;
    }
};

void Buy(Person &p) {
    p.BuyTicket();
}

void Buy(Person *p) {
    p->BuyTicket();
}

// 多态
// 条件 1.必须通过基类的指针或者引用调用虚函数
//     2.被调用的函数必须是虚函数，且派生类必须对基类的虚函数进行重写
int main() {

    Person p;
    Buy(p);
    Buy(&p);

    Student s;
    Buy(s);
    Buy(&s);

    Children c;
    Buy(c);
    Buy(&c);

    return 0;
}