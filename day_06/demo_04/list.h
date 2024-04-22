//
// Created by 徐鹏 on 2024/4/18.
//

#ifndef DEMO_04_LIST_H
#define DEMO_04_LIST_H


#include <iostream>

using namespace std;


// list的模拟实现(还未完成)

namespace xp {

    // 结点
    template<class T>
    struct ListNode {
        ListNode<T> *_next;
        ListNode<T> *_prev;
        T data;

        // 构造函数  -- 创建结点
        ListNode(const T &val = T()) : _next(nullptr), _prev(nullptr), data(val) { // data(val)调用拷贝构造


        }

        // 这里val的类型是左值
        ListNode(T &&val) : _next(nullptr), _prev(nullptr), data(forward<T>(val)) { // data(val)调用拷贝构造


        }

        template<class ...Args>
        ListNode(Args &&...args) : _next(nullptr), _prev(nullptr), data(forward<Args>(args)...) { // data(val)调用拷贝构造


        }

    };

    template<class T, class Ref, class Ptr>
    class __list_iterator {
    public:
        typedef ListNode<T> Node;
        typedef __list_iterator<T, Ref, Ptr> self; // 迭代器本身

        // 这里构造函数为了方便begin和end，直接隐式类型转换
        __list_iterator(Node *node) : _node(node) {

        }

        Ref operator*() {
            return _node->data;
        }

        Ptr operator->() {
            return &_node->data;
        }

        self &operator++() {
            _node = _node->_next;
            return *this;
        }

        self operator++(int) {
            self temp(*this); // 这里*this的类型是self ,调用默认拷贝构造函数！因为是内置类型，不需要自己写
            _node = _node->_next;
            return temp;
        }

        self &operator--() {
            _node = _node->_prev;
            return *this;
        }

        self &operator--(int) {
            self temp(*this);
            _node = _node->_prev;
            return temp;
        }

        bool operator!=(const self &s) {
            return _node != s._node;
        }

        bool operator==(const self &s) {
            return _node == s._node;
        }

        // 拷贝构造和析构不需要写，析构不能用，不然结点被删除了

        // 比如 lt.begin()，这里的类型就是Node*
        Node *_node; // 内置类型不能重载++等操作符，因此对这个内置类型进行封装来实现++等功能
    };

    template<class T>
    class list {
    public:
        typedef ListNode<T> Node;
        typedef __list_iterator<T, T &, T *> iterator;
        typedef __list_iterator<T, const T &, const T *> const_iterator;


        //构造函数
        list() {
            //创建带头节点的双向循环链表
            _head = new Node;
            _head->_next = _head;
            _head->_prev = _head;
        }

        // 拷贝构造函数
        list(list<T> &lt) {
            // 先创个头节点
            _head = new Node;
            _head->_next = _head;
            _head->_prev = _head;

            iterator it = lt.begin();
            while (it != lt.end()) {
                push_back(*it);
                ++it;
            }
        }

        void swap(list<T> &lt) {
            std::swap(_head, lt._head);
        }

        // 赋值
        list<T> operator=(list<T> lt) {
            swap(lt);
            return *this;
        }

        iterator begin() {
            return _head->_next;
        }

        iterator end() {
            return _head;
        }

        const_iterator begin() const {
            return _head->_next;
        }

        const_iterator end() const {
            return _head;
        }

        void push_back(const T &val) {
//            Node *tail = _head->_prev;// 先找到尾
//
//            // 创建新节点
//            Node *newnode = new Node(val);
//
//            tail->_next = newnode;
//            newnode->_prev = tail;
//
//            newnode->_next = _head;
//            _head->_prev = newnode;

            insert(end(), val);
        }

        // 这里val的类型是左值
        void push_back(T &&val) {
//            Node *tail = _head->_prev;// 先找到尾
//
//            // 创建新节点
//            Node *newnode = new Node(val);
//
//            tail->_next = newnode;
//            newnode->_prev = tail;
//
//            newnode->_next = _head;
//            _head->_prev = newnode;

            insert(end(), forward<T>(val));
        }

        template<class ...Args>
        void emplace_back(Args &&...args) {
            emplace(end(), forward<Args>(args)...);
        }

        template<class ...Args>
        iterator emplace(iterator pos, Args &&...args) {
            Node *cur = pos._node;
            Node *prev = cur->_prev;
            Node *newnode = new Node(forward<Args>(args)...);

            newnode->_next = cur;
            newnode->_prev = prev;
            prev->_next = newnode;
            cur->_prev = newnode;

            return newnode;
        }

        iterator insert(iterator pos, const T &val) {

            Node *cur = pos._node;
            Node *prev = cur->_prev;
            Node *newnode = new Node(val);

            newnode->_next = cur;
            newnode->_prev = prev;
            prev->_next = newnode;
            cur->_prev = newnode;

            return newnode;
        }

        // 这里val的类型是左值
        iterator insert(iterator pos, T &&val) {

            Node *cur = pos._node;
            Node *prev = cur->_prev;
            Node *newnode = new Node(forward<T>(val));

            newnode->_next = cur;
            newnode->_prev = prev;
            prev->_next = newnode;
            cur->_prev = newnode;

            return newnode;
        }


        iterator erase(iterator pos) {
            assert(pos != _head);// _head这个位置就是end()

            Node *cur = pos._node;
            Node *prev = cur->_prev;
            Node *tail = cur->_next;

            prev->_next = tail;
            tail->_prev = prev;

            delete cur;

            return tail;
        }

        void clear() {
            // 清空所有数据，只留一个头节点
            iterator it = begin();
            while (it != end()) {
                it = erase(begin());
            }
        }

        ~list() {
            clear();
            if (_head) {
                delete _head;
                _head = nullptr;
            }

        }

    private:
        Node *_head;// 头节点 -- 带头双向循环链表
    };

}

#endif //DEMO_04_LIST_H

