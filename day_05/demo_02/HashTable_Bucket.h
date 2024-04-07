//
// Created by 徐鹏 on 2024/4/6.
//

#ifndef DEMO_02_HASHTABLE_BUCKET_H
#define DEMO_02_HASHTABLE_BUCKET_H

#endif //DEMO_02_HASHTABLE_BUCKET_H


#include <iostream>
#include <vector>

using namespace std;

template<class T>
struct HashNode {
    typedef HashNode<T> Node;

    Node *_next;
    T _data;

    HashNode(const T &data) : _data(data), _next(nullptr) {}

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


// 前置声明
template<class K, class T, class KeyOfT, class Hash>
class HashTable;

template<class K, class T, class KeyOfT, class Hash>
struct __HTIterator {

    typedef HashNode<T> Node;
    typedef HashTable<K, T, KeyOfT, Hash> HT;
    typedef __HTIterator<K, T, KeyOfT, Hash> Self;

    Node *_node;
    HT *_ht;

    __HTIterator(Node *node, HT *ht) : _node(node), _ht(ht) {}


    T &operator*() {
        return _node->_data;
    }

    T *operator->() {
        return &_node->_data;
    }

    Self &operator++() {
        if (_node->_next) {
            // 当前结点还有后继结点
            _node = _node->_next;
        } else {
            // 当前桶走完了
            KeyOfT kot;
            Hash hs;

            // 先算出当前在哪个哈希桶
            int hashi = hs(kot(_node->_data)) % _ht->_tables.size();
            ++hashi;// 走到下一个桶

            while (hashi < _ht->_tables.size()) {
                if (_ht->_tables[hashi]) {
                    //  这个桶有结点
                    _node = _ht->_tables[hashi];
                    break;
                } else
                    ++hashi;// 这个桶没有有结点
            }

            if (hashi == _ht->_tables.size()) {
                // 走到最后了，没找到下一个位置
                _node = nullptr;
            }

        }
        return *this;
    }

    bool operator!=(const Self &s) {
        return s._node != _node;
    }
};

template<class K, class T, class KeyOfT, class Hash>
class HashTable {
    friend __HTIterator<K, T, KeyOfT, Hash>;// 为了能访问_tables
    typedef HashNode<T> Node;
public:

    typedef __HTIterator<K, T, KeyOfT, Hash> iterator;

    iterator begin() {
        for (int i = 0; i < _tables.size(); ++i) {
            if (_tables[i])
                return iterator(_tables[i], this);// 从左找到第一个哈希桶的第一个结点
        }
        return end();
    }

    iterator end() {
        return iterator(nullptr, this);
    }

    ~HashTable() {
        for (int i = 0; i < _tables.size(); ++i) {
            _tables[i] = nullptr;
        }
    }

    HashTable(size_t size = 10) {
        _tables.resize(size, nullptr);// 各结点初始化为空
    }

    iterator Find(const K &key) {
        Hash hs;
        KeyOfT kot;
        // 先算出映射到哪里
        int hashi = hs(key) % _tables.size();
        Node *cur = _tables[hashi];
        while (cur) {
            if (kot(cur->_data) == key) {
                return iterator(cur, this);
            }
            cur = cur->_next;
        }
        return iterator(nullptr, this); // 没找到
    }

    bool Erase(const K &key) {
        Hash hs;
        KeyOfT kot;
        iterator ret = Find(key);
        if (ret != end()) {
            int hashi = hs(key) % _tables.size();
            Node *cur = _tables[hashi];
            Node *prev = nullptr;
            while (cur) {
                if (kot(cur->_data) == key) {
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
            --_n;
            return true;
        } else {
            return false;
        }
    }

    pair<iterator, bool> Insert(const T &data) {

        Hash hs;
        KeyOfT kot;
        iterator it = Find(kot(data));
        if (it != end())
            return make_pair(it, false);// 找到了
        if (_n == _tables.size()) {
            // 扩容
            vector<Node *> newTables;
            newTables.resize(2 * _tables.size(), nullptr);
            for (int i = 0; i < _tables.size(); ++i) {
                Node *cur = _tables[i];
                while (cur) {
                    Node *next = cur->_next; //记录下一个结点位置，防止找不到下一个结点
                    // 映射到新表位置
                    int hashi = hs(kot(cur->_data)) % newTables.size();
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
        int hashi = hs(kot(data)) % _tables.size();
        Node *cur = _tables[hashi];
        Node *newnode = new Node(data);
        if (cur) {
            // 当前表中的结点不为空，则头插并链接
            newnode->_next = cur;
            _tables[hashi] = newnode;
        } else {
            // 当前表中的结点为空，则新结点直接放到这个表中
            _tables[hashi] = newnode;
        }
        ++_n;
        return make_pair(iterator(_tables[hashi], this), true);
    }

private:
    vector<Node *> _tables;
    size_t _n = 0;
};
















