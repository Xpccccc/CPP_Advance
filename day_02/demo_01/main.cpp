#include <iostream>

using namespace std;





//// 打印虚表内容 多继承 -- 要32位条件下
//class Base1 {
//public:
//    virtual void func1() { cout << "Base1::func1" << endl; }
//
//    virtual void func2() { cout << "Base1::func2" << endl; }
//
//private:
//    int b1;
//};
//
//class Base2 {
//public:
//    virtual void func1() { cout << "Base2::func1" << endl; }
//
//    virtual void func2() { cout << "Base2::func2" << endl; }
//
//private:
//    int b2;
//};
//
//class Derive : public Base1, public Base2 {
//public:
//    virtual void func1() { cout << "Derive::func1" << endl; }
//
//    virtual void func3() { cout << "Derive::func3" << endl; }
//
//private:
//    int d1;
//};
//
//typedef void(*VF_PTR)();
//
//void Printf_VFT(VF_PTR *vft) {
//    for (int i = 0; vft[i]; ++i) {
//        printf("[%d]:0x%x->", i, vft[i]);
//        VF_PTR f = vft[i];
//        f();
//    }
//}
//
//
//int main() {
//    Derive d;
//    VF_PTR *vTableb1 = (VF_PTR *) (*(int *) &d);
//    Printf_VFT(vTableb1);
//    VF_PTR *vTableb2 = (VF_PTR *) (*(int *) ((char *) &d + sizeof(Base1))); // sizeof(Base1)是Derive对象模型首位置到Base2对象模型首位置的偏移量
//    Printf_VFT(vTableb2);
//    return 0;
//}


//// 打印虚表内容 单继承 -- 要32位条件下
//class Base {
//public:
//    virtual void Func1() {
//        cout << "Base::Func1" << endl;
//    }
//
//    virtual void Func2() { cout << "Base::Func2" << endl; }
//
//    void Func3() { cout << "Base::Func3" << endl; }
//
//protected:
//private:
//    int _b;
//};
//
//class Derive : public Base {
//public:
//    virtual void Func1() {
//        cout << "Derive::Func1" << endl;
//    }
//
//    virtual void Func3() {
//        cout << "Derive::Func3" << endl;
//    }
//
//    void Func4() {
//        cout << "Derive::Func4" << endl;
//    }
//
//protected:
//    int _d;
//};
//
//typedef void(*VF_PTR)();
//
//void Printf_VFT(VF_PTR *vft) {
//    for (int i = 0; vft[i]; ++i) {
//        printf("[%d]:%s->", i, vft[i]);
//        VF_PTR f = vft[i];
//        f();
//    }
//}
//
//
//int main() {
//    Base b;
//    Derive d;
//
//    Printf_VFT((VF_PTR *) (*(int *) (&d)));
//    return 0;
//}


//// 抽象类
//class Car {
//public:
//    // 纯虚函数
//    virtual void Drive() = 0;// 抽象类不能实例化
//};
//
//class Audi : public Car {
//public:
//    // 抽象类的子类必须重写父类的纯虚函数,不重写的话子类也不能实例化
//    virtual void Drive() {
//        cout << "商务" << endl;
//    }
//};
//
//int main() {
////    Car c;
//    Audi a;
//    return 0;
//}


//class Person {
//public:
//    virtual void BuyTicket() { cout << "买票-全价" << endl; }
//};
//
//class Student : public Person {
//public:
//    virtual void BuyTicket() { cout << "买票-半价" << endl; }
//};
//
//void Func(Person &p) {
//    p.BuyTicket();
//}
//
//int main() {
//    Person Mike;
//    Func(Mike);
//    Student Johnson;
//    Func(Johnson);
//    return 0;
//}

//class Base {
//public:
//    virtual void Func1() {}
//
//    virtual void Func2() {}
//
//    void Func3() {}
//
//protected:
//private:
//    int _b;
//};
//
//class Derive : public Base {
//public:
//    virtual void Func1() {}
//
//    virtual void Func3() {}
//
//    void Func4() {}
//
//protected:
//    int _d;
//};
//
//int main() {
//    Base b;
//    Derive d;
//
//    cout << sizeof(b) << endl;
//    return 0;
//}



//class Person {
//public:
//    virtual void Print() {}
//    virtual void Print1() final{}
//};
//
//class Student : public Person {
//public:
//    virtual void Print() override {} // 检查虚函数重写的语法
////    virtual void Print1() override {} // 检查虚函数重写的语法
//};


////final
//class Car {
//public:
//    virtual void Drive() final {}// final：修饰虚函数，表示该虚函数不能再被重写
//
//};
//
//class Audi : public Car {
//public:
//    //    virtual void Drive() {}// 不可以再重写
//};
//
////final 修饰类表示这个类不可再被继承
//class Person final {
//};
////class Student:public Person{};



////析构函数的重写
//class Person {
//public:
//    virtual ~Person() {
//        cout << "~Person" << endl;
//    }
//};
//
//class Student : public Person {
//public:
//    virtual ~Student() {
//        cout << "~Student" << endl;
//    }
//};
//
//
//int main() {
//    Person *p = new Person;
//    Person *s = new Student;
//
//    delete p;
//    delete s;
//
//    Student ss;
//    return 0;
//}

//// 协变
//class A {
//};
//
//class B : public A {
//};
//
//class Person {
//public:
////    virtual Person *f() {
////        cout << "P" << endl;
////        return new Person;
////    }
//
//    virtual A *f() {
//        cout << "P" << endl;
//        return new A;
//    }
//};
//
//class Student : public Person {
//public:
////    virtual Student *f() {
////        cout << "S" << endl;
////        return new Student;
////    }
//
//    virtual B *f() {
//        cout << "S" << endl;
//        return new B;
//    }
//};
//
//void Func(Person &p) {
//    p.f();
//}
//
//int main() {
//
//    Person p;
//    Func(p);
//    Student s;
//    Func(s);
//
//    return 0;
//}
//


//class Person {
//public:
//    virtual void BuyTicket() {
//        cout << "票价--全票" << endl;
//    }
//};
//
//class Student : public Person {
//public:
//    //void BuyTicket() {// 也是可以的
//    virtual void BuyTicket() {
//        cout << "票价--半票" << endl;
//    }
//};
//
//class Children : public Person {
//public:
//    virtual void BuyTicket() {
//        cout << "票价--免费" << endl;
//    }
//};
//
//void Buy(Person &p) {
//    p.BuyTicket();
//}
//
//void Buy(Person *p) {
//    p->BuyTicket();
//}
//
//// 多态
//// 条件 1.必须通过基类的指针或者引用调用虚函数
////     2.被调用的函数必须是虚函数，且派生类必须对基类的虚函数进行重写
//int main() {
//
//    Person p;
//    Buy(p);
//    Buy(&p);
//
//    Student s;
//    Buy(s);
//    Buy(&s);
//
//    Children c;
//    Buy(c);
//    Buy(&c);
//
//    return 0;
//}
