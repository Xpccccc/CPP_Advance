//
// Created by 徐鹏 on 2024/4/6.
//

#ifndef DEMO_01_HASHTABLE_BUCKET_H
#define DEMO_01_HASHTABLE_BUCKET_H

#endif //DEMO_01_HASHTABLE_BUCKET_H

#include <iostream>
#include <vector>

using namespace std;


// 哈希表 --- 拉链法/哈希桶
template<class K, class V>
struct HashNode {
    typedef HashNode<K, V> Node;

    Node *_next;
    pair<K, V> _kv;

    HashNode(const pair<K, V> &kv) : _kv(kv), _next(nullptr) {}

};

template<class K>
struct HashFunc {
    size_t operator()(const K &key) {
        return (size_t) key;
    }
};

template<>
struct HashFunc<string> {
    size_t operator()(const string &str) {
        size_t hash = 0;
        for (auto e: str) {
            hash += e;
            e *= 131;
        }
        return hash;
    }
};

template<class K, class V, class Hash = HashFunc<K>>
class HashTable {
    typedef HashNode<K, V> Node;
public:
    ~HashTable() {
        for (int i = 0; i < _tables.size(); ++i) {
            _tables[i] = nullptr;
        }
    }

    HashTable(size_t size = 10) {
        _tables.resize(size, nullptr);// 各结点初始化为空
    }

    Node *Find(const K &key) {
        Hash hs;
        // 先算出映射到哪里
        int hashi = hs(key) % _tables.size();
        Node *cur = _tables[hashi];
        while (cur) {
            if (cur->_kv.first == key) {
                return cur;
            }
            cur = cur->_next;
        }
        return nullptr; // 没找到
    }

    bool Erase(const K &key) {
        Hash hs;
        Node *ret = Find(key);
        if (ret) {
            int hashi = hs(key) % _tables.size();
            Node *cur = _tables[hashi];
            Node *prev = nullptr;
            while (cur) {
                if (cur->_kv.first == key) {
                    if (prev == nullptr)
                        _tables[hashi] = cur->_next; // 要删除的就是表中的结点，那么将它的下一个结点放到表中
                    else
                        prev->_next = cur->_next; // 要删除的是表中的结点的后继中的某个

                    delete cur; // 删除该结点并退出循环
                    break;
                }
                prev = cur;
                cur = cur->_next;
            }
            return true;
        } else {
            return false;
        }
    }

    bool Insert(const pair<K, V> &kv) {

        Hash hs;
        if (Find(kv.first))
            return false;// 找到了
        if (_n == _tables.size()) {
            // 扩容
            vector<Node *> newTables;
            newTables.resize(2 * _tables.size(), nullptr);
            for (int i = 0; i < _tables.size(); ++i) {
                Node *cur = _tables[i];
                while (cur) {
                    Node *next = cur->_next; //记录下一个结点位置，防止找不到下一个结点
                    // 映射到新表位置
                    int hashi = hs(cur->_kv.first) % newTables.size();
                    // 插入到新表位置
                    Node *newcur = newTables[hashi];
                    if (newcur) {
                        // 当前表中的结点不为空，则头插并链接
                        cur->_next = newcur;
                        newTables[hashi] = cur;
                    } else {
                        // 当前表中的结点为空，则新结点直接放到这个表中
                        newTables[hashi] = cur;
                        cur->_next = nullptr;// 新插入的cur的_next不一定是空
                    }
                    cur = next;// 继续往下找
                }
            }
            _tables.swap(newTables);
        }

        // 先算出映射到哪里
        int hashi = hs(kv.first) % _tables.size();
        Node *cur = _tables[hashi];
        Node *newnode = new Node(kv);
        if (cur) {
            // 当前表中的结点不为空，则头插并链接
            newnode->_next = cur;
            _tables[hashi] = newnode;
        } else {
            // 当前表中的结点为空，则新结点直接放到这个表中
            _tables[hashi] = newnode;
        }
        ++_n;
        return true;
    }

private:
    vector<Node *> _tables;
    size_t _n = 0;
};

void test_Bucket1() {
//    int a[] = {4, 6, 7, 8, 9, 3, 2, 4, 5, 67, 11, 17, 0, 10};
    int a[] = {4, 6, 7, 8, 9, 3, 2, 0, 10, 20};
    HashTable<int, int> hs;
    for (auto &e: a) {
        hs.Insert(make_pair(e, e));
    }

    hs.Erase(10);
    hs.Erase(20);
    hs.Erase(0);
    hs.Erase(4);

}

void test_Bucket2() {
    string s[] = {"xp", "zl", "杨", "詹", "吕", "徐", "草莓", "梨", "香蕉", "梨", "hh", "ll"};
    HashTable<string, string> hs;
    for (auto &e: s) {
        if (e == "ll")
            int a = 0;
        hs.Insert(make_pair(e, e));
    }

    hs.Erase("xp");

}

class Date {
public:
    Date(int year = 1999, int month = 11, int day = 14) : _year(year), _month(month), _day(day) {

    }

    int getYear() const {
        return _year;
    }

    int getMonth() const {
        return _month;
    }

    int getDay() const {
        return _day;
    }

    bool operator==(const Date &d) {
        return _year == d._year && _month == d._month && _day == d._day;
    }

private:
    int _year;
    int _month;
    int _day;
};

struct HashNodeDate {
    size_t operator()(const Date &d) {
        size_t hash = 0;
        hash += d.getYear() * 131;
        hash += d.getMonth() * 131;
        hash += d.getDay() * 131;
        return hash;
    }
};

void test_Bucket3() {
    Date *d[] = {new Date(), new Date(1998, 1, 1), new Date(2000, 12, 11)};
    HashTable<Date, Date, HashNodeDate> hs;
    for (auto &e: d) {
        hs.Insert(make_pair(*e, *e));
    }
    hs.Erase(*new Date());
}

















