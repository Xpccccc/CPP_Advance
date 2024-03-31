//
// Created by 徐鹏 on 2024/3/25.
//

#ifndef DEMO_02_AVLTREE_H
#define DEMO_02_AVLTREE_H

#endif //DEMO_02_AVLTREE_H

#include <utility>
#include <iostream>

using namespace std;

template<class K, class V>
struct AVLTreeNode {
    typedef AVLTreeNode<K, V> Node;

    Node *_left;
    Node *_right;
    Node *_parent;

    pair<K, V> _kv;
    int _bf; // 平衡因子

    AVLTreeNode(const pair<K, V> &kv) : _left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv), _bf(0) {}
};


template<class K, class V>
class AVLTree {
public:
    typedef AVLTreeNode<K, V> Node;

    // AVL的查找
    Node *Find(const K &key) const {
        Node *cur = _root;

        // 从根节点开始搜索
        while (cur) {
            if (cur->_kv.first < key) {
                cur = cur->_right; // 如果当前节点的键值小于目标键值，则向右子树搜索
            } else if (cur->_kv.first > key) {
                cur = cur->_left; // 如果当前节点的键值大于目标键值，则向左子树搜索
            } else {
                return cur; // 找到目标键值，返回当前节点
            }
        }

        return nullptr; // 没有找到目标键值，返回空指针
    }


    // AVL的删除
    bool Remove(const K &key) {
        return Remove(_root, key);
    }

    bool Remove(Node *&root, const K &key) {
        if (!root)
            return false;

        if (key < root->_kv.first) {
            bool res = Remove(root->_left, key);
            // 重新计算平衡因子并进行平衡调整
            if (res)
                updateBalanceFactor(root);
            return res;
        } else if (key > root->_kv.first) {
            bool res = Remove(root->_right, key);
            // 重新计算平衡因子并进行平衡调整
            if (res)
                updateBalanceFactor(root);
            return res;
        } else {
            if (!root->_left || !root->_right) {
                Node *temp = root;
                root = (root->_left) ? root->_left : root->_right;
                if (root)
                    root->_parent = temp->_parent;
                delete temp;
            } else {
                Node *successor = GetSuccessor(root->_right);
                root->_kv = successor->_kv;
                Remove(root->_right, successor->_kv.first);
                // 重新计算平衡因子并进行平衡调整
                updateBalanceFactor(root);
            }
            return true;
        }
    }

    Node *GetSuccessor(Node *node) {
        while (node->_left)
            node = node->_left;
        return node;
    }

    void updateBalanceFactor(Node *node) {
        int leftHeight = (node->_left) ? _Height(node->_left) : -1;
        int rightHeight = (node->_right) ? _Height(node->_right) : -1;
        node->_bf = rightHeight - leftHeight;
    }


    // AVL的插入
    bool Insert(const pair<K, V> &kv) {

        if (_root == nullptr) {
            _root = new Node(kv);
            return true;
        }

        Node *cur = _root;
        Node *parent = nullptr;

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

        // cur == nullptr
        cur = new Node(kv);
        if (parent->_kv.first < kv.first)
            parent->_right = cur;
        else if (parent->_kv.first > kv.first)
            parent->_left = cur;

        cur->_parent = parent;

        // 看当前插入的结点会不会导致树不平衡
        // parent == nullptr说明已经调整到根了
        // 平衡因子使用的是右减左的方案
        while (parent) {
            if (cur == parent->_left)
                parent->_bf--;
            else
                parent->_bf++;

            // 说明插入之前parent的平衡因子是1或者-1，现在变得非常健康，不要调整
            if (parent->_bf == 0) {
                break;
            } else if (parent->_bf == 1 || parent->_bf == -1) {
                // 说明插入之前parent的平衡因子是0,现在变得亚健康，需要往上看爷爷结点是不是平衡因子出现问题了
                cur = cur->_parent;
                parent = parent->_parent;
            } else if (parent->_bf == 2 || parent->_bf == -2) {
                // 旋转调整

                // 说明插入之前parent的平衡因子是1或者-1，现在变得不健康了，需要调整
                if (parent->_bf == 2 && parent->_right->_bf == 1) { // parent->_bf == 2 && cur->_bf == 1
                    // 此时需要左单旋
                    RotateL(parent);
                } else if (parent->_bf == -2 && parent->_left->_bf == -1) {
                    // 此时需要右单旋
                    RotateR(parent);
                } else if (parent->_bf == 2 && parent->_right->_bf == -1) {
                    // 此时需要右旋再左旋
                    RotateRL(parent);
                } else {
                    // 此时需要左旋再右旋
                    RotateLR(parent);
                }
                break;// 调整结束，不用再往上调整
            }
        }
        return true;
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
        parent->_bf = 0;
        subR->_bf = 0;
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
        parent->_bf = 0;
        subL->_bf = 0;
    }

