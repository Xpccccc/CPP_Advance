#include <iostream>

using namespace std;

// 菱形继承和菱形虚拟继承
class Person {
public :
    string _name; // 姓名
    int _age;
};

//class Student : public Person {
class Student : virtual public Person {
protected :
    int _num; //学号
};

//class Teacher : public Person {
class Teacher : virtual public Person {
protected :
    int _id; // 职工编号
};

class Assistant : public Student, public Teacher {
protected :
    string _majorCourse; // 主修课程
};


void Test1() {

    Assistant a;

//    a._name = "peter";// 这样会有二义性无法明确知道访问的是哪一个
// 需要显示指定访问哪个父类的成员可以解决二义性问题，但是数据冗余问题无法解决 --- 比如年龄不用存两份
    a.Student::_name = "xxx";
    a.Teacher::_name = "yyy";
}

void Test2() {

    Assistant a;

    a._name = "peter";// 这样就没有二义性

}

int main() {
    Test2();
    return 0;
}

