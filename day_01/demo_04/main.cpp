#include <iostream>

using namespace std;


//    隐藏
// Student的_num和Person的_num构成隐藏关系，可以看出这样代码虽然能跑，但是非常容易混淆
class Person {
protected :
    string _name = "小李子"; // 姓名
    int _num = 111;// 身份证号
};

class Student : public Person {
public:
    void Print() {
        cout << " 姓名:" << _name << endl;
        cout << " 身份证号:" << Person::_num << endl;
        cout << " 学号:" << _num << endl;
    }

protected:
    int _num = 999; // 学号
};

int main() {
    Student s1;
    s1.Print();
    return 0;
};