    void RotateRL(Node *parent) {
        // 因为左单旋转和右单旋后bf都设置为0了，因此我们需要手动再设置改变的结点的平衡因子

        // 会改变平衡因子的结点
        Node *subR = parent->_right;
        Node *subRL = subR->_left;

        //  用来记录没旋转前subRL的结点的bf
        int rlbf = subRL->_bf;

        RotateR(parent->_right);
        RotateL(parent);

        // 讨论旋转后的bf（平衡因子改变的结点）
        if (rlbf == -1) {
            subRL->_bf = 0;
            subR->_bf = 1;
            parent->_bf = 0;
        } else if (rlbf == 1) {
            subRL->_bf = 0;
            subR->_bf = 0;
            parent->_bf = -1;
        } else if (rlbf == 0) { // rlbf == 0
            subRL->_bf = 0;
            subR->_bf = 0;
            parent->_bf = 0;
        } else {
            assert(false);
        }
    }

    void RotateLR(Node *parent) {
        // 因为左单旋转和右单旋后bf都设置为0了，因此我们需要手动再设置改变的结点的平衡因子

        // 会改变平衡因子的结点
        Node *subL = parent->_left;
        Node *subLR = subL->_right;

        //  用来记录没旋转前subLR的结点的bf
        int lrbf = subLR->_bf;

        RotateL(parent->_left);
        RotateR(parent);

        // 讨论旋转后的bf（平衡因子改变的结点）
        if (lrbf == -1) {
            subLR->_bf = 0;
            subL->_bf = 0;
            parent->_bf = 1;
        } else if (lrbf == 1) {
            subLR->_bf = 0;
            subL->_bf = -1;
            parent->_bf = 0;
        } else if (lrbf == 0) { // lrbf == 0
            subLR->_bf = 0;
            subL->_bf = 0;
            parent->_bf = 0;
        } else {
            assert(false);
        }

    }


    void InOrder() {
        _InOrder(_root);
    }

    int Height() {
        return _Height(_root);
    }

    bool IsBalance() {
        return _IsBalance(_root);
    }


private:

    bool _IsBalance(Node *root) {
        if (root == nullptr)
            return true;
        int lheight = _Height(root->_left);
        int rheight = _Height(root->_right);
        if (root->_bf != (rheight - lheight) || root->_bf > 1 || root->_bf < -1)
            return false;
        cout << "key:" << root->_kv.first << " " << "bf:" << root->_bf << " " << "rh-lh:" << rheight - lheight
             << endl;
        return _IsBalance(root->_left) && _IsBalance(root->_right);
    }

    int _Height(Node *root) {
        if (root == nullptr)
            return 0;
        int lheight = _Height(root->_left);
        int rheight = _Height(root->_right);
        return lheight > rheight ? lheight + 1 : rheight + 1;
    }

    void _InOrder(Node *root) {
        if (root == nullptr)
            return;
        _InOrder(root->_left);
        cout << root->_kv.first << ":" << root->_kv.second << "[" << root->_bf << "]" << endl;
        _InOrder(root->_right);

    }


    Node *_root= nullptr;
};

void test_AVLTree1() {
    int a[] = {3, 5, 7, 1, 2, 9, 4, 6, 10, 1, 9, 99, -1, -2, -10, -100, 11, 6};
    AVLTree<int, string> avl;
    for (auto e: a) {
        avl.Insert(make_pair(e, ""));
    }
    avl.InOrder();
    cout << "height：" << avl.Height() << endl;
}

void test_AVLTree2() {
    int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    AVLTree<int, string> avl;
    for (auto e: a) {
        avl.Insert(make_pair(e, ""));
    }
    avl.InOrder();
    cout << avl.IsBalance() << endl;
}

void test_AVLTree3() {
    int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    AVLTree<int, string> avl;
    for (auto e: a) {
        avl.Insert(make_pair(e, ""));
    }
    avl.InOrder();
    cout << avl.IsBalance() << endl;
    avl.Remove(11);
    avl.InOrder();
    cout << avl.IsBalance() << endl;
}

void test_AVLTree4() {
    int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    AVLTree<int, string> avl;
    for (auto e: a) {
        avl.Insert(make_pair(e, ""));
    }
    avl.InOrder();
    cout << "====" << endl;
//    cout << avl.IsBalance() << endl;

    avl.Remove(11);
    avl.Remove(14);
    avl.Remove(3);
    avl.Remove(9);

    avl.InOrder();

    cout << avl.IsBalance() << endl;

    AVLTreeNode<int, string> *node = avl.Find(7);
    cout << node->_kv.first << endl;
}


















