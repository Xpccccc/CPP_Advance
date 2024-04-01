//
// Created by 徐鹏 on 2024/4/1.
//

#ifndef DEMO_04_MYMAP_H
#define DEMO_04_MYMAP_H

#endif //DEMO_04_MYMAP_H


namespace xp {
    template<class K, class V>
    class map {
        // 用来取出key
        struct MapKeyofT {
            K operator()(const pair<K, V> &kv) {
                return kv.first;
            }
        };

    public:

        // 在类模版里取iterator需要使用到typename，指定这个iterator是类型
        // 否则不知道是静态成员变量还是类型，因为他们的定义语法是一样的
        typedef typename RBTree<K, pair<const K, V>, MapKeyofT>::iterator iterator;
        typedef typename RBTree<K, pair<const K, V>, MapKeyofT>::const_iterator  const_iterator;

        iterator begin() {
            return _t.begin();
        }

        iterator end() {
            return _t.end();
        }

        const_iterator begin() const {
            return _t.begin();
        }

        const_iterator end() const {
            return _t.end();
        }

        iterator find(const K &key) {
            return _t.Find(key);
        }


        V &operator[](const K &key) {
            pair<iterator, bool> p = insert(make_pair(key, V()));

            return p.first->second; // p.first的类型是iterator，iterator使用->，返回的是pair<>*
        }

        pair<iterator, bool> insert(const pair<K, V> &kv) {
            return _t.Insert(kv);
        }


    private:
        RBTree<K, pair<const K, V>, MapKeyofT> _t;
    };

    void test_map1() {
        map<int, int> mp;
        mp.insert(make_pair(9, 9));
        mp.insert(make_pair(3, 3));
        mp.insert(make_pair(5, 5));
        mp.insert(make_pair(2, 2));
        mp.insert(make_pair(8, 8));
        mp.insert(make_pair(-1, 1));
        mp.insert(make_pair(0, 1));

        map<int, int>::iterator it = mp.begin();
        while (it != mp.end()) {
//            it->first += 10;
            cout << it->first << " ";
            ++it;
        }

//        for (auto e: mp) {
//            cout << e.first << " ";
//        }
        cout << endl;

        cout << mp[0] << endl;
        cout << mp[-1] << endl;
        cout << mp[9] << endl;

        cout << mp[10] << endl;

        for (auto e: mp) {
            cout << e.first << " ";
        }
    }

    void test_map2() {
        string a[] = {"草莓", "苹果", "西瓜", "梨", "橘子", "香蕉", "草莓", "苹果", "梨", "橘子", "西瓜", "梨", "蛋"};
        map<string, int> mp;
        for (auto &e: a) {
            mp[e]++;
        }

        for (auto e: mp) {
            cout << e.first << ":" << e.second << endl;
        }
    }
}

