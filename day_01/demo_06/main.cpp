#include <iostream>

using namespace std;

//  继承中的友元
class Student;

class Person {
public:
    // 友元不能继承，也就是说基类友元不能访问子类私有和保护成员
    friend void Print(const Person &p, const Student &s);

protected:
    string _name = "hh";
    int _age = 1;
};



class Student : public Person {
    friend void Print(const Person &p, const Student &s);
public:
protected:
    int _id = 2;
};
void Print(const Person &p, const Student &s) {
    cout << "Person name:" << p._name << endl << "Person age:" << p._age << endl;
    cout << "Student id:" << s._id << endl;// 访问不了_id
}

int main() {
    Student s;
    Person p;
    Print(p, s);
    return 0;
}
