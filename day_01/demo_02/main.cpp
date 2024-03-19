#include <iostream>

using namespace std;

//  认识继承
class Person {
public:
    void Print() {
        cout << _name << " " << _age << endl;
    }

protected:
    string _name = "张三";
    int _age = 18;
};

class Student : public Person {
public:
    void Study() {
        cout << "Study" << endl;
    }

protected:
    int _stuid;
};

class Teacher : public Person {
public:
    void Teach() {
        cout << "Teach" << endl;
    }

protected:
    int _jobid;
};

// 继承
int main() {

    Student s;
    Teacher t;

    s.Print();
    t.Print();
    return 0;
}