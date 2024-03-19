#include <iostream>

using namespace std;

// 虚拟继承内存视图
class A {
public:
    int _a;
};

// class B : public A
class B : virtual public A {
public:
    int _b;
};

// class C : public A
class C : virtual public A {
public:
    int _c;
};

class D : public B, public C {
public:
    int _d;
};

int main() {
    D d;
    d.B::_a = 1;
    d.C::_a = 2;
    d._b = 3;
    d._c = 4;
    d._d = 5;
    return 0;
}



//// 虚拟继承
//class Person {
//public :
//    string _name; // 姓名
//    int _age;
//};
//
////class Student : public Person {
//class Student : virtual public Person {
//protected :
//    int _num; //学号
//};
//
////class Teacher : public Person {
//class Teacher : virtual public Person {
//protected :
//    int _id; // 职工编号
//};
//
//class Assistant : public Student, public Teacher {
//protected :
//    string _majorCourse; // 主修课程
//};
//
//
//void Test1() {
//
//    Assistant a;
//
////    a._name = "peter";// 这样会有二义性无法明确知道访问的是哪一个
//// 需要显示指定访问哪个父类的成员可以解决二义性问题，但是数据冗余问题无法解决 --- 比如年龄不用存两份
//    a.Student::_name = "xxx";
//    a.Teacher::_name = "yyy";
//}
//
//void Test2() {
//
//    Assistant a;
//
//    a._name = "peter";// 这样就没有二义性
//
//}
//
//int main() {
//    Test2();
//    return 0;
//}


//// 静态成员
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

//class Base {
//public:
//    static int staticVar; // 静态成员变量
//    static void staticFunc() { // 静态成员函数
//        std::cout << "Base::staticFunc() called" << std::endl;
//    }
//};
//
//int Base::staticVar = 10; // 静态成员变量初始化
//
//class Derived : public Base {
//public:
//    static void staticFunc() { // 静态成员函数
//        std::cout << "Derived::staticFunc() called" << std::endl;
//    }
//};
//
//int main() {
//    // 通过派生类调用静态成员函数
//    Derived::staticFunc(); // 输出：Derived::staticFunc() called
//
//    // 通过基类调用静态成员函数
//    Base::staticFunc(); // 输出：Base::staticFunc() called
//
//
//    // 访问静态成员变量
//    std::cout << "Base::staticVar: " << Base::staticVar << std::endl; // 输出：Base::staticVar: 10
//
//    // 修改静态成员变量
//    Base::staticVar = 20;
//    std::cout << "Base::staticVar: " << Base::staticVar << std::endl; // 输出：Base::staticVar: 20
//
//    // 派生类也共享相同的静态成员变量
//    std::cout << "Derived::staticVar: " << Derived::staticVar << std::endl; // 输出：Derived::staticVar: 20
//
//    return 0;
//}



////友元
//class Student;
//
//class Person {
//public:
//    // 友元不能继承，也就是说基类友元不能访问子类私有和保护成员
//    friend void Print(const Person &p, const Student &s);
//
//protected:
//    string _name = "hh";
//    int _age = 1;
//};
//
//
//
//class Student : public Person {
//    friend void Print(const Person &p, const Student &s);
//public:
//protected:
//    int _id = 2;
//};
//void Print(const Person &p, const Student &s) {
//    cout << "Person name:" << p._name << endl << "Person age:" << p._age << endl;
//    cout << "Student id:" << s._id << endl;// 访问不了_id
//}
//
//int main() {
//    Student s;
//    Person p;
//    Print(p, s);
//    return 0;
//}



//// 默认成员函数
//class Person {
//public:
//    Person(const char *name = "张三", int age = 18) : _name(name), _age(age) {
//        cout << "Person()" << endl;
//    }
//
//    Person(const Person &p) : _name(p._name), _age(p._age) {
//        cout << "Person(const Person &p)" << endl;
//    }
//
//    Person &operator=(const Person &p) {
//        if (&p != this) {
//            _name = p._name;
//            _age = p._age;
//        }
//        cout << "Person &operator=(const Person &p)" << endl;
//        return *this;
//    }
//
//    ~Person() {
//        cout << "~Person()" << endl;
//    }
//
//protected:
//    const char *_name;
//    int _age;
//};
//
//class Student : public Person {
//public:
//    Student(int id = 0, const char *name = "ss", int age = 1) : Person(name, age), _id(id) {
//        cout << "Student()" << endl;
//    }
//
//    Student(const Student &s) : Person(s), _id(s._id) {
//        cout << "Student(const Student &s)" << endl;
//    }
//
//    Student &operator=(const Student &s) {
//        if (&s != this) {
//            Person::operator=(s);
//            _id = s._id;
//        }
//
//        cout << "Student &operator=(const Student &s)" << endl;
//        return *this;
//    }
//
//    ~Student() {
//        cout << "~Student()" << endl;
//    }
//
//protected:
//    int _id;
//};
//
//int main() {
//    Student s(1,"xp",26);
////    Person p;
////    p = s;
//
//    Student s1;
//    s1 = s;
//
//    return 0;
//}



////    隐藏
//// Student的_num和Person的_num构成隐藏关系，可以看出这样代码虽然能跑，但是非常容易混淆
//class Person {
//protected :
//    string _name = "小李子"; // 姓名
//    int _num = 111;// 身份证号
//};
//
//class Student : public Person {
//public:
//    void Print() {
//        cout << " 姓名:" << _name << endl;
//        cout << " 身份证号:" << Person::_num << endl;
//        cout << " 学号:" << _num << endl;
//    }
//
//protected:
//    int _num = 999; // 学号
//};
//
//void Test() {
//    Student s1;
//    s1.Print();
//};

//// 赋值兼容转换 -- 切片   隐藏
//class Person {
//public:
//    Person(string name = "张三", string sex = "男", int age = 18) : _name(name), _sex(sex), _age(age) {
//        cout << "Person(string name = \"张三\", string sex = \"男\", int age = 18) : _name(name), _sex(sex), _age(age)"
//             << endl;
//    }
//
//    void Print() {
//        cout << "Person:Print()" << endl;
//    }
//
//protected:
//    string _name;
//    string _sex;
//    int _age;
//};
//
//class Student : public Person {
//public:
//    Student(int id, string name, string sex, int age) : Person(name, sex, age), _stuid(id) {
//        cout << "Student(int id, string name, string sex, int age) : Person(name, sex, age), _stuid(id)" << endl;
//    }
//
//    void Print(int a) {
//        cout << "Student:Print(int a)" << endl;
//    }
//
//protected:
//    int _stuid;
//};
//
//int main() {
//    Student sobj(1, "杨", "男", 22);
//
//    // 赋值兼容转换 --- 切片
//    // 只赋值父类有的成员数据
//    Person pobj = sobj;
//    Person *pp = &sobj;
//    Person &pr = sobj;
//
//    sobj.Print(1);
//    sobj.Person::Print();
//
//    return 0;
//}


//// 认识继承
//class Person {
//public:
//    void Print() {
//        cout << _name << " " << _age << endl;
//    }
//
//protected:
//    string _name = "张三";
//    int _age = 18;
//};
//
//class Student : public Person {
//public:
//    void Study() {
//        cout << "Study" << endl;
//    }
//
//protected:
//    int _stuid;
//};
//
//class Teacher : public Person {
//public:
//    void Teach() {
//        cout << "Teach" << endl;
//    }
//
//protected:
//    int _jobid;
//};
//
//// 继承
//int main() {
//
//    Student s;
//    Teacher t;
//
//    s.Print();
//    t.Print();
//    return 0;
//}
