//
// Created by 徐鹏 on 2024/3/31.
//

#ifndef DEMO_05_BINARYSEACHTREE_H
#define DEMO_05_BINARYSEACHTREE_H

#endif //DEMO_05_BINARYSEACHTREE_H

#include <iostream>

using namespace std;

template<class K>
struct BSTreeNode {
    //typedef BSTreeNode<K> Node;

    BSTreeNode<K> *_left;
    BSTreeNode<K> *_right;
    K _key;

    BSTreeNode(const K &key) : _left(nullptr), _right(nullptr), _key(key) {}

};


template<class K>
class BinarySearchTree {
public:
    typedef BSTreeNode<K> Node;

    BinarySearchTree() = default;

    BinarySearchTree(const BinarySearchTree<K> &b) {
        _root = Copy(b._root);
    }

    Node *Copy(Node *root) {
        if (root == nullptr)
            return nullptr;
        Node *newNode = new Node(root->_key);
        newNode->_left = Copy(root->_left);
        newNode->_right = Copy(root->_right);

        return newNode;

    }

    BinarySearchTree<K> &operator=(BinarySearchTree<K> b) {
        swap(b._root, _root);
        return *this;
    }

    ~BinarySearchTree() {
        Destroy(_root);
    }

    void Destroy(Node *root) {
        if (root == nullptr)
            return;
        Destroy(root->_left);
        Destroy(root->_right);
        delete root;
    }


    bool Erase(const K &key) {
        Node *cur = _root;
        Node *parent = nullptr;

        if (cur == nullptr)
            return false;


        while (cur) {
            if (cur->_key < key) {
                parent = cur;
                cur = cur->_right;
            } else if (cur->_key > key) {
                parent = cur;
                cur = cur->_left;
            } else {
                //找到要删的结点

                // 当前要删的结点有一个孩子或者没有孩子
                if (cur->_left == nullptr) {
                    // 判断跟结点是否只有一颗子树
                    if (cur == _root) {
                        _root = _root->_right;
                    } else {
                        if (parent->_left == cur)
                            parent->_left = cur->_right;
                        else
                            parent->_right = cur->_right;
                    }

                    delete cur;
                    return true;

                } else if (cur->_right == nullptr) {

                    // 判断跟结点是否只有一颗子树
                    if (cur == _root) {
                        _root = _root->_left;
                    } else {
                        if (parent->_left == cur)
                            parent->_left = cur->_left;
                        else
                            parent->_right = cur->_left;
                    }


                    delete cur;
                    return true;

                } else {
                    // 当前要删的结点有两个孩子

                    // 找个替代的值去删  -- 找左子树的最右结点,即左子树最大的结点

                    Node *LeftMax = cur->_left;
                    Node *LeftMaxParent = cur;
                    while (LeftMax->_right) {
                        LeftMaxParent = LeftMax;
                        LeftMax = LeftMax->_right;
                    }

                    cur->_key = LeftMax->_key;
                    if (LeftMaxParent->_left == LeftMax)
                        LeftMaxParent->_left = LeftMax->_left;
                    else
                        LeftMaxParent->_right = LeftMax->_left;
                    delete LeftMax;
                    return true;
                }
            }
        }
        return false;
    }

    bool Insert(const K &key) {
        Node *cur = _root;
        Node *parent = nullptr;
        if (cur == nullptr) {
            Node *newNode = new Node(key);
            _root = newNode;
            return true;
        }
        while (cur) {
            if (cur->_key < key) {
                parent = cur;
                cur = cur->_right;
            } else if (cur->_key > key) {
                parent = cur;
                cur = cur->_left;
            } else {
                return false;
            }
        }

        // cur == nullptr
//        Node *newNode = new Node(key);
//        if (parent->_key < key)
//            parent->_right = newNode;
//        else if (parent->_key > key)
//            parent->_left = newNode;

        cur = new Node(key);
        if (parent->_key < key)
            parent->_right = cur;
        else if (parent->_key > key)
            parent->_left = cur;
        return true;
    }

    bool Find(const K &key) {
        Node *cur = _root;
        if (cur == nullptr)
            return false;

        while (cur) {
            if (cur->_key < key) {
                cur = cur->_right;
            } else if (cur->_key > key) {
                cur = cur->_left;
            } else {
                return true;
            }
        }

        return false;
    }

    int Height() {
        return _Height(_root);
    }

    int _Height(Node *root) {
        if (root == nullptr)
            return 0;
        int lheight = _Height(root->_left);
        int rheight = _Height(root->_right);
        return lheight > rheight ? lheight + 1 : rheight + 1;
    }

    int Size() {
        if (!_root)
            return 0;

        int size = 0;
        std::stack<Node *> stack;
        Node *current = _root;

        while (current || !stack.empty()) {
            while (current) {
                stack.push(current);
                current = current->_left;
            }

            current = stack.top();
            stack.pop();
            size++;
            current = current->_right;
        }

        return size;
    }

    void InOrder() {
        _InOrder(_root);
        cout << endl;
    }


    bool FindR(const K &key) {
        return _FindR(_root, key);
    }

    bool InsertR(const K &key) {
        return _InsertR(_root, key);
    }

    bool EraseR(const K &key) {
        return _EraseR(_root, key);
    }


private:

    bool _EraseR(Node *root, const K &key) {
        if (root == nullptr)
            return false;

        if (root->_key < key) {
            return _EraseR(root->_right, key);
        } else if (root->_key > key) {
            return _EraseR(root->_left, key);
        } else {

            Node *del = root;
            if (root->_right == nullptr)
                root = root->_left;
            else if (root->_left == nullptr)
                root = root->_right;
            else {
                // 将当前要删的结点的值和当前结点的左子树最大值的结点交换
                Node *LeftMax = root->_left;
                while (LeftMax->_right) {
                    LeftMax = LeftMax->_right;
                }

                swap(LeftMax->_key, root->_key);

                return _EraseR(root, key);
            }
            delete del;
            return true;
        }
    }

