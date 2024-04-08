//
// Created by 徐鹏 on 2024/4/7.
//


#ifndef DEMO_03_BITSET_H
#define DEMO_03_BITSET_H

#endif //DEMO_03_BITSET_H

#include <vector>

// 位图
// 给40亿个不重复的无符号整数，没排过序。给一个无符号整数，如何快速判断一个数是否在这40亿个数中。【腾讯】
namespace xp {
    template<size_t N>
    class bitset {
    public:
        bitset() {
            _bs.resize(N / 32 + 1, 0); // 当N很大时，位图的长度范围是1～2^32
        }

        void set(size_t x) {
            assert(x <= N);
            size_t i = x / 32; // 找到第几个int（32位）
            size_t j = x % 32;

            _bs[i] |= (1 << j);// 将该位置置1
        }

        void reset(size_t x) {
            assert(x <= N);
            size_t i = x / 32; // 找到第几个int（32位）
            size_t j = x % 32;

            _bs[i] &= ~(1 << j);// 将该位置置0
        }

        bool test(size_t x) {
            assert(x <= N);
            size_t i = x / 32; // 找到第几个int（32位）
            size_t j = x % 32;

            if (_bs[i] & (1 << j))
                return true;// 这个值存在
            else
                return false;// 这个值不存在
        }

    private:
        vector<int> _bs;
    };

    void test_bitset1() {
        bitset<100> bs;
        bs.set(10);
        bs.set(1);
        bs.set(5);
        bs.set(99);
        bs.set(29);
        bs.set(5);

        for (size_t i = 0; i < 100; ++i) {
            if (bs.test(i))
                cout << i << endl;
        }

        cout << "===================" << endl;
        bs.reset(5);
        bs.reset(10);
        for (size_t i = 0; i < 100; ++i) {
            if (bs.test(i))
                cout << i << endl;
        }
    }

    // 给定100亿个整数，设计算法找到只出现一次的整数？
    // 使用位图 -- 1、使用一个位图，两个位表示一个整数的出现次数，比如00、01、10、11  ,如果N为2^32,需要的长度就是2^33，开空间resize(N/16,0)
    //             ，但是size_t 能表示这么大吗，前面的2^32的比特位可以访问到，但是后面的2^32的比特位怎么访问---编译器64位下！不能long，long在32位下还是32位
    //            2、使用两个位图，一个位图的的该位上作为第一个比特位，一个位图的的该位上作为第二个比特位。

    template<size_t N>
    class two_bitset {
    public:
        void set(size_t x) {
            if (_bs1.test(x) == false && _bs2.test(x) == false) {
                // 00 -> 01
                _bs2.set(x);
            } else if (_bs1.test(x) == false && _bs2.test(x) == true) {
                // 01 -> 10
                _bs1.set(x);
                _bs2.reset(x);
            } else {

                _bs1.set(x);
                _bs2.set(x);
            }
        }

        size_t test(size_t x) {
            if (_bs1.test(x) == false && _bs2.test(x) == false) {
                return 0;
            } else if (_bs1.test(x) == false && _bs2.test(x) == true) {
                // 01 -> 10
                return 1;
            } else {
                return 2;// 大于等于2次
            }
        }

    private:
        bitset<N> _bs1;
        bitset<N> _bs2;
    };

    void test_teo_bitset1() {
        two_bitset<101> tbs;
//        two_bitset<UINT_MAX> tbs;
        tbs.set(10);
        tbs.set(10);
        tbs.set(10);
        tbs.set(1);
        tbs.set(10);
        tbs.set(100);
        tbs.set(12);
        tbs.set(22);
        tbs.set(21);
        tbs.set(55);
        tbs.set(4);

        for (size_t i = 0; i <= 100; ++i) {
            if (tbs.test(i)) {
                cout << i << "->" << tbs.test(i) << endl;
            }
        }

    };
}

























