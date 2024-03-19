#include <iostream>

using namespace std;

//// 继承中的静态成员
//class Person {
//public :
//    Person() { ++_count; }
//
//protected :
//    string _name; // 姓名
//public :
//    static int _count; // 统计人的个数。
//};
//
//int Person::_count = 0;
//
//class Student : public Person {
//protected :
//    int _stuNum; // 学号
//};
//
//class Graduate : public Student {
//protected :
//    string _seminarCourse; // 研究科目
//};
//
//int main() {
//
//    Student s1;
//    Student s2;
//    Student s3;
//    Graduate s4;
//    cout << " 人数 :" << Person::_count << endl;
//    Student::_count = 0;
//    cout << " 人数 :" << Person::_count << endl;
//
//    // 同一个_count
//    cout << &Person::_count << " " << &Student::_count << " " << &Graduate::_count << endl;
//
//    return 0;
//}

class Base {
public:
    static int staticVar; // 静态成员变量
    static void staticFunc() { // 静态成员函数
        std::cout << "Base::staticFunc() called" << std::endl;
    }
};

int Base::staticVar = 10; // 静态成员变量初始化

class Derived : public Base {
public:
    static void staticFunc() { // 静态成员函数
        std::cout << "Derived::staticFunc() called" << std::endl;
    }
};

int main() {
    // 通过派生类调用静态成员函数
    Derived::staticFunc(); // 输出：Derived::staticFunc() called

    // 通过基类调用静态成员函数
    Base::staticFunc(); // 输出：Base::staticFunc() called


    // 访问静态成员变量
    std::cout << "Base::staticVar: " << Base::staticVar << std::endl; // 输出：Base::staticVar: 10

    // 修改静态成员变量
    Base::staticVar = 20;
    std::cout << "Base::staticVar: " << Base::staticVar << std::endl; // 输出：Base::staticVar: 20

    // 派生类也共享相同的静态成员变量
    std::cout << "Derived::staticVar: " << Derived::staticVar << std::endl; // 输出：Derived::staticVar: 20

    return 0;
}