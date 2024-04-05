#include <iostream>
#include <set>
#include <map>

using namespace std;


void test_set1() {
    set<int> s;
    s.insert(4);
    s.insert(6);
    s.insert(8);
    s.insert(3);
    s.insert(1);
    for (auto e: s) {
        cout << e << " ";
    }
    cout << endl;

    cout << "=============" << endl;

    set<int> s1(s.begin(), s.end());
    for (auto e: s1) {
        cout << e << " ";
    }
    cout << endl;
}


void test_set2() {
    set<int> s;
    s.insert(4);
    s.insert(6);
    s.insert(8);
    s.insert(3);
    s.insert(1);

    set<int>::iterator it = s.begin();
    while (it != s.end()) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;

    set<int>::reverse_iterator rit = s.rbegin();
    while (rit != s.rend()) {
        cout << *rit << " ";
        ++rit;
    }
    cout << endl;

}

void test_set3() {
    set<int> s;
    s.insert(4);
    s.insert(6);
    s.insert(8);
    s.insert(3);
    s.insert(1);

    cout << s.size() << endl;
    cout << s.empty() << endl;

    s.clear();

    cout << s.size() << endl;
    cout << s.empty() << endl;
}

void test_set4() {
    set<int> s;
    s.insert(4);
    s.insert(6);
    s.insert(8);
    s.insert(3);
    s.insert(1);

    for (auto e: s) {
        cout << e << " ";
    }
    cout << endl;

    auto pos = s.find(6);
    s.erase(pos);

    for (auto e: s) {
        cout << e << " ";
    }
    cout << endl;
    cout << s.count(6) << endl;
    cout << s.count(1) << endl;

    set<int> s1;
    s1.insert(1000);
    s1.insert(100);
    s1.insert(10);
    s1.insert(1);

    s1.swap(s);
    for (auto e: s1) {
        cout << e << " ";
    }
    cout << endl;
    s1.clear();

    for (auto e: s1) {
        cout << e << " ";
    }
    cout << endl;

}

void test_multiset1() {
    multiset<int> ms;

    ms.insert(6);
    ms.insert(1);
    ms.insert(5);
    ms.insert(6);
    ms.insert(8);
    ms.insert(9);
    ms.insert(1);
    ms.insert(1);

    for (auto e: ms) {
        cout << e << " ";
    }
    cout << endl;
}


void test_map1() {
    map<int, int> mp;
    mp.insert(make_pair(2, 2));
    mp.insert(make_pair(4, 4));
    mp.insert(make_pair(12, 12));
    mp.insert(make_pair(5, 5));
    mp.insert(make_pair(9, 9));
    mp.insert(make_pair(1, 1));

    for (auto e: mp) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << "===========" << endl;

    map<int, int> mp2(mp.begin(), mp.end());
    for (auto e: mp2) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << "===========" << endl;

    map<int, int> mp3(mp2);
    for (auto e: mp3) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << "===========" << endl;

}

void test_map2() {
    map<int, int> mp;
    mp.insert(make_pair(2, 2));
    mp.insert(make_pair(4, 4));
    mp.insert(make_pair(12, 12));
    mp.insert(make_pair(5, 5));
    mp.insert(make_pair(9, 9));
    mp.insert(make_pair(1, 1));

    map<int, int>::iterator it = mp.begin();
    while (it != mp.end()) {
        cout << it->first << ":" << it->second << endl;
        ++it;
    }

    cout << "===========" << endl;

    map<int, int>::reverse_iterator rit = mp.rbegin();
    while (rit != mp.rend()) {
        cout << rit->first << ":" << rit->second << endl;
        ++rit;
    }

}

void test_map3() {
    map<int, int> mp;
    mp.insert(make_pair(2, 2));
    mp.insert(make_pair(4, 4));
    mp.insert(make_pair(12, 12));
    mp.insert(make_pair(5, 5));
    mp.insert(make_pair(9, 9));
    mp.insert(make_pair(1, 1));

    cout << mp.size() << endl;
    cout << mp.empty() << endl;

    mp.clear();

    cout << mp.size() << endl;
    cout << mp.empty() << endl;
}

void test_map4() {
    map<int, int> mp;
    mp.insert(make_pair(2, 2));
    mp.insert(make_pair(4, 4));
    mp.insert(make_pair(12, 12));
    mp.insert(make_pair(5, 5));
    mp.insert(make_pair(9, 9));
    mp.insert(make_pair(1, 1));

    for (auto e: mp) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << "===========" << endl;

    auto pos = mp.find(12);
    mp.erase(pos);
    mp.erase(2);

    for (auto e: mp) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << "===========" << endl;

    map<int, int> mp2;
    mp2.swap(mp);

    for (auto e: mp2) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << "===========" << endl;

    cout << mp2.count(5) << endl;
    cout << mp2.count(12) << endl;

    mp2.clear();
    for (auto e: mp2) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << "===========" << endl;

}

void test_multimap1() {
    multimap<int, int> mmp;
    mmp.insert(make_pair(2, 2));
    mmp.insert(make_pair(4, 4));
    mmp.insert(make_pair(4, 2));
    mmp.insert(make_pair(12, 12));
    mmp.insert(make_pair(12, 1));
    mmp.insert(make_pair(5, 5));
    mmp.insert(make_pair(9, 7));
    mmp.insert(make_pair(9, 9));
    mmp.insert(make_pair(9, 9));
    mmp.insert(make_pair(1, 1));
    mmp.insert(make_pair(2, 1));

    for (auto e: mmp) {
        cout << e.first << ":" << e.second << endl;
    }
}


int main() {
    test_multimap1();
//    test_map4();
//    test_map3();
//    test_map2();
//    test_map1();
//    test_multiset1();
//    test_set4();
//    test_set3();
//    test_set1();
//    test_set2();
    return 0;
}
