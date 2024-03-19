#include <iostream>

using namespace std;

// 协变
class A {
};

class B : public A {
};

class Person {
public:
//    virtual Person *f() {
//        cout << "P" << endl;
//        return new Person;
//    }

    virtual A *f() {
        cout << "P" << endl;
        return new A;
    }
};

class Student : public Person {
public:
//    virtual Student *f() {
//        cout << "S" << endl;
//        return new Student;
//    }

    virtual B *f() {
        cout << "S" << endl;
        return new B;
    }
};

void Func(Person &p) {
    p.f();
}

int main() {

    Person p;
    Func(p);
    Student s;
    Func(s);

    return 0;
}

