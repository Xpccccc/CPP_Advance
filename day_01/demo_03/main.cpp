#include <iostream>

using namespace std;

// 赋值兼容转换 -- 切片   隐藏
class Person {
public:
    Person(string name = "张三", string sex = "男", int age = 18) : _name(name), _sex(sex), _age(age) {
        cout << "Person(string name = \"张三\", string sex = \"男\", int age = 18) : _name(name), _sex(sex), _age(age)"
             << endl;
    }

    void Print() {
        cout << "Person:Print()" << endl;
    }

protected:
    string _name;
    string _sex;
    int _age;
};

class Student : public Person {
public:
    Student(int id, string name, string sex, int age) : Person(name, sex, age), _stuid(id) {
        cout << "Student(int id, string name, string sex, int age) : Person(name, sex, age), _stuid(id)" << endl;
    }

    void Print(int a) {
        cout << "Student:Print(int a)" << endl;
    }

protected:
    int _stuid;
};

int main() {
    Student sobj(1, "杨", "男", 22);

    // 赋值兼容转换 --- 切片
    // 只赋值父类有的成员数据
    Person pobj = sobj;
    Person *pp = &sobj;
    Person &pr = sobj;

    sobj.Print(1);
    sobj.Person::Print();

    return 0;
}
