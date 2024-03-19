#include <iostream>

using namespace std;

//析构函数的重写
class Person {
public:
    virtual ~Person() {
        cout << "~Person" << endl;
    }
};

class Student : public Person {
public:
    virtual ~Student() {
        cout << "~Student" << endl;
    }
};


int main() {
    Person *p = new Person;
    Person *s = new Student;

    delete p;
    delete s;

    Student ss;
    return 0;
}