#include <iostream>
#include <vector>
#include <functional>

using namespace std;

struct Goods {
    string _name;// 名字
    double _price; // 价格
    int _evaluate; // 评价
    Goods(const char *str, double price, int evaluate)
            : _name(str), _price(price), _evaluate(evaluate) {}
};

struct ComparePriceLess {
    bool operator()(const Goods &gl, const Goods &gr) {
        return gl._price < gr._price;
    }
};

struct ComparePriceGreater {
    bool operator()(const Goods &gl, const Goods &gr) {
        return gl._price > gr._price;
    }
};

//
//// lambda 表达式使用
//int main() {
//    vector<Goods> v = {{"苹果", 2.1, 5},
//                       {"香蕉", 3,   4},
//                       {"橙子", 2.2, 3},
//                       {"菠萝", 1.5, 4}};
////    sort(v.begin(), v.end(), ComparePriceLess());
////    sort(v.begin(), v.end(), ComparePriceGreater());
//
//    //  按价格
//    sort(v.begin(), v.end(), [](const Goods &gl, const Goods &gr) {
//        return gl._price < gr._price;
//    });
//
//    // 按评价
//    sort(v.begin(), v.end(), [](const Goods &gl, const Goods &gr) {
//        return gl._evaluate < gr._evaluate;
//    });
//}


//// lambda 表达式用法
//// [capture-list] (parameters) mutable -> return-type { statement;}
//int main() {
//    [] {};
//    auto add = [](int a, int b) -> int { return a + b; };
//    auto sub = [](int a, int b) { return a - b; };
//    cout << add(1, 2) << endl;
//    cout << sub(1, 2) << endl;
//
//    int a = 3, b = 4;
//    auto ret1 = [=] { return a + b; }; // [=]捕捉当前行及以上所有的临时变量（参数）,这里是传值
//    cout << ret1() << endl;
//
//    auto ret2 = [&](int c) { return b = a + c; };// [&]捕捉当前行及以上所有的临时变量（参数）,这里是传引用
//    cout << ret2(10) << endl;
//    cout << b << endl;
//
//    // 也可以混合使用
//    int c = 20;
//    auto ret3 = [=, &b]mutable {
//        b += a;
//        a++;
//        c++;
//    };// 这里不使用mutable不行，因为a，c都是const（[=]传过来就是给他加上const）
//    cout << a << endl; // 因为式传值，不改变
//    cout << b << endl; // 传引用会改变
//    cout << c << endl; // 因为式传值，不改变
//
//}


//// lambda 表达式直接不能相互赋值，因为他们的类型不一样 -- 看汇编,用vs看
//int main() {
//    [] {};
//    auto add = [](int a, int b) -> int { return a + b; };
//    auto sub = [](int a, int b) { return a - b; };
//    add(1, 2); // 调用 <lambda_ef40fe5bc5a973397e80dda597378044>::operator() (0862100h)
//    sub(1, 2); // 调用 <lambda_d852103dcf4f1550eb4af18bd087c4d6>::operator() (0862E20h)
//
//}


//class Rate {
//public:
//    Rate(double rate) : _rate(rate) {}
//
//    double operator()(double money, int year) { return money * _rate * year; }
//
//private:
//    double _rate;
//};
//
//// 查看汇编代码，其实底层差不多
//int main() {
//    // 函数对象
//    double rate = 0.49;
//    Rate r1(rate);
//    r1(10000, 2);
//    // lambda
//    auto r2 = [=](double monty, int year) -> double {
//        return monty * rate * year;
//    };
//    r2(10000, 2);
//    return 0;
//}

template<class F, class T>
double useF(F f, T t) {
    static int count = 0;
    cout << "count :" << ++count << endl;
    cout << "count :" << &count << endl;
    return f(t);
}

double func(double i) {
    return i / 2;
}

struct Function {
    double operator()(double d) {
        return d / 3;
    }
};



// 这里实例化了三份
//int main() {
//
//    // 函数名
//    cout << useF(func, 1) << endl;
//    // 函数对象
//    cout << useF(Function(), 1) << endl;
//    // lambda
//    cout << useF([](double d) -> double { return d / 3; }, 1) << endl;
//
//    return 0;
//}


//int f(int a, int b) {
//    return a + b;
//}
//
//struct Functor {
//public:
//    int operator()(int a, int b) {
//        return a + b;
//    }
//};
//
//class Plus {
//public:
//    static int plusi(int a, int b) {
//        return a + b;
//    }
//
//    double plusd(double a, double b) {
//        return a + b;
//    }
//};
//
//// 包装器使用
//int main() {
//    // 函数名(函数指针)
//    std::function<int(int, int)> func1 = f;
//    cout << func1(1, 2) << endl;
//
//    // 函数对象
//    std::function<int(int, int)> func2 = Functor();
//    cout << func2(1, 2) << endl;
//
//    // lambda表达式
//    std::function<int(int, int)> func3 = [](const int a, const int b) { return a + b; };
//    cout << func3(1, 2) << endl;
//
//    // 类的静态成员函数
//    std::function<int(int, int)> func4 = &Plus::plusi;
//    cout << func4(1, 2) << endl;
//
//    // 类的非静态成员函数
//    std::function<double(Plus, double, double)> func5 = &Plus::plusd;
//    cout << func5(Plus(), 1.1, 2.2) << endl;
//    return 0;
//}
//
//
//// 包装器  实例化一个模版
//int main() {
//
//    // 函数名
//    function<double(double)> func1 = func;
//    cout << useF(func1, 1) << endl;
//
//
//    // 函数对象
//    function<double(double)> func2 = Function();
//    cout << useF(func2, 1) << endl;
//
//
//    // lambda
//    function<double(double)> func3 = [](double d) -> double { return d / 3; };
//    cout << useF(func3, 1) << endl;
//
//
//    return 0;
//}

int f(int a, int b) {
    return a + b;
}

struct Functor {
public:
    int operator()(int a, int b) {
        return a + b;
    }
};

class Plus {
public:
    static int plusi(int a, int b) {
        return a + b;
    }

    double plusd(double a, double b) {
        return a - b;
    }
};

// bind绑定
int main() {

    // 类的静态成员函数
    std::function<int(int, int)> func4 = &Plus::plusi;
    cout << func4(1, 2) << endl;

    // 类的非静态成员函数
    std::function<double(double, double)> func5 = bind(&Plus::plusd, Plus(), placeholders::_1, placeholders::_2);
    cout << func5(1.1, 2.2) << endl;

    // 参数调换顺序
    std::function<double(double, double)> func6 = bind(&Plus::plusd, Plus(), placeholders::_2, placeholders::_1);
    cout << func6(1.1, 2.2) << endl;

    return 0;
}






