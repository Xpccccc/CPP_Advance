#include <iostream>

using namespace std;

//// 返回右值
//// 右值是指不能被修改的临时值，它们通常是表达式的结果或者临时对象。
//int funcr() {
//    static int ret = 1;
//    return ret;
//}
//
//// 返回左值
//// 左值是可以放在赋值操作符（=）的左边的表达式，因为它们具有地址，可以在内存中存储。左值可以是变量、数组元素或对象的成员等。
//// 右值也有地址，但是右值并不具有持久性。右值是临时的、短暂存在的值，可能是表达式的结果或者临时对象。
//// 右值通常不能取地址，因为它们可能不存储在内存中的具体位置，或者即使存在，也没有持久性。
//int &funcl() {
//    static int ret = 1;
//    return ret;
//}


//// 左值及左值引用
//// 左值：可以取地址
//int main() {
//// 以下的p、b、c、*p都是左值
//    int *p = new int(0);
//    int b = 1;
//    const int c = 2;
//
////    int* res1 = &funcr(); // 因为返回值是临时对象
//    int *res2 = &funcl();
//// 以下几个是对上面左值的左值引用
//    int *&rp = p;
//    int &rb = b;
//    const int &rc = c;
//    int &pvalue = *p;
//
//    int *&pres2 = res2;
//
//    return 0;
//}



//// 右值是指不能被修改的临时值，它们通常是表达式的结果或者临时对象。
//int main() {
//    double x = 1.1, y = 2.2;
//// 以下几个都是常见的右值
//    10;
//    x + y;
//    funcr();
//// 以下几个都是对右值的右值引用
//    int &&rr1 = 10;
//    double &&rr2 = x + y;
//    double &&rr3 = funcr();
//// 这里编译会报错：error C2106: “=”: 左操作数必须为左值
////    10 = 1;
////    x + y = 1;
////    funcr() = 1;
//
//
//    return 0;
//}


////需要注意的是右值是不能取地址的，但是给右值取别名后，会导致右值被存储到特定位置，且可以取到该位置的地址,也就是右值引用的属性是左值
//int main() {
//    double x = 1.1, y = 2.2;
//    int &&rr1 = 10;
//    const double &&rr2 = x + y;
//    rr1 = 20;
////    rr2 = 5.5; // 报错
//    return 0;
//}


////1. 左值引用只能引用左值，不能引用右值。
////2. 但是const左值引用既可引用左值，也可引用右值。
//int main() {
//    // 左值引用只能引用左值，不能引用右值。
//    int a = 10;
//    int &ra1 = a;  // ra为a的别名
//    //int& ra2 = 10;  // 编译失败，因为10是右值
//    // const左值引用既可引用左值，也可引用右值。
//    const int &ra3 = 10;
//    const int &ra4 = a;
//
////    ra3 = 1;
////    ra4 = 1;
//    return 0;
//}


////1. 右值引用只能右值，不能引用左值。
////2. 但是右值引用可以move以后的左值。
//int main() {
//    // 右值引用只能右值，不能引用左值。
//    int &&r1 = 10;
//
//    // error C2440: “初始化”: 无法从“int”转换为“int &&”
//    // message : 无法将左值绑定到右值引用
//    int a = 10;
////    int &&r2 = a;
//
//    // 右值引用可以引用move以后的左值
//    int &&r3 = move(a);
//    return 0;
//}



namespace xp {
    class string {
    public:
        typedef char *iterator;

        iterator begin() {
            return _str;
        }

        iterator end() {
            return _str + _size;
        }

        string(const char *str = "")
                : _size(strlen(str)), _capacity(_size) {
            //cout << "string(char* str)" << endl;
            _str = new char[_capacity + 1];
            strcpy(_str, str);
        }

        // s1.swap(s2)
        void swap(string &s) {
            ::swap(_str, s._str);
            ::swap(_size, s._size);
            ::swap(_capacity, s._capacity);
        }

        // 拷贝构造  -- 没有写右值引用的拷贝构造的时候，左值和右值的拷贝构造都走这个const string&
        string(const string &s)
                : _str(nullptr) {
            cout << "string(const string& s) -- 深拷贝" << endl;
            string tmp(s._str);
            swap(tmp);
        }

