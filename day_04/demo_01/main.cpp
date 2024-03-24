#include <iostream>
#include <set>
#include <map>

using namespace std;

void test_set3() {
    multiset<int> mst; // 可以存重复值
    mst.insert(4);
    mst.insert(1);
    mst.insert(6);
    mst.insert(3);
    mst.insert(3);
    mst.insert(9);
    mst.insert(5);
    mst.insert(5);
    mst.insert(5);
    mst.insert(1);

    multiset<int>::reverse_iterator rit = mst.rbegin();
    while (rit != mst.rend()) {
        cout << *rit << " ";
        ++rit;
    }
    cout << endl;

    multiset<int>::iterator lit = mst.lower_bound(3); // >=3

    multiset<int>::iterator uit = mst.upper_bound(6);// > 6

    mst.erase(lit, uit);
    for (auto &e: mst) {
        cout << e << " ";
    }
    cout << endl;


}

void test_set2() {
    set<int> st;
    st.insert(4);
    st.insert(1);
    st.insert(6);
    st.insert(3);
    st.insert(9);
    st.insert(5);

    cout << st.count(1) << endl; // 可以查看一个值在不在这个搜索树中
    cout << st.count(10) << endl;
}

void test_set1() {
    set<int> st; // 不存重复值
    st.insert(4);
    st.insert(1);
    st.insert(6);
    st.insert(3);
    st.insert(9);
    st.insert(5);

    set<int>::iterator it = st.begin();
    while (it != st.end()) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;

    st.erase(1);
    for (auto &e: st) {
        cout << e << " ";
    }
    cout << endl;

    set<int>::iterator fit = find(st.begin(), st.end(), 3);
    st.erase(fit);

    for (auto &e: st) {
        cout << e << " ";
    }
    cout << endl;

    set<int>::iterator fit1 = st.find(6);
    st.erase(fit1);

    for (auto &e: st) {
        cout << e << " ";
    }
    cout << endl;
}


void test_map4() {
    multimap<string, int> mmp; // 可存重复的key
    mmp.insert({"我", 1});
    mmp.insert({"我", 2});
    mmp.insert(make_pair("你", 2));
    mmp.insert(make_pair("他", 3));
    mmp.insert(make_pair("谁", 4));
    mmp.insert(make_pair("谁", 5));
    mmp.insert(pair<string, int>("hh", 10));
    mmp.insert(pair<string, int>("谁", 10));

    for (auto &e: mmp) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << endl;

    cout << "我的个数：" << mmp.count("我") << endl;
    mmp.erase("我");
    for (auto &e: mmp) {
        cout << e.first << ":" << e.second << endl;
    }

    cout << "我的个数：" << mmp.count("我") << endl;

}


// map的[]使用 : (*((this->insert(make_pair(k,mapped_type()))).first)).second
void test_map3() {
    map<string, int> mp;
    string s[] = {"苹果", "香蕉", "草莓", "梨", "甘蔗", "香蕉", "梨", "甘蔗", "苹果", "草莓", "草莓"};
    for (auto &e: s) {
        pair<map<string, int>::iterator, bool> p = mp.insert(make_pair(e, 1));
        if (p.second == false) {
            p.first->second++; // 如果该元素已经插入过，则当前不插入，但是返回指向该key的迭代器和false，使用迭代器找到v，对v++
        }
    }

    for (auto &e: mp) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << endl;

    mp["橘子"];// 插入
    cout << "查找当前甘蔗值:" << mp["甘蔗"] << endl; // 查找
    mp["甘蔗"] = 1;// 修改
    mp["橙子"] = 5;// 插入：修改

    for (auto &e: mp) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << endl;
}

void test_map2() {
    map<string, int> mp;
    string s[] = {"苹果", "香蕉", "草莓", "梨", "甘蔗", "香蕉", "梨", "甘蔗", "苹果", "草莓", "草莓"};

//    for (auto &e: s) {
//        map<string, int>::iterator it = mp.find(e);
//        if (it != mp.end()) {
//            it->second++;
//        } else {
//            mp.insert(make_pair(e, 1));
//        }
//    }

    for (auto &e: s) {
        mp[e]++;
    }
    for (auto &e: mp) {
        cout << e.first << ":" << e.second << endl;
    }
    cout << endl;


}


void test_map1() {
    map<string, string> mp; // 不能存key一样的pair
    mp.insert(pair<string, string>("string", "字符串"));
    pair<string, string> p = pair("sort", "排序");
    mp.insert(p);
    mp.insert({"string", "字符串"});
    mp.insert(make_pair("string", "字符串"));

    map<string, string>::iterator it = mp.begin();

    while (it != mp.end()) {
        cout << it->first << ":" << it->second << endl;
        ++it;
    }
    cout << endl;
    map<string, string>::iterator fit = mp.find("string");
    mp.insert(fit, make_pair("find", "找到"));

    it = mp.begin();
    while (it != mp.end()) {
        cout << it->first << ":" << it->second << endl;
        ++it;
    }
    cout << endl;

    mp.erase("find");
    it = mp.begin();
    while (it != mp.end()) {
        cout << it->first << ":" << it->second << endl;
        ++it;
    }
    cout << endl;
    cout << mp["string"] << endl;
}

int main() {
//    test_set1();
//    test_set2();
//    test_set3();

//    test_map1();
//    test_map2();
//    test_map3();
    test_map4();
    return 0;
}
