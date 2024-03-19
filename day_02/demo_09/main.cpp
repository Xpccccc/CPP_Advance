#include <iostream>

using namespace std;

// 打印虚表内容 单继承 -- 要32位条件下
class Base {
public:
    virtual void Func1() {
        cout << "Base::Func1" << endl;
    }

    virtual void Func2() { cout << "Base::Func2" << endl; }

    void Func3() { cout << "Base::Func3" << endl; }

protected:
private:
    int _b;
};

class Derive : public Base {
public:
    virtual void Func1() {
        cout << "Derive::Func1" << endl;
    }

    virtual void Func3() {
        cout << "Derive::Func3" << endl;
    }

    void Func4() {
        cout << "Derive::Func4" << endl;
    }

protected:
    int _d;
};

typedef void(*VF_PTR)();

void Printf_VFT(VF_PTR *vft) {
    for (int i = 0; vft[i]; ++i) {
        printf("[%d]:%s->", i, vft[i]);
        VF_PTR f = vft[i];
        f();
    }
}


int main() {
    Base b;
    Derive d;

    Printf_VFT((VF_PTR *) (*(int *) (&d)));
    return 0;
}
