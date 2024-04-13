#include <iostream>
#include <vector>
#include <map>

using namespace std;


//// C++11 新特性
//struct Point {
//    int _x;
//    int _y;
//};

//// {} 列表初始化
//int main() {
//    int array1[] = {1, 2, 3, 4, 5};
//    int array2[]{1, 2, 3, 4, 5};
//    int array3[5] = {0};
//    Point p1 = {1, 2};
//    Point p2{1, 2};
//    return 0;
//}

//class Date {
//public:
//    Date(int year, int month, int day)
//            : _year(year), _month(month), _day(day) {
//        cout << "Date(int year, int month, int day)" << endl;
//    }
//
//private:
//    int _year;
//    int _month;
//    int _day;
//};
//
//int main() {
//    Date d1(2022, 1, 1); // old style
//    // C++11支持的列表初始化，这里会调用构造函数初始化
//    Date d2{2022, 1, 2};
//    Date d3 = {2022, 1, 3}; // 隐式类型转换 构造+拷贝构造 = 构造
//
//    Date *d4 = new Date[3]{d1, d2, d3};
//    Date *d5 = new Date[3]{{2022, 1, 2}, {2022, 1, 2}, {2022, 1, 2}}; // 构造+拷贝构造 = 构造
//    return 0;
//}


//// initializer_list<T>
//int main() {
//    // the type of il is an initializer_list
//    auto il = {10, 20, 30};
//
//    // initializer_list<T>的  构造 + 拷贝构造 = 构造
//    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//
//    for (auto e: v) {
//        cout << e << " ";
//    }
//    cout << endl;
//
//    // initializer_list<T>的赋值
//    v = {1, 2, 3};
//    for (auto e: v) {
//        cout << e << " ";
//    }
//    cout << endl;
//
//    char i = 1;
//    cout << typeid(il).name() << endl;
//    cout << typeid(i).name() << endl; // 打印类型
//
//
//    pair<string, string> kv1("sort", "排序");
//    pair<string, string> kv2("insert", "插入");
//    map<string, string> dict1 = {kv1, kv2}; // pair<string,string> 拷贝构造 pair<const string,string>
//    map<string, string> dict2 = {{"sort",   "排序"},
//                                 {"insert", "插入"}};// pair<const char* ,const char*>拷贝构造 pair<string,string>
//    // 因为pair的拷贝构造是带模版参数的，不强制类型一样，但是得能正确赋值
//    return 0;
//}


//// auto类型推导 -- 不推荐做返回值
//int main() {
//    int i = 10;
//    auto p = &i;
//    auto pf = strcpy;
//    cout << typeid(p).name() << endl;
//    cout << typeid(pf).name() << endl;
//    map<string, string> dict = {{"sort",   "排序"},
//                                {"insert", "插入"}};
//    //map<string, string>::iterator it = dict.begin();
//    auto it = dict.begin();
//    return 0;
//}


//// decltype的一些使用使用场景
template<class T1, class T2>
void F(T1 t1, T2 t2) {
    decltype(t1 * t2) ret;
    cout << typeid(ret).name() << endl;
}

int main() {
    const int x = 1;
    double y = 2.2;
    decltype(x * y) ret; // ret的类型是double
    decltype(&x) p; // p的类型是int*
    cout << typeid(ret).name() << endl;
    cout << typeid(p).name() << endl;
    F(1, 'a');
    return 0;
}


