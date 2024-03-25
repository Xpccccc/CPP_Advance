#include <iostream>

using namespace std;

#include "BinarySearchTree.h"

using namespace std;

int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};

void test_BST1() {
    BinarySearchTree<int> bst;
    for (auto e: a) {
        bst.Insert(e);
    }

    bst.InOrder();
    cout << "Find(1):" << bst.Find(1) << endl;
    cout << "FindR(1):" << bst.FindR(1) << endl;

    bst.InOrder();
    for (auto e: a) {
        bst.Erase(e);
        bst.InOrder();
    }
}

void test_BST2() {
    BinarySearchTree<int> bst;
    for (auto e: a) {
        bst.InsertR(e);
    }

    bst.InOrder();

    for (auto e: a) {
        bst.Erase(e);
        bst.InOrder();
    }

}

void test_BST3() {
    BinarySearchTree<int> bst1;

    for (auto e: a) {
        bst1.Insert(e);
    }

    bst1.InOrder();

    BinarySearchTree<int> bst2(bst1);
    bst2.InOrder();

    BinarySearchTree<int> bst3 = bst1;
    bst3.InOrder();

}

void test_BST_KV() {
    kv::BinarySearchTree<string, string> bstkv;
    bstkv.Insert("hello", "你好");
    bstkv.Insert("xp", "徐鹏");
    bstkv.Insert("zl", "紫玲");
    bstkv.Insert("search", "搜索");
    string s;
    while (cin >> s) {
        auto ret = bstkv.Find(s);
        if (ret)
            cout << ret->_val << endl;
        else
            cout << "没有这个" << endl;
    }
}

int main() {
//    test_BST1();
//    test_BST2();
//    test_BST3();
    test_BST_KV();


    return 0;
}
