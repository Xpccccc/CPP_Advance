#include <iostream>
#include <memory>
#include <cstdlib>
#include <functional>

using namespace std;

// shared_ptr的模拟实现，带删除器接口
namespace xp {
    template<class T>
    class shared_ptr {
    public:

        template<class D>
        shared_ptr(T *ptr, D del) : _ptr(ptr), _del(del) {
            _pcount = new int(1); // 构造的时候引用计数设置为1
        }

        shared_ptr(T *ptr = nullptr) : _ptr(ptr) {
            _pcount = new int(1); // 构造的时候引用计数设置为1
        }

        shared_ptr(const shared_ptr<T> &sp) {
            _ptr = sp._ptr;// 先指向同一块空间
            _pcount = sp._pcount;
            // 再引用计数++
            ++(*_pcount);
        }

        shared_ptr<T> &operator=(const shared_ptr<T> &sp) {
            if (_ptr != sp._ptr) {
                // 当前指针指向的引用计数--，--后引用计数等于0就释放
                release();

                // sp指向的引用计数++
                _ptr = sp._ptr;
                _pcount = sp._pcount;
                ++(*_pcount);
            }
            return *this;
        }

        void release() {
            if (--(*_pcount) == 0) {
                if (_ptr) {
                    cout << "delete _ptr" << endl;
//                    delete _ptr;
                    _del(_ptr);
                    delete _pcount;
                }
            }
        }

        ~shared_ptr() {
            release();
        }

        // 重载*,->使其获得指针的行为
        T &operator*() {
            return *_ptr;
        }

        T *operator->() {
            return _ptr;
        }

        int use_count() {
            return *_pcount;
        }

        T *get() const {
            return _ptr;
        }

    private:
        function<void(T *)> _del = [](T *ptr) { delete ptr; };
        T *_ptr;
        int *_pcount;

    };

    // weak_ptr没有引用计数，相当于就是我们之前写的SmartPtr
    template<class T>
    class weak_ptr {
    public:
        weak_ptr(T *ptr) : _ptr(ptr) {}

        weak_ptr(shared_ptr<T> &wp) {
            _ptr = wp.get();
        }

        weak_ptr<T> &operator=(shared_ptr<T> &wp) {
            _ptr = wp.get();
            return *this;
        }

        T &operator*() {
            return *_ptr;
        }

        T *operator->() {
            return _ptr;
        }

    private:
        T *_ptr;
    };
}

// 仿函数删除器
template<class T>
struct FreeFunc {
    void operator()(T *ptr) {
        cout << "free :" << ptr << endl;
        free(ptr);
    }

};


template<class T>
struct DeleteArray {
    void operator()(T *ptr) {
        cout << "delete[] :" << ptr << endl;
        delete[] ptr;
    }

};


int main() {

    FreeFunc<int> freeFunc;
    xp::shared_ptr<int> sp1((int *) malloc(4), freeFunc);

    DeleteArray<int> deleteArray;
    xp::shared_ptr<int> sp2(new int[10], deleteArray);
    // lambda 表达式删除器
    xp::shared_ptr<int> sp3(new int, [](int *ptr) {
        cout << "sp3 delete" << endl;
        delete ptr;
    });

    xp::shared_ptr<FILE> sp4(fopen("hello.txt", "w"), [](FILE *pf) {
        cout << "sp4 delete" << endl;
        fclose(pf);
    });

    return 0;
}


//// 仿函数删除器
//template<class T>
//struct FreeFunc {
//    void operator()(T *ptr) {
//        cout << "free :" << ptr << endl;
//        free(ptr);
//    }
//
//};
//
//
//template<class T>
//struct DeleteArray {
//    void operator()(T *ptr) {
//        cout << "delete[] :" << ptr << endl;
//        delete[] ptr;
//    }
//
//};
//
//// shared_ptr的删除器使用
//int main() {
//
//    FreeFunc<int> freeFunc;
//    shared_ptr<int> sp1((int *) malloc(4), freeFunc);
//
//    DeleteArray<int> deleteArray;
//    shared_ptr<int> sp2(new int[10], deleteArray);
//    // lambda 表达式删除器
//    shared_ptr<int> sp3(new int, [](int *ptr) { delete ptr; });
//
//    shared_ptr<FILE> sp4(fopen("hello.txt", "w"), [](FILE *pf) { fclose(pf); });
//
//    return 0;
//}

