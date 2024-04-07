//
// Created by 徐鹏 on 2024/4/6.
//

#ifndef DEMO_02_MYUNORDERED_SET_H
#define DEMO_02_MYUNORDERED_SET_H

#endif //DEMO_02_MYUNORDERED_SET_H


template<class K, class Hash = HashFunc<K>>
class MyUnordered_Set {
    struct SetKeyOfT {
        K operator()(const K &key) {
            return key;
        }
    };

public:

    typedef typename HashTable<K, const K, SetKeyOfT, Hash>::iterator iterator;

    iterator begin() {
        return _hs.begin();
    }

    iterator end() {
        return _hs.end();
    }

    pair<iterator,bool> insert(const K &key) {
        return _hs.Insert(key);
    }

    bool erase(const K &key) {
        return _hs.Erase(key);
    }

    iterator find(const K &key) {
        return _hs.Find(key);
    }



private:
    HashTable<K, const K, SetKeyOfT, Hash> _hs;
};

