//
// Created by 徐鹏 on 2024/4/6.
//

#ifndef DEMO_01_HASHTABLE_OPENADDR_H
#define DEMO_01_HASHTABLE_OPENADDR_H

#endif //DEMO_01_HASHTABLE_OPENADDR_H

#include <iostream>
#include <vector>

using namespace std;
enum State {
    EMPTY,
    EXIST,
    DELETE
};

// 哈希表 --- 开放定址法
template<class K, class V>
struct HashData {
    pair<K, V> _kv;
    State _s;

    HashData(const pair<K, V> &kv = pair<K, V>()) : _kv(kv), _s(EMPTY) {}
};

template<class K>
struct HashNodeFunc {
    size_t operator()(const K &key) {
        return (size_t) key;
    }
};

template<>
struct HashNodeFunc<string> {
    size_t operator()(const string &str) {
        size_t hash = 0;
        for (auto e: str) {
            e *= 131;
            hash += e;
        }
        return hash;
    }
};


template<class K, class V, class HashMode = HashNodeFunc<K> >
class HashTable_OpenAddr {
    typedef HashData<K, V> Node;
public:

    HashTable_OpenAddr(size_t size = 10) {
        _tables.resize(size);
    }

    Node *Find(const K &key) {
        HashMode hs;
        int hashi = hs(key) % _tables.size();
        while (_tables[hashi]._s == EXIST) {
            if (_tables[hashi]._kv.first == key)
                return &_tables[hashi];
            hashi++;
            hashi %= _tables.size(); // 可能从尾部到头部了
        }
        return nullptr;
    }

    bool Insert(const pair<K, V> &kv) {
        if (Find(kv.first))
            return false; // 存在就不插入了
        if (_n * 10 / _tables.size() >= 7) {
            // 装填因子为0.7，扩容
            size_t newSize = 2 * _tables.size();
//            _tables.resize(newSize);

            // 把原数据重新放到新空间中
            HashTable_OpenAddr<K, V,HashMode> newHashTable(newSize);
            for (auto &e: _tables) {
                if (e._s == EXIST) {
                    newHashTable.Insert(e._kv);
                }
            }
            _tables.swap(newHashTable._tables);
        }
        HashMode hs;
        int hashi = hs(kv.first) % _tables.size();
        while (_tables[hashi]._s == EXIST) {
            hashi++;
            hashi %= _tables.size(); // 可能从尾部到头部了
        }
        // 现在hashi的位置是空的或者是删除了的
        _tables[hashi]._kv = kv;
        _tables[hashi]._s = EXIST;
        ++_n;
        return true;
    }

    bool Erase(const K &key) {
        Node *ret = Find(key);
        if (ret) {
            --_n;
            ret->_s = DELETE;
            return true;
        } else {
            return false;
        }
    }


private:
    vector<Node> _tables;
    size_t _n = 0;
};

void test_Hash_Table1() {
    int a[] = {1, 2, 3, 4, 5, 6, 15};
    HashTable_OpenAddr<int, int> hs;
    for (auto e: a) {
        hs.Insert(make_pair(e, e));
    }
}

void test_Hash_Table2() {
    int a[] = {1, 2, 3, 4, 5, 6, 15, 16, 17};
    HashTable_OpenAddr<int, int> hs;
    for (auto e: a) {
        hs.Insert(make_pair(e, e));
    }
}

void test_Hash_Table3() {
    string a[] = {"草莓", "梨", "西瓜", "香蕉", "香瓜"};
    HashTable_OpenAddr<string, string> hs;
    for (auto e: a) {
        hs.Insert(make_pair(e, e));
    }
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

    bool operator==(const Date& d) {
        return _year == d._year && _month == d._month && _day == d._day;
    }

private:
    int _year;
    int _month;
    int _day;
};

struct HashNodeDate{
    size_t operator()(const Date &d) {
        size_t hash = 0;
        hash += d.getYear() * 131;
        hash += d.getMonth() * 131;
        hash += d.getDay() * 131;
        return hash;
    }
};

void test_Hash_Table4() {
    Date *d[] = {new Date(), new Date(1998, 1, 1), new Date(2000, 12, 11)};
    HashTable_OpenAddr<Date, Date, HashNodeDate> hs;
    for (auto e: d) {
        hs.Insert(make_pair(*e, *e));
    }
    hs.Erase(*new Date(1998, 1, 1));
}