//// shared_ptr的模拟实现
//namespace xp {
//    template<class T>
//    class shared_ptr {
//    public:
//        shared_ptr(T *ptr = nullptr) : _ptr(ptr) {
//            _pcount = new int(1); // 构造的时候引用计数设置为1
//        }
//
//        shared_ptr(const shared_ptr<T> &sp) {
//            _ptr = sp._ptr;// 先指向同一块空间
//            _pcount = sp._pcount;
//            // 再引用计数++
//            ++(*_pcount);
//        }
//
//        shared_ptr<T> &operator=(const shared_ptr<T> &sp) {
//            if (_ptr != sp._ptr) {
//                // 当前指针指向的引用计数--，--后引用计数等于0就释放
//                release();
//
//                // sp指向的引用计数++
//                _ptr = sp._ptr;
//                _pcount = sp._pcount;
//                ++(*_pcount);
//            }
//            return *this;
//        }
//
//        void release() {
//            if (--(*_pcount) == 0) {
//                if (_ptr) {
//                    cout << "delete _ptr" << endl;
//                    delete _ptr;
//                    delete _pcount;
//                }
//            }
//        }
//
//        ~shared_ptr() {
//            release();
//        }
//
//        // 重载*,->使其获得指针的行为
//        T &operator*() {
//            return *_ptr;
//        }
//
//        T *operator->() {
//            return _ptr;
//        }
//
//        int use_count() {
//            return *_pcount;
//        }
//
//        T *get() const {
//            return _ptr;
//        }
//
//    private:
//        T *_ptr;
//        int *_pcount;
//    };
//
//    // weak_ptr没有引用计数，相当于就是我们之前写的SmartPtr
//    template<class T>
//    class weak_ptr {
//    public:
//        weak_ptr(T *ptr) : _ptr(ptr) {}
//
//        weak_ptr(shared_ptr<T> &wp) {
//            _ptr = wp.get();
//        }
//
//        weak_ptr<T> &operator=(shared_ptr<T> &wp) {
//            _ptr = wp.get();
//            return *this;
//        }
//
//        T &operator*() {
//            return *_ptr;
//        }
//
//        T *operator->() {
//            return _ptr;
//        }
//
//    private:
//        T *_ptr;
//    };
//}
//
//struct ListNode {
//    int _data;
////    xp::shared_ptr<ListNode> _prev;
////    xp::shared_ptr<ListNode> _next;
//    xp::weak_ptr<ListNode> _prev;
//    xp::weak_ptr<ListNode> _next;
//
//    ListNode(int val = 0) : _data(val), _prev(nullptr), _next(nullptr) {}
//
//    ~ListNode() {
//        cout << "~ListNode()" << endl;
//    }
//};
//
//// shared_ptr的循环引用问题
//int main() {
//    xp::shared_ptr<ListNode> node1(new ListNode);
//    xp::shared_ptr<ListNode> node2(new ListNode);
//    cout << node1.use_count() << endl;
//    cout << node2.use_count() << endl;
//
//    node1->_next = node2;
//    node2->_prev = node1;
//    cout << node1.use_count() << endl;
//    cout << node2.use_count() << endl;
//    return 0;
//}

//int main() {
//    xp::shared_ptr<int> sp1(new int(1));
//    xp::shared_ptr<int> sp2(new int(3));
//    cout << sp2.use_count() << endl;
//
//    *sp1 += 1;
//    *sp2 += 1;
//
//    xp::shared_ptr<int> sp3(sp2);
//    cout << sp2.use_count() << endl;
//
//    sp1 = sp2;
//    cout << sp2.use_count() << endl;
//
//    return 0;
//}


//// shared_ptr的使用
//int main() {
//    shared_ptr<int> sp1(new int(1));
//    shared_ptr<int> sp2(new int(3));
//    cout << sp2.use_count() << endl;
//
//    *sp1 += 1;
//    *sp2 += 1;
//
//    shared_ptr<int> sp3(sp2);
//    cout << sp2.use_count() << endl;
//
//    sp1 = sp2;
//    cout << sp2.use_count() << endl;
//
//    return 0;
//}

//// unique_ptr的模拟实现
//namespace xp {
//    template<class T>
//    class unique_ptr {
//    public:
//        unique_ptr(T *ptr = nullptr) : _ptr(ptr) {
//
//        }
//
//        unique_ptr(unique_ptr<T> &ap) = delete;
//
//        unique_ptr<T> &operator=(unique_ptr<T> &ap) = delete;
//
//        ~unique_ptr() {
//            if (_ptr)
//                delete _ptr;
//        }
//
//        // 重载*,->使其获得指针的行为
//        T &operator*() {
//            return *_ptr;
//        }
//
//        T *operator->() {
//            return _ptr;
//        }
//
//    private:
//        T *_ptr;
//    };
//}
//
//int main() {
//    xp::unique_ptr<int> ap1(new int(1));
//    xp::unique_ptr<int> ap2(new int(2));
//    *ap1 += 10;
//    *ap2 += 10;
//
////    xp::unique_ptr<int> ap3(ap2); // 不允许拷贝构造
//    // *ap2 += 1;
//
////    ap3 = ap1; // 不允许赋值
//    return 0;
//}

//// unique_str的使用
//int main() {
//    unique_ptr<int> ap1(new int(1));
//    unique_ptr<int> ap2(new int(2));
//    *ap1 += 10;
//    *ap2 += 10;
//
//    // unique_ptr<int> ap3(ap2); // 不允许拷贝构造
//
//    // ap3 = ap1; // 不允许赋值
//    return 0;
//}

