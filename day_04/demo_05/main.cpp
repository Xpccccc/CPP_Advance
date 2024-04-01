#include<stack>
#include"AVLTree.h"
#include"RBTree.h"
#include"BinarySeachTree.h"
#include<vector>

#define N 3000000

void test_ARB1() {
    vector<int> v;
    v.reserve(N);
    srand(time(0));

    for (size_t i = 0; i < N; i++) {
        v.push_back(rand() + i); // 让几棵树插入随机值
//        v.push_back( i );// 让几棵树插入有序值 -- 这个会导致二叉搜索树和结点个数一样高
    }

    RBTree<int, int> rbt;
    AVLTree<int, int> avl;
    BinarySearchTree<int> bst;

    int begin1 = clock();
    for (auto &e: v) {
        rbt.Insert(make_pair(e, e));
    }
    int end1 = clock();

    int begin2 = clock();
    for (auto &e: v) {
        avl.Insert(make_pair(e, e));
    }
    int end2 = clock();


    cout << "RBTree RotateSize:" << rbt.GetRotateSize() << endl;
    cout << "AVLTree RotateSize:" << avl.GetRotateSize() << endl;
    cout << "============================" << endl;


    cout << "RBTree Insert:" << end1 - begin1 << endl;
    cout << "AVLTree Insert:" << end2 - begin2 << endl;
    cout << "============================" << endl;


    cout << "RBTree IsBalance:" << rbt.IsBalance() << endl;
    cout << "AVLTree IsBalance:" << avl.IsBalance() << endl;
    cout << "============================" << endl;


    cout << "RBTree Height:" << rbt.Height() << endl;
    cout << "RBTree Size:" << rbt.Size() << endl;
    cout << "============================" << endl;


    cout << "AVLTree Height:" << avl.Height() << endl;
    cout << "AVLTree Size:" << avl.Size() << endl;
    cout << "============================" << endl;


    cout << "BinarySearchTree Height:" << bst.Height() << endl;
    cout << "BinarySearchTree Size:" << bst.Size() << endl;
    cout << "============================" << endl;


    int begin4 = clock();
    for (auto &e: v) {
        rbt.Find(e);
    }

//    // 随机值
//    for (size_t i = 0; i < N; i++) {
//        rbt.Find((rand() + i));
//    }

    int end4 = clock();

    int begin5 = clock();
    for (auto &e: v) {
        avl.Find(e);
    }

//    // 随机值
//    for (size_t i = 0; i < N; i++) {
//        avl.Find((rand() + i));
//    }
    int end5 = clock();


    int begin6 = clock();
    for (auto &e: v) {
        bst.Find(e);
    }

//    // 随机值
//    for (size_t i = 0; i < N; i++) {
//        avl.Find((rand() + i));
//    }
    int end6 = clock();
    cout << "RBTree Find:" << end4 - begin4 << endl;
    cout << "AVLTree Find:" << end5 - begin5 << endl;
    cout << "BinarySearchTree Find:" << end6 - begin6 << endl;

}


void test_ARB2() {
    vector<int> v;
    v.reserve(N);
    srand(time(0));

    for (size_t i = 0; i < N; i++) {
        v.push_back(rand() + i); // 让几棵树插入随机值
//        v.push_back( i );// 让几棵树插入有序值 -- 这个会导致二叉搜索树和结点个数一样高
    }

    RBTree<int, int> rbt;
    AVLTree<int, int> avl;

    int begin1 = clock();
    for (auto &e: v) {
        rbt.Insert(make_pair(e, e));
    }
    int end1 = clock();

    int begin2 = clock();
    for (auto &e: v) {
        avl.Insert(make_pair(e, e));
    }
    int end2 = clock();


    cout << "RBTree RotateSize:" << rbt.GetRotateSize() << endl;
    cout << "AVLTree RotateSize:" << avl.GetRotateSize() << endl;
    cout << "============================" << endl;


    cout << "RBTree Insert:" << end1 - begin1 << endl;
    cout << "AVLTree Insert:" << end2 - begin2 << endl;
    cout << "============================" << endl;


    cout << "RBTree IsBalance:" << rbt.IsBalance() << endl;
    cout << "AVLTree IsBalance:" << avl.IsBalance() << endl;
    cout << "============================" << endl;


    cout << "RBTree Height:" << rbt.Height() << endl;
    cout << "RBTree Size:" << rbt.Size() << endl;
    cout << "============================" << endl;


    cout << "AVLTree Height:" << avl.Height() << endl;
    cout << "AVLTree Size:" << avl.Size() << endl;
    cout << "============================" << endl;



    int begin4 = clock();
    for (auto &e: v) {
        rbt.Find(e);
    }

//    // 随机值
//    for (size_t i = 0; i < N; i++) {
//        rbt.Find((rand() + i));
//    }

    int end4 = clock();

    int begin5 = clock();
    for (auto &e: v) {
        avl.Find(e);
    }

//    // 随机值
//    for (size_t i = 0; i < N; i++) {
//        avl.Find((rand() + i));
//    }
    int end5 = clock();


    cout << "RBTree Find:" << end4 - begin4 << endl;
    cout << "AVLTree Find:" << end5 - begin5 << endl;

}
int main() {
//    test_ARB1();
    test_ARB2();
    return 0;
}