    bool _InsertR(Node *&root, const K &key) {
        if (root == nullptr) {
            root = new Node(key);
            return true;
        }

        if (root->_key < key) {
            return _InsertR(root->_right, key);
        } else if (root->_key > key) {
            return _InsertR(root->_left, key);
        } else {
            return false;
        }
    }

    bool _FindR(Node *root, const K &key) {
        if (root == nullptr)
            return false;

        if (root->_key < key) {
            return _FindR(root->_right, key);
        } else if (root->_key > key) {
            return _FindR(root->_left, key);
        } else {
            return true;
        }
    }


    void _InOrder(Node *root) {
        if (root == nullptr)
            return;
        if (root->_left)
            _InOrder(root->_left);
        cout << root->_key << " ";
        if (root->_right)
            _InOrder(root->_right);
    }

    Node *_root = nullptr;
};


namespace kv {
    template<class K, class V>
    struct BSTreeNode {
        //typedef BSTreeNode<K> Node;

        BSTreeNode<K, V> *_left;
        BSTreeNode<K, V> *_right;
        K _key;
        V _val;

        BSTreeNode(const K &key, const K &val) : _left(nullptr), _right(nullptr), _key(key), _val(val) {}

    };


    template<class K, class V>
    class BinarySearchTree {
    public:
        typedef BSTreeNode<K, V> Node;

        BinarySearchTree() = default;

        BinarySearchTree(const BinarySearchTree<K, V> &b) {
            _root = Copy(b._root);
        }

        Node *Copy(Node *root) {
            if (root == nullptr)
                return nullptr;
            Node *newNode = new Node(root->_key);
            newNode->_left = Copy(root->_left);
            newNode->_right = Copy(root->_right);

            return newNode;

        }

        BinarySearchTree<K, V> &operator=(BinarySearchTree<K, V> b) {
            swap(b._root, _root);
            return *this;
        }

        ~BinarySearchTree() {
            Destroy(_root);
        }

        void Destroy(Node *root) {
            if (root == nullptr)
                return;
            Destroy(root->_left);
            Destroy(root->_right);
            delete root;
        }


        bool Erase(const K &key) {
            Node *cur = _root;
            Node *parent = nullptr;

            if (cur == nullptr)
                return false;


            while (cur) {
                if (cur->_key < key) {
                    parent = cur;
                    cur = cur->_right;
                } else if (cur->_key > key) {
                    parent = cur;
                    cur = cur->_left;
                } else {
                    //找到要删的结点

                    // 当前要删的结点有一个孩子或者没有孩子
                    if (cur->_left == nullptr) {
                        // 判断跟结点是否只有一颗子树
                        if (cur == _root) {
                            _root = _root->_right;
                        } else {
                            if (parent->_left == cur)
                                parent->_left = cur->_right;
                            else
                                parent->_right = cur->_right;
                        }

                        delete cur;
                        return true;

                    } else if (cur->_right == nullptr) {

                        // 判断跟结点是否只有一颗子树
                        if (cur == _root) {
                            _root = _root->_left;
                        } else {
                            if (parent->_left == cur)
                                parent->_left = cur->_left;
                            else
                                parent->_right = cur->_left;
                        }


                        delete cur;
                        return true;

                    } else {
                        // 当前要删的结点有两个孩子

                        // 找个替代的值去删  -- 找左子树的最右结点,即左子树最大的结点

                        Node *LeftMax = cur->_left;
                        Node *LeftMaxParent = cur;
                        while (LeftMax->_right) {
                            LeftMaxParent = LeftMax;
                            LeftMax = LeftMax->_right;
                        }

                        cur->_key = LeftMax->_key;
                        if (LeftMaxParent->_left == LeftMax)
                            LeftMaxParent->_left = LeftMax->_left;
                        else
                            LeftMaxParent->_right = LeftMax->_left;
                        delete LeftMax;
                        return true;
                    }
                }
            }
            return false;
        }

        bool Insert(const K &key, const K &val) {
            Node *cur = _root;
            Node *parent = nullptr;
            if (cur == nullptr) {
                Node *newNode = new Node(key, val);
                _root = newNode;
                return true;
            }
            while (cur) {
                if (cur->_key < key) {
                    parent = cur;
                    cur = cur->_right;
                } else if (cur->_key > key) {
                    parent = cur;
                    cur = cur->_left;
                } else {
                    return false;
                }
            }

            // cur == nullptr
            Node *newNode = new Node(key, val);
            if (parent->_key < key)
                parent->_right = newNode;
            else if (parent->_key > key)
                parent->_left = newNode;
            return true;
        }

        Node *Find(const K &key) {
            Node *cur = _root;
            if (cur == nullptr)
                return nullptr;

            while (cur) {
                if (cur->_key < key) {
                    cur = cur->_right;
                } else if (cur->_key > key) {
                    cur = cur->_left;
                } else {
                    return cur;
                }
            }

            return nullptr;
        }

        void InOrder() {
            _InOrder(_root);
            cout << endl;
        }


    private:

        void _InOrder(Node *root) {
            if (root == nullptr)
                return;
            if (root->_left)
                _InOrder(root->_left);
            cout << root->_key << " ";
            if (root->_right)
                _InOrder(root->_right);
        }

        Node *_root = nullptr;
    };

}