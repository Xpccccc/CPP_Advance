#include <iostream>
#include <list>

using namespace std;

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
            cout << "string(char* str)" << endl;
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

        // 移动构造
        string(string &&s) {
            cout << "string(string &&s) -- 移动语义" << endl;
            swap(s); // 转移s的资源给*this
        }

        // 赋值重载
        string &operator=(const string &s) {
            cout << "string& operator=(string s) -- 深拷贝" << endl;
            string tmp(s);
            swap(tmp);
            return *this;
        }

        // 移动赋值
        string &operator=(string &&s) {
            cout << "string& operator=(string&& s) -- 移动语义" << endl;
            swap(s);
            return *this;
        }

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
        char *_str = nullptr;
        size_t _size = 0;
        size_t _capacity = 0; // 不包含最后做标识的\0
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
        return str;
    }
}


//#include "list.h"
//
//// 右值引用使用move引用左值的场景
//int main() {
//    xp::list<xp::string> lt;
//    xp::string s1("123"); // s1是左值
////    lt.push_back(s1);
//    move(s1);
//    lt.push_back(move(s1)); // 这里move以后，s1的资源就被掠夺了，置空了，其实不是这么用的
//    cout << "=================" << endl;
//
//    lt.push_back(xp::string("222")); // 右值
//    cout << "=================" << endl;
//
//    lt.push_back("333"); // 右值
//    cout << "=================" << endl;
//    return 0;
//}

//void Fun(int &val) {
//    cout << "int& val" << endl;
//}
//
//void Fun(const int &val) {
//    cout << "const int &val" << endl;
//}
//
//void Fun(int &&val) {
//    cout << "int&& val" << endl;
//}
//
//void Fun(const int &&val) {
//    cout << "const int&& val" << endl;
//}
//
//// 完美转发
//template<class T>
//void Transit(T &&val) {
//    Fun(forward<T>(val));
//}
//
//int main() {
//    int a = 10; // 左值
//    Transit(a);
//
//    const int b = 11; // const 左值
//    Transit(b);
//
//    Transit(10);// 右值
//    Transit(move(b));// const 右值
//
//    return 0;
//}

//// 新增两个默认成员函数
//class Person {
//public:
//    Person(const char *name = "", int age = 0)
//            : _name(name), _age(age) {}
//
//    void Swap(Person &p) {
//        std::swap(_age, p._age);
//        std::swap(_name, p._name);
//    }
//
////  移动构造  --  只写了移动构造，那么编译器移动赋值就不会生成了，赋值重载也不会生成
////    Person(Person &&p) {
////        Swap(p);
////    }
//
////  移动赋值  --  只写了移动赋值，那么编译器移动构造就不会生成了，拷贝构造也不会生成
////    Person &operator=(Person &&p) {
////        Swap(p);
////        return *this;
////    }
//
//
////    Person(const Person &p) : _name(p._name), _age(p._age) {}
////
////    Person &operator=(const Person &p) {
////        if (this != &p) {
////            _name = p._name;
////            _age = p._age;
////        }
////        return *this;
////    }
////
////    ~Person() {}
//
//private:
//    xp::string _name;
//    int _age;
//};
//
//
//int main() {
//    Person s1;
//    Person s2 = s1;
//    Person s3 = move(s1); // 调用默认的移动构造，默认的移动构造去调用string的移动构造
//    Person s4;
//    s4 = move(s2); // 调用默认的移动赋值，默认的移动赋值去调用string的移动赋值
//    return 0;
//}


//// 关键值delete 、 default
//class Person {
//public:
//    Person(const char *name = "", int age = 0)
//            : _name(name), _age(age) {}
//
//    Person(const Person &p) = default;
//
//    Person(Person &&p) = default;
//
//    Person &operator=(Person &&p) = default;
//
//    //Person(Person &&p) = delete;
//    //Person &operator=(Person &&p) = delete;
//
//private:
//    xp::string _name;
//    int _age;
//};
//
//
//int main() {
//    Person s1;
//    Person s2 = s1;
//    Person s3 = move(s1); // 调用默认的移动构造，默认的移动构造去调用string的移动构造
//    Person s4;
//    s4 = move(s2); // 调用默认的移动赋值，默认的移动赋值去调用string的移动赋值
//    return 0;
//}



//template<class ...Args>
//void Showlist(Args... args) {
//    Showlist(args...);
//}


//// 编译时递归！
//template<class T>
//void Showlist(const T& value) {
//    cout << value << endl;
//}
//
//template<class T, class ...Args>
//void Showlist(T value, Args... args) {
//    cout << value << " ";
//    Showlist(args...);
//}
//
//
//int main() {
//    Showlist(1);
//    Showlist(1, 2);
//    Showlist(1, 2, 'a');
//    Showlist(1, 2, 'a', "hello");
//    Showlist(1, 2, 'a', "hello", string("你好"));
//    return 0;
//}


//#include "list.h"
//
//// emplace支持可变参数
//// emplace系列，针对浅拷贝的类，如果写插入对象的参数，可以减少拷贝，直接构造
//// 浅拷贝的类，减少一次拷贝构造
//// 深拷贝的类，减少一次移动构造
//// 推荐emplace的用法是直接给其类的构造函数的参数 ， 这样就只构造，不拷贝构造
//int main() {
//
//    list<xp::string> lt;
//    xp::string s1("hello");
//
//    lt.push_back("dss");
//    cout << "---------------------------" << endl;
//    lt.emplace_back("dss"); // 直接构造  -- 直接给其类的构造函数的参数
//    cout << "============================" << endl;
//    lt.push_back(s1);
//    cout << "---------------------------" << endl;
//    lt.emplace_back(s1);
//
//    cout << "============================" << endl;
//    lt.push_back(move(s1));
//    cout << "---------------------------" << endl;
//    lt.emplace_back(move(s1));
//
//    cout << "============================" << endl;
//    cout << "============================" << endl;
//
//    pair<xp::string, xp::string> kv1("xp", "xp");
//    pair<xp::string, xp::string> kv2("zl", "zl");
//
//    list<pair<xp::string, xp::string>> lt1;
//    lt1.push_back(kv1);
//    cout << "---------------------------" << endl;
//    lt1.emplace_back(kv1);
//    cout << "============================" << endl;
//
//    lt1.push_back(make_pair("hh", "hh"));
//    cout << "---------------------------" << endl;
//    lt1.emplace_back(make_pair("hh", "hh"));
//    cout << "============================" << endl;
//
//    lt1.push_back({"hh", "hh"});
//    cout << "---------------------------" << endl;
//    lt1.emplace_back("hh", "hh"); // 直接构造  -- 直接给其类的构造函数的参数
//
//
//    return 0;
//}


//// 可变参数模版的另一种调用
//template<class T>
//void PrintArgs(T val) {
//    cout << val << " ";
//}
//
//template<class ...Args>
//void Showlist(Args... args) {
//    int arr[] = {(PrintArgs(args), 0)...};
//    cout << endl;
//}
//
//int main() {
//    Showlist(1);
//    Showlist(1, 2, 3);
//    Showlist(1, 2, 3, "hello");
//    Showlist(1, 2, 3, "hello", 'a');
//    Showlist(1, 2, 3, "hello", 'a', string("nihao"));
//    return 0;
//}




