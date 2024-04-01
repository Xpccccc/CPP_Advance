//
// Created by 徐鹏 on 2024/4/1.
//

#ifndef DEMO_06_RBTREE_H
#define DEMO_06_RBTREE_H

#endif //DEMO_06_RBTREE_H


//
// Created by 徐鹏 on 2024/3/31.
//

#ifndef DEMO_05_RBTREE_H
#define DEMO_05_RBTREE_H

#endif //DEMO_05_RBTREE_H

#include <stack>
#include <iostream>

using namespace std;

enum Colour {
    RED,
    BLACK
};

template<class K, class V>
struct RBTreeNode {
    typedef RBTreeNode<K, V> Node;
    Node *_left;
    Node *_right;
    Node *_parent;
    Colour _col;

    pair<K, V> _kv;

    RBTreeNode(const pair<K, V> &kv) : _left(nullptr), _right(nullptr), _parent(nullptr), _col(RED), _kv(kv) {}
};


template<class K, class V>
class RBTree {
    typedef RBTreeNode<K, V> Node;
public:

    // 红黑树的查找
    Node *Find(const K &key) const {
        Node *cur = _root;
        while (cur) {
            if (cur->_kv.first < key)
                cur = cur->_right;
            else if (cur->_kv.first > key)
                cur = cur->_left;
            else
                return cur; // 找到了目标结点
        }
        return nullptr; // 没找到目标结点
    }


    // 红黑树的删除

    bool Remove(const K &key) {
        Node *target = Find(key);
        if (!target) // 如果没找到目标结点，则返回false
            return false;

        // 执行删除操作
        Node *to_fix = nullptr; // 用于记录需要修正的结点
        Node *parent = target->_parent;
        Colour target_original_colour = target->_col;
        Node *child;
        if (!target->_left) {
            child = target->_right;
            Transplant(target, target->_right);
        } else if (!target->_right) {
            child = target->_left;
            Transplant(target, target->_left);
        } else {
            Node *successor = Minimum(target->_right); // 找到右子树中的最小结点作为后继结点
            target_original_colour = successor->_col;
            child = successor->_right;
            if (successor->_parent == target)
                child->_parent = successor;
            else {
                Transplant(successor, successor->_right);
                successor->_right = target->_right;
                successor->_right->_parent = successor;
            }
            Transplant(target, successor);
            successor->_left = target->_left;
            successor->_left->_parent = successor;
            successor->_col = target->_col;
        }
        delete target;

        // 修正红黑树性质
        if (target_original_colour == BLACK)
            FixAfterDelete(parent, child);
        return true;
    }


    void FixAfterDelete(Node *parent, Node *node) {
        while (node != _root && (!node || node->_col == BLACK)) {
            if (node == parent->_left) {
                Node *sibling = parent->_right;
                if (sibling->_col == RED) {
                    sibling->_col = BLACK;
                    parent->_col = RED;
                    RotateL(parent);
                    sibling = parent->_right;
                }
                if ((!sibling->_left || sibling->_left->_col == BLACK) &&
                    (!sibling->_right || sibling->_right->_col == BLACK)) {
                    sibling->_col = RED;
                    node = parent;
                    parent = parent->_parent;
                } else {
                    if (!sibling->_right || sibling->_right->_col == BLACK) {
                        sibling->_left->_col = BLACK;
                        sibling->_col = RED;
                        RotateR(sibling);
                        sibling = parent->_right;
                    }
                    sibling->_col = parent->_col;
                    parent->_col = BLACK;
                    sibling->_right->_col = BLACK;
                    RotateL(parent);
                    node = _root;
                }
            } else {
                Node *sibling = parent->_left;
                if (sibling->_col == RED) {
                    sibling->_col = BLACK;
                    parent->_col = RED;
                    RotateR(parent);
                    sibling = parent->_left;
                }
                if ((!sibling->_right || sibling->_right->_col == BLACK) &&
                    (!sibling->_left || sibling->_left->_col == BLACK)) {
                    sibling->_col = RED;
                    node = parent;
                    parent = parent->_parent;
                } else {
                    if (!sibling->_left || sibling->_left->_col == BLACK) {
                        sibling->_right->_col = BLACK;
                        sibling->_col = RED;
                        RotateL(sibling);
                        sibling = parent->_left;
                    }
                    sibling->_col = parent->_col;
                    parent->_col = BLACK;
                    sibling->_left->_col = BLACK;
                    RotateR(parent);
                    node = _root;
                }
            }
        }
        if (node)
            node->_col = BLACK;
    }


    Node *Minimum(Node *node) const {
        while (node->_left)
            node = node->_left;
        return node;
    }


    void Transplant(Node *u, Node *v) {
        if (!u->_parent)
            _root = v;
        else if (u == u->_parent->_left)
            u->_parent->_left = v;
        else
            u->_parent->_right = v;
        if (v)
            v->_parent = u->_parent;
    }


