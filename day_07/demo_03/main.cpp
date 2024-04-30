#include <iostream>

using namespace std;


// 设计一个类，只能创建一个对象（单例模式）
// 懒汉模式：如果单例对象构造十分耗时或者占用很多资源，比如加载插件啊， 初始化网络连接啊，读取文件啊等等，
// 而有可能该对象程序运行时不会用到，那么也要在程序一开始就进行初始化，就会导致程序启动时非常的缓慢。 所以这种情况使用懒汉模式（延迟加载）更好。
class Singleton {
public:

    // 这里涉及到线程安全问题，需要加锁，后面学了线程再补充
    static Singleton *GetInstance() {
        if (!_psl) // 如果_psl为空，就创建对象，否则（已经有对象了）不创建
            _psl = new Singleton(3, 4, new int(10));
//            _psl = new Singleton;
        return _psl;
    }

    void Debug() {
        cout << "_x :" << _x << " _y:" << _y << " _p :" << _p << endl;
//        cout << "_x :" << _x << " _y:" << _y << " _p :" << _p << " *_p:" << *_p << endl;
    }


    static void DelInstance() {
        if (_psl) {
            delete _psl;
            _psl = nullptr;
        }
    }

private:
    int _x;
    int _y;
    int *_p;

    Singleton(int x = 1, int y = 2, int *p = nullptr) : _x(x), _y(y), _p(p) {}

    // 防止通过拷贝来创建新对象
    Singleton(const Singleton &sl) = delete;

    Singleton &operator=(const Singleton &sl) = delete;

    ~Singleton() {
        cout << "把数据写入文件" << endl;
        delete _p;
        _p = nullptr;
    }

    static Singleton *_psl;

    // 内部类
    class GC {
    public:
        ~GC() {
            Singleton::DelInstance();
        }
    };

    static GC gc;
};

Singleton *Singleton::_psl = nullptr;  // 初始化为nullptr，表明当前还没调用过
Singleton::GC Singleton::gc;

int main() {
    Singleton *psl = Singleton::GetInstance();
    psl->Debug();
    Singleton *psl1 = Singleton::GetInstance();
    psl1->Debug();

//    psl->DelInstance();
    cout << "=====================" << endl;

    return 0;
}

//// 饿汉模式：就是说不管你将来用不用，程序启动时就创建一个唯一的实例对象。
//class Singleton {
//public:
//    static Singleton *GetInstance() {
//        return &sl;
//    }
//
//    void Debug() {
//        cout << "_x :" << _x << " _y:" << _y << " _p :" << _p << " *_p:" << *_p << endl;
//    }
//
//private:
//    int _x;
//    int _y;
//    int *_p;
//
//    Singleton(int x = 1, int y = 2, int *p = nullptr) : _x(x), _y(y), _p(p) {}
//
//    // 防止通过拷贝来创建新对象
//    Singleton(const Singleton &sl) = delete;
//
//    Singleton &operator=(const Singleton &sl) = delete;
//
//    static Singleton sl;
//};
//
//Singleton Singleton::sl = {3, 4, new int(10)};  // 在程序入口之前就完成单例对象的初始化
//
//int main() {
//    Singleton *psl = Singleton::GetInstance();
//    psl->Debug();
//    Singleton *psl1 = Singleton::GetInstance();
//    psl1->Debug();
//
//    return 0;
//}

//// 设计一个类，不能被继承
//class Base final {
//
//};
//
////class Derive:public Base{}; // 报错


//class Base {
//private:
//    Base() {}
//};
//
//class Drive : public Base {
//
//};
//
//int main() {
////    Drive d; // 报错
//    return 0;
//}

//// 设计一个类，只能在栈上创建对象
//class CreateHeap {
//public:
//    static CreateHeap Create(int x, int y) {
//        return CreateHeap(x, y);
//    }
//
//    void Debug() {
//        cout << _x << " " << _y << endl;
//    }
//
//    // 重载operator new 和 operator delete
//    void *operator new(size_t size) = delete;
//
//    void operator delete(void *ptr) = delete;
//
//private:
//    CreateHeap(int x = 1, int y = 2) : _x(x), _y(y) {}
//
////    CreateHeap(const CreateHeap &cnp) = delete;
//
//    int _x;
//    int _y;
//};
//
//int main() {
//    // 不能直接使用构造函数，不然该对象就是栈上的
////    CreateHeap ch;
//    CreateHeap pcn = CreateHeap::Create(3, 7);
////    CreateHeap *pcn1 = new CreateHeap(pcn);// 报错，new的属性是delete
//
////    CreateHeap *pcn1 = new CreateHeap(pcn);// 报错，拷贝构造没定义
//
//    pcn.Debug();
//    return 0;
//}

//// 设计一个类，只能在堆上创建对象
//class CreateHeap {
//public:
//    static CreateHeap *Create(int x, int y) {
//        return new CreateHeap(x, y);
//    }
//
//    void Debug() {
//        cout << _x << " " << _y << endl;
//    }
//
//private:
//    CreateHeap(int x = 1, int y = 2) : _x(x), _y(y) {}
//
//    CreateHeap(const CreateHeap& cnp) = delete;
//    int _x;
//    int _y;
//};
//
//int main() {
//    // 不能直接使用构造函数，不然该对象就是栈上的
////    CreateHeap ch;
//    CreateHeap *pcn = CreateHeap::Create(3, 7);
//    pcn->Debug();
//}

//// 设计一个类，不能被拷贝
//class CannotCopy {
//public:
//    CannotCopy(){};
//    CannotCopy(const CannotCopy &cnp) = delete;
//
//    CannotCopy &operator=(const CannotCopy &cnp) = delete;
//};
//
//
//// 特殊类设计
//int main() {
//    CannotCopy cnp1;
////    CannotCopy cnp2(cnp1);
////    CannotCopy cnp3 = cnp1;
//    CannotCopy cnp4;
////    cnp4 = cnp1;
//
//    return 0;
//}