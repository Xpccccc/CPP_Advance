#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;


void test_us1() {
    unordered_set<int> us;
    int a[]{1, 2, 5, 7, 2, 3, 5, 8, 2, 11, 9};

    for (auto e: a) {
        us.insert(e);
    }
    for (auto e: us) {
        cout << e << " ";
    }
    cout << endl;
    cout << "=======================" << endl;

    unordered_set<int> us1(us.begin(), us.end());
    for (auto e: us1) {
        cout << e << " ";
    }
    cout << endl;
    cout << "=======================" << endl;

    unordered_set<int> us2(us1);
    for (auto e: us2) {
        cout << e << " ";
    }
    cout << endl;

}

void test_us2() {
    unordered_set<int> us;
    int a[]{1, 2, 5, 7, 2, 3, 5, 8, 2, 11, 9};
    for (auto e: a) {
        us.insert(e);
    }
    unordered_set<int>::iterator it = us.begin();
    while (it != us.end()) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;

    cout << "=======================" << endl;

    unordered_set<int>::const_iterator it1 = us.cbegin();
    while (it1 != us.cend()) {
        cout << *it1 << " ";
        ++it1;
    }
    cout << endl;
}


void test_us3() {
    unordered_set<int> us;
    int a[]{1, 2, 5, 7, 2, 3, 5, 8, 2, 11, 9};
    for (auto e: a) {
        us.insert(e);
    }
    cout << us.empty() << endl;
    cout << us.size() << endl;

    us.clear();
    cout << us.empty() << endl;
    cout << us.size() << endl;
}

void test_us4() {
    unordered_set<int> us;
    int a[]{1, 2, 5, 7, 2, 3, 5, 8, 2, 11, 9};
    for (auto e: a) {
        us.insert(e);
    }
    for (auto e: us) {
        cout << e << " ";
    }
    cout << endl;
    cout << "========================" << endl;
    us.erase(1);
    us.erase(2);

    auto pos = us.find(11);
    us.erase(pos);
    for (auto e: us) {
        cout << e << " ";
    }
    cout << endl;
    cout << "========================" << endl;

    unordered_set<int> us1;
    us1.insert(100);
    us1.swap(us);
    cout << "us:";
    for (auto e: us) {
        cout << e << " ";
    }
    cout << endl;

    cout << "us1:";
    for (auto e: us1) {
        cout << e << " ";
    }
    cout << endl;

    cout << "========================" << endl;

    cout << us1.count(5) << endl;
    cout << us1.count(1) << endl;
    cout << "========================" << endl;

    us1.clear();
    cout << "us:";
    for (auto e: us) {
        cout << e << " ";
    }
    cout << endl;

    cout << "us1:";
    for (auto e: us1) {
        cout << e << " ";
    }
    cout << endl;

}

void test_us5() {
    unordered_set<int> us;
    int a[]{1, 2, 5, 7, 2, 3, 5, 8, 2, 11, 9};
    for (auto e: a) {
        us.insert(e);
    }

    cout << us.bucket_count() << endl;
    cout << us.bucket_size(1) << endl;
    cout << us.bucket(11) << endl;
}

void test_ums1() {
    unordered_multiset<int> ums;
    int a[]{1, 2, 5, 7, 2, 3, 5, 8, 2, 11, 9};
    for (auto e: a) {
        ums.insert(e);
    }

    for (auto e: ums) {
        cout << e << " ";
    }
    cout << endl;
}

void test_um1() {
    unordered_map<int, int> um;
    int a[]{1, 2, 5, 7, 2, 3, 5, 8, 2, 11, 9};

    for (auto e: a) {
        um.insert(make_pair(e, e));
    }
    for (auto e: um) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << "=======================" << endl;

    unordered_map<int, int> um1(um.begin(), um.end());
    for (auto e: um1) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << "=======================" << endl;

    unordered_map<int, int> um2(um1);
    for (auto e: um2) {
        cout << e.first << ":" << e.second << endl;
    }

}

void test_um2() {
    unordered_map<int, int> um;
    int a[]{1, 2, 5, 7, 2, 3, 5, 8, 2, 11, 9};
    for (auto e: a) {
        um.insert(make_pair(e, e));
    }
    unordered_map<int, int>::iterator it = um.begin();
    while (it != um.end()) {
        cout << it->first << ":" << it->second << endl;
        ++it;
    }

    cout << "=======================" << endl;

    unordered_map<int, int>::const_iterator cit = um.cbegin();

    while (cit != um.cend()) {
        cout << cit->first << ":" << cit->second << endl;
        ++cit;
    }
}


void test_um3() {
    unordered_map<int, int> um;
    int a[]{1, 2, 5, 7, 2, 3, 5, 8, 2, 11, 9};
    for (auto e: a) {
        um.insert(make_pair(e, e));
    }
    cout << um.empty() << endl;
    cout << um.size() << endl;

    um.clear();
    cout << um.empty() << endl;
    cout << um.size() << endl;
}

void test_um4() {
    unordered_map<int, int> um;
    int a[]{1, 2, 5, 7, 2, 3, 5, 8, 2, 11, 9};
    for (auto e: a) {
        um.insert(make_pair(e, e));
    }
    for (auto e: um) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << "========================" << endl;
    um.erase(1);
    um.erase(2);

    auto pos = um.find(11);
    um.erase(pos);
    for (auto e: um) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << "========================" << endl;

    unordered_map<int, int> um1;
    um1.insert(make_pair(100, 100));
    um1.swap(um);
    cout << "um:";
    for (auto e: um) {
        cout << e.first << ":" << e.second << endl;
    }

    cout << "um1:";
    for (auto e: um1) {
        cout << e.first << ":" << e.second << endl;
    }

    cout << "========================" << endl;

    cout << um1.count(5) << endl;
    cout << um1.count(1) << endl;
    cout << "========================" << endl;

    um1.clear();
    cout << "um:";
    for (auto e: um) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << "um1:";
    for (auto e: um1) {
        cout << e.first << ":" << e.second << endl;
    }

}

void test_um5() {
    unordered_map<int, int> um;
    int a[]{1, 2, 5, 7, 2, 3, 5, 8, 2, 11, 9};
    for (auto e: a) {
        um.insert(make_pair(e, e));
    }

    cout << um.bucket_count() << endl;
    cout << um.bucket_size(1) << endl;
    cout << um.bucket(11) << endl;
}

void test_umm1() {
    unordered_multimap<int, int> ummp;
    int a[]{1, 2, 5, 7, 2, 3, 5, 8, 2, 11, 9};
    for (auto e: a) {
        ummp.insert(make_pair(e, e));
    }

    for (auto e: ummp) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << endl;
}

int main() {

    test_umm1();
//    test_um5();
//    test_um3();
//    test_um2();
//    test_um1();

//    test_ums1();
//    test_us5();
//    test_us4();
//    test_us3();
//    test_us2();
//    test_us1();
    return 0;
}

