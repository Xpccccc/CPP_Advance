#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std;

double Division(int a, int b) {
    // 当b == 0时抛出异常
    if (b == 0) {
        throw "Division by zero condition!";
    }
    return (double) a / (double) b;
}

int main() {
    try {
        vector<int> v(10, 5);
        // 这里如果系统内存不够也会抛异常
        v.reserve(1000000000000000);
        // 这里越界会抛异常
        v.at(10) = 100;
//        Division(1, 0);
    }
    catch (const exception &e) // 这里捕获父类对象就可以
    {
        cout << e.what() << endl;
    }
    catch (...) {
        cout << "Unkown Exception" << endl;
    }
    return 0;
}

//// 服务器开发中通常使用的异常继承体系
//class Exception {
//public:
//    Exception(const string &errmsg, int id)
//            : _errmsg(errmsg), _id(id) {}
//
//    virtual string what() const {
//        return _errmsg;
//    }
//
//protected:
//    string _errmsg;
//    int _id;
//};
//
//class SqlException : public Exception {
//public:
//    SqlException(const string &errmsg, int id, const string &sql)
//            : Exception(errmsg, id), _sql(sql) {}
//
//    virtual string what() const {
//        string str = "SqlException:";
//        str += _errmsg;
//        str += "->";
//        str += _sql;
//        return str;
//    }
//
//private:
//    const string _sql;
//};
//
//class CacheException : public Exception {
//public:
//    CacheException(const string &errmsg, int id)
//            : Exception(errmsg, id) {}
//
//    virtual string what() const {
//        string str = "CacheException:";
//        str += _errmsg;
//        return str;
//    }
//};
//
//class HttpServerException : public Exception {
//public:
//    HttpServerException(const string &errmsg, int id, const string &type)
//            : Exception(errmsg, id), _type(type) {}
//
//    virtual string what() const {
//        string str = "HttpServerException:";
//        str += _type;
//        str += ":";
//        str += _errmsg;
//        return str;
//    }
//
//private:
//    const string _type;
//};
//
//void SQLMgr() {
//    srand(time(0));
//    if (rand() % 7 == 0) {
//        throw SqlException("权限不足", 100, "select * from name = '张三'");
//    }
//    //throw "xxxxxx";
//}
//
//void CacheMgr() {
//    srand(time(0));
//    if (rand() % 5 == 0) {
//        throw CacheException("权限不足", 100);
//    } else if (rand() % 6 == 0) {
//        throw CacheException("数据不存在", 101);
//    }
//    SQLMgr();
//}
//
//void HttpServer() {
//    // ...
//    srand(time(0));
//    if (rand() % 3 == 0) {
//        throw HttpServerException("请求资源不存在", 100, "get");
//    } else if (rand() % 4 == 0) {
//        throw HttpServerException("权限不足", 101, "post");
//    }
//    CacheMgr();
//}
//
//
//// 异常
//int main() {
//    while (1) {
//        sleep(1);
//        try {
//            HttpServer();
//        } catch (const Exception &e) // 这里捕获父类对象就可以
//        {
//            // 多态
//            cout << e.what() << endl;
//        }
//        catch (...) {
//            cout << "Unkown Exception" << endl;
//        }
//    }
//    return 0;
//}

// 异常规范 -- 没什么用
//double Division(int a, int b) throw() {
//    // 当b == 0时抛出异常
//    if (b == 0) {
//        throw "Division by zero condition!";
//    }
//    return (double) a / (double) b;
//}
//
//void Func() noexcept {
//    Division(1, 2);
//}



//double Division(int a, int b) {
//    // 当b == 0时抛出异常
//    if (b == 0) {
//        throw "Division by zero condition!";
//    }
//    return (double) a / (double) b;
//}
//
//// 构造析构不要抛异常
//struct AA {
//    AA(int a, int b) {
//        _a = 1;
//        _c = new int(1);
//        try {
//            Division(a, b); // 这里抛异常了，b就没初始化
//        } catch (const exception &e) {
//            cout << e.what() << endl;
//        } catch (const char *msg) {
//            cout << msg << endl;
//        } catch (...) {
//            cout << "unknow error" << endl;
//        }
//
//        _b = b;
//
//    }
//
//    ~AA() {
//        try {
//            Division(_a, _b); // 这里抛异常了，c就没释放空间
//        } catch (exception e) {
//            cout << e.what() << endl;
//        }
//        delete _c;
//    }
//
//    int _a;
//    int _b;
//    int *_c;
//};
//
//int main() {
//    try {
//        AA aa(1, 0);
//    } catch (const exception &e) {
//        cout << e.what() << endl;
//    }
//    return 0;
//}

//// 异常的重新抛出
//double Division(int a, int b) {
//    // 当b == 0时抛出异常
//    if (b == 0) {
//        throw "Division by zero condition!";
//    }
//    return (double) a / (double) b;
//}
//
//void Func() {
//    // 这里可以看到如果发生除0错误抛出异常，另外下面的array没有得到释放。
//    // 所以这里捕获异常后并不处理异常，异常还是交给外面处理，这里捕获了再
//    // 重新抛出去。
//    int *array = new int[10];
//    try {
//        int len, time;
//        cin >> len >> time;
//        cout << Division(len, time) << endl;
//    }
//    catch (...) {
//        cout << "delete []" << array << endl;
//        delete[] array;
//        throw;
//    }
//    // ...
//    cout << "delete []" << array << endl;
//    delete[] array;
//}
//
//int main() {
//    try {
//        Func();
//    }
//    catch (const char *errmsg) {
//        cout << errmsg << endl;
//    }
//    return 0;
//}


//// 异常的抛出和捕获以及匹配规则
//double Division(int a, int b) {
//    // 当b == 0时抛出异常
//    if (b == 0)
//        throw "Division by zero condition!";
//    else
//        return ((double) a / (double) b);
//}
//
//void Func() {
//    int len, time;
//    cin >> len >> time;
//    cout << Division(len, time) << endl;
//}
//
//int main() {
//    try {
//        Func();
//    }
//    catch (const char *errmsg) {
//        cout << errmsg << endl;
//    }
//    catch (...) {
//        cout << "unkown exception" << endl;
//    }
//    return 0;
//}