        // 赋值重载
        string &operator=(const string &s) {
            cout << "string& operator=(string s) -- 深拷贝" << endl;
            string tmp(s);
            swap(tmp);
            return *this;
        }

        // 移动构造   ---  右值
        // 右值引用的拷贝构造函数得到的是右值。
        // 右值引用的属性是左值，也就是s是左值，所以才可以被转移资源（使用swap，swap的形参是左值引用（string&））
        string(string &&s)
                : _str(nullptr), _size(0), _capacity(0) {
            cout << "string(string&& s) -- 移动语义" << endl;
            swap(s); // 转移s的资源给*this
        }
//
////
////        // 移动赋值
//        string &operator=(string &&s) {
//            cout << "string& operator=(string&& s) -- 移动语义" << endl;
//            swap(s);
//            return *this;
//        }

        ~string() {
            delete[] _str;
            _str = nullptr;
        }

        char &operator[](size_t pos) {
            assert(pos < _size);
            return _str[pos];
        }

        void reserve(size_t n) {
            if (n > _capacity) {
                char *tmp = new char[n + 1];
                strcpy(tmp, _str);
                delete[] _str;
                _str = tmp;
                _capacity = n;
            }
        }

        void push_back(char ch) {
            if (_size >= _capacity) {
                size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
                reserve(newcapacity);
            }
            _str[_size] = ch;
            ++_size;
            _str[_size] = '\0';
        }

        //string operator+=(char ch)
        string &operator+=(char ch) {
            push_back(ch);
            return *this;
        }

        const char *c_str() const {
            return _str;
        }

    private:
        char *_str;
        size_t _size;
        size_t _capacity; // 不包含最后做标识的\0
    };

    string to_string(int value) {
        bool flag = true;
        if (value < 0) {
            flag = false;
            value = 0 - value;
        }
        string str;
        while (value > 0) {
            int x = value % 10;
            value /= 10;
            str += ('0' + x);
        }
        if (flag == false) {
            str += '-';
        }
        std::reverse(str.begin(), str.end());
        return move(str); // 强制把str转右值 -- 去调用右值引用的拷贝构造
    }
}



//void func1(xp::string s) {}
//
//void func2(const xp::string &s) {}
//
//int main() {
//    xp::string s1("hello world");
//    // func1和func2的调用我们可以看到左值引用做参数减少了拷贝，提高效率的使用场景和价值
//    func1(s1); // 这里调用拷贝构造函数 ，用s1拷贝构造处理一个副本来初始化s
//    func2(s1);
//    // string operator+=(char ch) 传值返回存在深拷贝
//    // string& operator+=(char ch) 传左值引用没有拷贝提高了效率
//    s1 += '!';
//    return 0;
//}


//int main() {
//// 在xp::string to_string(int value)函数中可以看到，这里
//// 只能使用传值返回，传值返回会导致至少1次拷贝构造(如果是一些旧一点的编译器可能是两次拷贝构造)。
//
//    // 这里 xp::to_string(1234)的返回值是右值 -- 继续调用移动构造 ，移动构造+移动构造 = 移动构造
//    xp::string ret1 = xp::to_string(1234);
//    return 0;
//}

int main() {
// 在bit::string to_string(int value)函数中可以看到，这里
// 只能使用传值返回，传值返回会导致至少1次拷贝构造(如果是一些旧一点的编译器可能是两次拷贝构造)。

    // 这里 xp::to_string(1234)的返回值是右值 -- 继续调用移动构造 ，移动构造+移动构造 = 移动构造
    xp::string ret1;
    ret1 = xp::to_string(1234);
    return 0;
}

//int main() {
//    int &&r = 10; // 右值被右值引用后，右值引用的属性是左值，即r是左值
//    r++;
//    const int & rr = 1;
//    &rr;
//    &r;
//    return 0;
//}



//#include "list.h"
//
//
//int main() {
//    xp::list<xp::string> lt;
//    xp::string s1("123"); // s1是左值
////    lt.push_back(s1);
//    lt.push_back(move(s1));
//    cout << "=================" << endl;
//
//    lt.push_back(xp::string("222")); // 右值
//    cout << "=================" << endl;
//
//    lt.push_back("333"); // 右值
//    cout << "=================" << endl;
//    return 0;
//}