//// auto_ptr的模拟实现
//namespace xp {
//    template<class T>
//    class auto_ptr {
//    public:
//        auto_ptr(T *ptr = nullptr) : _ptr(ptr) {
//
//        }
//
//        auto_ptr(auto_ptr<T> &ap) {
//            _ptr = ap._ptr;
//            ap._ptr = nullptr;
//        }
//
//        auto_ptr<T> &operator=(auto_ptr<T> &ap) {
//            if (_ptr != ap._ptr) {
//                // 释放当前对象资源
//                if (_ptr)
//                    delete _ptr;
//                _ptr = ap._ptr;
//                ap._ptr = nullptr;
//            }
//            return *this;
//        }
//
//        ~auto_ptr() {
//            if (_ptr)
//                delete _ptr;
//        }
//
//        // 重载*,->使其获得指针的行为
//        T &operator*() {
//            return *_ptr;
//        }
//
//        T *operator->() {
//            return _ptr;
//        }
//
//    private:
//        T *_ptr;
//    };
//}
//
//int main() {
//    xp::auto_ptr<int> ap1(new int(1));
//    xp::auto_ptr<int> ap2(new int(2));
//    *ap1 += 10;
//    *ap2 += 10;
//
//    xp::auto_ptr<int> ap3(ap2);
//    // *ap2 += 1;
//
//    ap3 = ap1;
//    return 0;
//}




//// VS下才能使用，CLion不支持auto_ptr
//int main() {
//    auto_ptr<int> ap1(new int(1));
//    auto_ptr<int> ap2(new int(2));
//    auto_ptr<int> ap3(ap2);
//
//    *ap1 += 10;
//    *ap2 += 10;
//    *ap3 += 10;
//
//    return 0;
//}


// //  智能指针简化版
//template<class T>
//class SmartPtr {
//public:
//    SmartPtr(T *ptr = nullptr) : _ptr(ptr) {
//
//    }
//
//    ~SmartPtr() {
//        if (_ptr)
//            delete _ptr;
//    }
//
//    // 重载*,->使其获得指针的行为
//    T &operator*() {
//        return *_ptr;
//    }
//
//    T *operator->() {
//        return _ptr;
//    }
//
//private:
//    T *_ptr;
//};
//
//class Date {
//public:
//    Date() = default;
//
//    Date(int year, int month, int day) : _year(year), _month(month), _day(day) {}
//
//    int &GetYear() {
//        return _year;
//    }
//
//    int &GetMonth() {
//        return _month;
//    }
//
//    int &GetDay() {
//        return _day;
//    }
//
//private:
//    int _year;
//    int _month;
//    int _day;
//};
//
//int div() {
//    int a, b;
//    cin >> a >> b;
//    if (b == 0)
//        throw invalid_argument("除0错误");
//    return a / b;
//}
//
//void Func() {
//    SmartPtr<int> sp1(new int); //这里就算出现异常，也不会存在内存释放问题，因为sp1出函数的时候会调用析构函数
//    SmartPtr<int> sp2(new int);
//    *sp1 += 10;
//    *sp2 += 10;
//
//    SmartPtr<Date> sp3 = (new Date);
//    sp3->GetYear() = 1999;
//    sp3->GetMonth() = 11;
//    sp3->GetDay() = 14;
//    cout << div() << endl;
//}
//
//int main() {
//    try {
//        Func();
//    }
//    catch (const exception &e) {
//        cout << e.what() << endl;
//    } catch (...) {
//        cout << "unknow error" << endl;
//    }
//    return 0;
//}




//// 内存泄漏
//int div() {
//    int a, b;
//    cin >> a >> b;
//    if (b == 0)
//        throw invalid_argument("除0错误");
//    return a / b;
//}
//
//void Func() {
//// 1、如果p1这里new 抛异常会如何？
//// 2、如果p2这里new 抛异常会如何？
//// 3、如果div调用这里又会抛异常会如何？
////    int* p1 = new int;
////    int* p2 = new int;
////    cout << div() << endl;
////    delete p1;
////    delete p2;
//
//    int *p1, *p2;
//
//    p1 = new int; // p1抛异常直接退出就行了
//    try {
//        p2 = new int; // p2抛异常的时候，p1已经申请好了，必须释放p1
//        cout << div() << endl;
//    } catch (...) {
//        // 这里捕获异常 需要p1释放
//        delete p1;
//        cout << "unknow error" << endl;
//        throw;// 交给上一层栈帧处理
//    }
//    delete p1;
//    delete p2;
//}
//
//int main() {
//    try {
//        Func();
//    }
//    catch (exception &e) {
//        cout << e.what() << endl;
//    } catch (...) {
//        cout << "unknow error" << endl;
//    }
//    return 0;
//}
