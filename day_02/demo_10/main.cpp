#include <iostream>

using namespace std;

// 打印虚表内容 多继承 -- 要32位条件下
class Base1 {
public:
    virtual void func1() { cout << "Base1::func1" << endl; }

    virtual void func2() { cout << "Base1::func2" << endl; }

private:
    int b1;
};

class Base2 {
public:
    virtual void func1() { cout << "Base2::func1" << endl; }

    virtual void func2() { cout << "Base2::func2" << endl; }

private:
    int b2;
};

class Derive : public Base1, public Base2 {
public:
    virtual void func1() { cout << "Derive::func1" << endl; }

    virtual void func3() { cout << "Derive::func3" << endl; }

private:
    int d1;
};

typedef void(*VF_PTR)();

void Printf_VFT(VF_PTR *vft) {
    for (int i = 0; vft[i]; ++i) {
        printf("[%d]:0x%x->", i, vft[i]);
        VF_PTR f = vft[i];
        f();
    }
}


int main() {
    Derive d;
    VF_PTR *vTableb1 = (VF_PTR *) (*(int *) &d);
    Printf_VFT(vTableb1);
    VF_PTR *vTableb2 = (VF_PTR *) (*(int *) ((char *) &d + sizeof(Base1))); // sizeof(Base1)是Derive对象模型首位置到Base2对象模型首位置的偏移量
    Printf_VFT(vTableb2);
    return 0;
}