    // 红黑树的插入
    bool Insert(const pair<K, V> &kv) {
        if (_root == nullptr) {
            _root = new Node(kv);
            _root->_col = BLACK;
            return true;
        }

        Node *parent = nullptr;
        Node *cur = _root;
        while (cur) {
            if (cur->_kv.first < kv.first) {
                parent = cur;
                cur = cur->_right;
            } else if (cur->_kv.first > kv.first) {
                parent = cur;
                cur = cur->_left;
            } else {
                return false;
            }
        }

        cur = new Node(kv);
        if (parent->_kv.first > cur->_kv.first)
            parent->_left = cur;
        else
            parent->_right = cur;

        cur->_parent = parent;

        while (parent && parent->_col == RED) {

            // 记录祖父结点
            Node *grandfather = parent->_parent;

            // 记录祖父结点
            if (parent == grandfather->_left) {
                Node *uncle = grandfather->_right;

                // 情况一：叔叔存在且为红 --- 当前不用旋转调整，只需要改变g、u、p的颜色
                // 因为如果叔叔为红，那么祖父和父亲的颜色是确定的！
                if (uncle && uncle->_col == RED) {
                    parent->_col = uncle->_col = BLACK;
                    grandfather->_col = RED;

                    //继续往上检查
                    cur = grandfather;
                    parent = cur->_parent;// 注意别写反了
                } else {
                    // 情况二：叔叔不存在或者叔叔存在且为黑

                    //  形状一
                    //               g
                    //        p               u
                    //  cur
                    if (cur == parent->_left) {
                        // 这时候只需要右旋
                        RotateR(grandfather);
                        //只要父亲和祖父变色
                        parent->_col = BLACK;
                        grandfather->_col = RED;
                    } else {
                        //形状三
                        //               g
                        //        p               u
                        //            cur

                        // 这时候需要先左旋再右旋
                        // p位置左旋
                        // 再g位置右旋
                        RotateL(parent);
                        RotateR(grandfather);

                        //p和g位置变色
                        cur->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    break; // 旋转完加变色，不需要再调整
                }

            } else {
                Node *uncle = grandfather->_left;
                // 情况一：叔叔存在且为红 --- 当前不用旋转调整，只需要改变g、u、p的颜色
                // 因为如果叔叔为红，那么祖父和父亲的颜色是确定的！
                if (uncle && uncle->_col == RED) {
                    parent->_col = uncle->_col = BLACK;
                    grandfather->_col = RED;

                    //继续往上检查
                    cur = grandfather;
                    parent = cur->_parent;// 注意别写反了
                } else {
                    // 情况二：叔叔不存在或者叔叔存在且为黑

                    //  形状二
                    //               g
                    //        u               p
                    //                              cur
                    if (cur == parent->_right) {
                        // 这时候只需要左旋
                        RotateL(grandfather);
                        //只要父亲和祖父变色
                        parent->_col = BLACK;
                        grandfather->_col = RED;
                    } else {
                        //形状四
                        //               g
                        //        u               p
                        //                   cur

                        // 这时候需要先右旋再左旋
                        // p位置右旋
                        // 再g位置左旋
                        RotateR(parent);
                        RotateL(grandfather);

                        //p和g位置变色
                        cur->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    break; // 旋转完加变色，不需要再调整
                }
            }
        }
        _root->_col = BLACK; // 根结点始终为黑
        return true;
    }

    void InOrder() {
        return _InOrder(_root);
    }

    bool IsBalance() {
        if (_root && _root->_col == RED)
            return false;
        int refBlackNum = 0; // 每条路径黑色结点的个数，这里以最右边的路径黑色结点的个数为基准
        Node *cur = _root;
        while (cur) {
            if (cur->_col == BLACK)
                ++refBlackNum;
            cur = cur->_right;
        }
        return _Check(_root, 0, refBlackNum);
    }

private:
    Node *_root = nullptr;

    bool _Check(Node *cur, int blackNum, int refBlackNum) {
        if (cur == nullptr) {
            if (blackNum != refBlackNum) {
                cout << "黑结点数量不一样" << endl;
                return false;// 到空结点开始比较黑结点是不是一样
            }

            cout << blackNum << endl;
            return true;
        }

        if (cur->_col == RED && cur->_parent->_col == RED) {
            cout << "存在连续红结点：" << cur->_kv.first << endl;
            return false;
        }

        if (cur->_col == BLACK)
            ++blackNum; // 统计该条路径的黑结点个数


        return _Check(cur->_left, blackNum, refBlackNum) && _Check(cur->_right, blackNum, refBlackNum);
    }

    void _InOrder(Node *root) {
        if (root == nullptr)
            return;
        _InOrder(root->_left);
        cout << root->_kv.first << endl;
        _InOrder(root->_right);
    }

    void RotateL(Node *parent) {
        Node *subR = parent->_right;
        Node *subRL = subR->_left;

        parent->_right = subRL;
        subR->_left = parent;
        Node *ppnode = parent->_parent;

        if (subRL)
            subRL->_parent = parent;
        parent->_parent = subR;

        // 如果当前parent本身就是跟结点的话，我们得把根结点更新
        if (parent == _root) {
            _root = subR;
            subR->_parent = nullptr;
        } else {
            if (parent == ppnode->_left) {
                // subR链接上之前的爷爷结点
                ppnode->_left = subR;
            } else {
                // subR链接上之前的爷爷结点
                ppnode->_right = subR;
            }
            subR->_parent = ppnode;
        }
    }

    void RotateR(Node *parent) {
        Node *subL = parent->_left;
        Node *subLR = subL->_right;

        parent->_left = subLR;
        subL->_right = parent;
        Node *ppnode = parent->_parent;

        if (subLR)
            subLR->_parent = parent;
        parent->_parent = subL;

        // 如果当前parent本身就是跟结点的话，我们得把根结点更新
        if (parent == _root) {
            _root = subL;
            subL->_parent = nullptr;
        } else {
            if (parent == ppnode->_left) {
                // subR链接上之前的爷爷结点
                ppnode->_left = subL;
            } else {
                // subR链接上之前的爷爷结点
                ppnode->_right = subL;
            }
            subL->_parent = ppnode;
        }
    }
};


