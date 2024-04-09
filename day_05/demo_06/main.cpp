#include <iostream>
#include<bitset>

using namespace std;


void test_bs1() {
    bitset<1000> bs;
    int a[] = {1, 5, 7, 8, 999, 44, 22, 44, 0, 3, 5, 65, 78, 95};
    for (auto e: a) {
        bs.set(e);
    }

    for (auto e: a) {
        cout << e << "->" << bs.test(e) << endl;
    }
    cout << "==================" << endl;
    bs.reset(1);
    bs.reset(5);

    for (auto e: a) {
        cout << e << "->" << bs.test(e) << endl;
    }
    // a中没有的值
    cout << "a中没有的值:" << 10 << "->" << bs.test(10) << endl;

}

int main() {
    test_bs1();
    return 0;
}
