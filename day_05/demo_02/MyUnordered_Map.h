//
// Created by 徐鹏 on 2024/4/6.
//

#ifndef DEMO_02_MYUNORDERED_MAP_H
#define DEMO_02_MYUNORDERED_MAP_H

#endif //DEMO_02_MYUNORDERED_MAP_H


template<class K, class V, class Hash = HashFunc<K>>
class MyUnordered_Map {
    struct MapKeyOfT {
        K operator()(const pair<K, V> &kv) {
            return kv.first;
        }
    };

public:

    typedef typename HashTable<K, pair<const K, V>, MapKeyOfT, Hash>::iterator iterator;

    iterator begin() {
        return _hs.begin();
    }

    iterator end() {
        return _hs.end();
    }

    pair<iterator, bool> insert(const pair<K, V> &kv) {
        return _hs.Insert(kv);
    }

    bool erase(const K &key) {
        return _hs.Erase(key);
    }

    iterator find(const K &key) {
        return _hs.Find(key);
    }

    V &operator[](const K &key) {
        pair<iterator, bool> ret = insert(make_pair(key, V()));
        return ret.first->second;
    }

private:
    HashTable<K, pair<const K, V>, MapKeyOfT, Hash> _hs;
};
