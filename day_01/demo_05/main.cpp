#include <iostream>

using namespace std;

// 继承中的默认成员函数
class Person {
public:
    Person(const char *name = "张三", int age = 18) : _name(name), _age(age) {
        cout << "Person()" << endl;
    }

    Person(const Person &p) : _name(p._name), _age(p._age) {
        cout << "Person(const Person &p)" << endl;
    }

    Person &operator=(const Person &p) {
        if (&p != this) {
            _name = p._name;
            _age = p._age;
        }
        cout << "Person &operator=(const Person &p)" << endl;
        return *this;
    }

    ~Person() {
        cout << "~Person()" << endl;
    }

protected:
    const char *_name;
    int _age;
};

class Student : public Person {
public:
    Student(int id = 0, const char *name = "ss", int age = 1) : Person(name, age), _id(id) {
        cout << "Student()" << endl;
    }

    Student(const Student &s) : Person(s), _id(s._id) {
        cout << "Student(const Student &s)" << endl;
    }

    Student &operator=(const Student &s) {
        if (&s != this) {
            Person::operator=(s);
            _id = s._id;
        }

        cout << "Student &operator=(const Student &s)" << endl;
        return *this;
    }

    ~Student() {
        cout << "~Student()" << endl;
    }

protected:
    int _id;
};

int main() {
    Student s(1,"xp",26);
//    Person p;
//    p = s;

    Student s1;
    s1 = s;

    return 0;
}
