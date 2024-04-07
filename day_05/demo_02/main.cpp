#include "HashTable_Bucket.h"

#include "MyUnordered_Map.h"
#include "MyUnordered_Set.h"


void test_us1() {
    MyUnordered_Set<int> us;
    us.insert(3);
    us.insert(1);
    us.insert(2);
    us.insert(4);
    us.insert(14);
    us.insert(24);
    us.insert(11);
    us.insert(12);
    us.insert(13);
    us.insert(15);

    us.insert(22);

}


//
//void test_Bucket3() {
//
//    HashTable<Date, Date, HashNodeDate> hs;
//    for (auto &e: d) {
//        hs.Insert(make_pair(*e, *e));
//    }
//    hs.Erase(*new Date());
//}

void test_us2() {
    string s[] = {"xp", "zl", "杨", "詹", "吕", "徐", "草莓", "梨", "香蕉", "梨", "hh", "ll"};
    MyUnordered_Set<string> us;
    for (auto &e: s) {
        if (e == "ll")
            int a = 0;
        us.insert(e);
    }

    us.erase("xp");

}

class Date {
public:
    Date(int year = 1999, int month = 11, int day = 14) : _year(year), _month(month), _day(day) {

    }

    int getYear() const {
        return _year;
    }

    int getMonth() const {
        return _month;
    }

    int getDay() const {
        return _day;
    }

    bool operator==(const Date &d) {
        return _year == d._year && _month == d._month && _day == d._day;
    }

private:
    int _year;
    int _month;
    int _day;
};

struct HashNodeDate {
    size_t operator()(const Date &d) {
        size_t hash = 0;
        hash += d.getYear() * 131;
        hash += d.getMonth() * 131;
        hash += d.getDay() * 131;
        return hash;
    }
};

void test_us3() {
    Date *d[] = {new Date(), new Date(1998, 1, 1),
                 new Date(2000, 12, 11), new Date(2000, 11, 11),
                 new Date(2000, 10, 11), new Date(2001, 12, 11),
                 new Date(2002, 12, 11), new Date(2003, 12, 1),
                 new Date(2000, 12, 2), new Date(2010, 2, 11),
                 new Date(2004, 2, 11)};
    MyUnordered_Set<Date, HashNodeDate> us;
    for (auto &e: d) {
        us.insert(*e);
    }
    us.erase(*new Date());

}

void test_us4() {
    string s[] = {"xp", "zl", "杨", "詹", "吕", "徐", "草莓", "梨", "香蕉", "梨", "hh", "ll"};
    MyUnordered_Set<string> us;
    for (auto &e: s) {
        int a = 0;
        us.insert(e);
    }

    MyUnordered_Set<string>::iterator it = us.begin();
    while (it != us.end()) {
//        *it += 1;
        cout << *it << endl;
        ++it;
    }

    us.erase("xp");

}

void test_us5() {
    string s[] = {"xp", "zl", "杨", "詹", "吕", "徐", "草莓", "梨", "香蕉", "梨", "hh", "ll"};
    MyUnordered_Set<string> us;
    for (auto &e: s) {
        int a = 0;
        us.insert(e);
    }

    us.erase("ll");
    MyUnordered_Set<string>::iterator ret = us.find("xp");
    cout << *ret << endl;

}


void test_um1() {
    MyUnordered_Map<int, int> um;
    um.insert(make_pair(3, 3));
    um.insert(make_pair(1, 1));
    um.insert(make_pair(2, 2));
    um.insert(make_pair(4, 4));
    um.insert(make_pair(14, 14));
    um.insert(make_pair(24, 24));
    um.insert(make_pair(11, 11));
    um.insert(make_pair(12, 12));
    um.insert(make_pair(13, 13));
    um.insert(make_pair(15, 15));

    um.insert(make_pair(22, 22));

}

void test_um2() {
    string s[] = {"xp", "zl", "杨", "詹", "吕", "徐", "草莓", "梨", "香蕉", "梨", "hh", "ll"};
    MyUnordered_Map<string, string> um;
    for (auto &e: s) {
        if (e == "ll")
            int a = 0;
        um.insert(make_pair(e, e));
    }

    um.erase("xp");

}

void test_um3() {
    Date *d[] = {new Date(), new Date(1998, 1, 1),
                 new Date(2000, 12, 11), new Date(2000, 11, 11),
                 new Date(2000, 10, 11), new Date(2001, 12, 11),
                 new Date(2002, 12, 11), new Date(2003, 12, 1),
                 new Date(2000, 12, 2), new Date(2010, 2, 11),
                 new Date(2004, 2, 11)};
    MyUnordered_Map<Date, Date, HashNodeDate> um;
    for (auto &e: d) {
        um.insert(make_pair(*e, *e));
    }
    um.erase(*new Date());

}

void test_um4() {
    string s[] = {"xp", "zl", "杨", "詹", "吕", "徐", "草莓", "梨", "香蕉", "梨", "hh", "ll"};
    MyUnordered_Map<string, string> um;
    for (auto &e: s) {
        um.insert(make_pair(e, e));
    }

    MyUnordered_Map<string, string>::iterator it = um.begin();
    while (it != um.end()) {
//        it->first += 10;
        cout << it->first << ":" << it->second << endl;
        ++it;
    }

}

void test_um5() {
    string s[] = {"xp", "zl", "杨", "詹", "ll", "吕", "徐", "草莓", "梨", "香蕉", "梨", "hh", "ll"};
    MyUnordered_Map<string, int> um;
    for (auto &e: s) {
        um.insert(make_pair(e, 0));
    }

    MyUnordered_Map<string, int>::iterator it = um.begin();
    while (it != um.end()) {
//        it->first += 10;
        cout << it->first << ":" << it->second << endl;
        ++it;
    }
    cout << "==================" << endl;

    for (auto &e: s) {
        um[e]++;
    }

    it = um.begin();
    while (it != um.end()) {
//        it->first += 10;
        cout << it->first << ":" << it->second << endl;
        ++it;
    }
    cout << "==================" << endl;

    um["我"]++;
    it = um.begin();
    while (it != um.end()) {
//        it->first += 10;
        cout << it->first << ":" << it->second << endl;
        ++it;
    }
    cout << "==================" << endl;

    cout << um.find("xp")->first << endl;
}


int main() {

//    test_um5();
//    test_um4();
//    test_um3();
//    test_um2();
//    test_um1();

//    test_us5();
    test_us4();
//    test_us3();
//    test_us2();
//    test_us1();

    return 0;
}
