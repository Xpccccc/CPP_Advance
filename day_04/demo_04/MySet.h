//
// Created by 徐鹏 on 2024/4/1.
//

#ifndef DEMO_04_MYSET_H
#define DEMO_04_MYSET_H

#endif //DEMO_04_MYSET_H


namespace xp {
    template<class K>
    class set {
        // 用来取出key
        struct SetKeyofT {
            K operator()(const K &key) {
                return key;
            }
        };

    public:

        // 在类模版里取iterator需要使用到typename，指定这个iterator是类型
        // 否则不知道是静态成员变量还是类型，因为他们的定义语法是一样的
        typedef typename RBTree<const K, K, SetKeyofT>::iterator iterator;
        typedef typename RBTree<const K, K, SetKeyofT>::iterator const_iterator;

        iterator begin() {
            return _t.begin();
        }


        iterator end() {
            return _t.end();
        }

        const_iterator begin() const {
            return _t.cbegin();
        }


        const_iterator end() const {
            return _t.cend();
        }

        pair<iterator,bool> insert(const K &key) {
            return _t.Insert(key);
        }

    private:
        RBTree<const K, K, SetKeyofT> _t;
    };


    void test_set1() {
        set<int> s;
        s.insert(9);
        s.insert(3);
        s.insert(5);
        s.insert(2);
        s.insert(8);
        s.insert(0);
        s.insert(-1);

        set<int>::iterator it = s.begin();
        while (it != s.end()) {
//            *it += 10;
            cout << *it << " ";
            ++it;
        }

//        for (auto e: s) {
//            cout << e << " ";
//        }
        cout << endl;

    }
}
