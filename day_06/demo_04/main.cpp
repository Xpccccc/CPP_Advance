#include <iostream>
#include <list>
#include "list.h"

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
//            cout << "string(char* str)" << endl;
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

// 把emplace_back的功能放到自己模拟实现的list中
//int main() {
//
//    list <xp::string> lt;
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
//    list <pair<xp::string, xp::string>> lt1;
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

int main() {

    xp::list <xp::string> lt;
    xp::string s1("hello");

    lt.push_back("dss");
    cout << "---------------------------" << endl;
    lt.emplace_back("dss"); // 直接构造  -- 直接给其类的构造函数的参数
    cout << "============================" << endl;
    lt.push_back(s1);
    cout << "---------------------------" << endl;
    lt.emplace_back(s1);

    cout << "============================" << endl;
    lt.push_back(move(s1));
    cout << "---------------------------" << endl;
    lt.emplace_back(move(s1));

    cout << "============================" << endl;
    cout << "============================" << endl;

    pair<xp::string, xp::string> kv1("xp", "xp");
    pair<xp::string, xp::string> kv2("zl", "zl");

    xp::list <pair<xp::string, xp::string>> lt1;
    lt1.push_back(kv1);
    cout << "---------------------------" << endl;
    lt1.emplace_back(kv1);
    cout << "============================" << endl;

    lt1.push_back(make_pair("hh", "hh"));
    cout << "---------------------------" << endl;
    lt1.emplace_back(make_pair("hh", "hh"));
    cout << "============================" << endl;

    lt1.push_back({"hh", "hh"});
    cout << "---------------------------" << endl;
    lt1.emplace_back("hh", "hh"); // 直接构造  -- 直接给其类的构造函数的参数


    return 0;
}