//
// Created by 徐鹏 on 2024/4/8.
//

#ifndef DEMO_04_BLOOMFILTER_H
#define DEMO_04_BLOOMFILTER_H

#endif //DEMO_04_BLOOMFILTER_H

#include<iostream>
#include<vector>
#include<ctime>

using namespace std;

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
}

struct HashFuncBKDR {
    size_t operator()(const string &str) {
        unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
        unsigned int hash = 0;

        for (auto &e: str) {
            hash = hash * seed + e;
        }
        return hash;
    }
};

struct HashFuncAP {
    size_t operator()(const string &str) {
        unsigned int hash = 0;
        int i;
        for (i = 0; i < str.size(); i++) {
            if ((i & 1) == 0) {
                hash ^= ((hash << 7) ^ (str[i]) ^ (hash >> 3));
            } else {
                hash ^= (~((hash << 11) ^ (str[i]) ^ (hash >> 5)));
            }
        }
        return hash;
    }

};

struct HashFuncDJB {
    size_t operator()(const string &str) {
        unsigned int hash = 5381;

        for (auto &e: str) {
            hash += (hash << 5) + e;
        }
        return hash;
    }

};

template<size_t N,
        class K=string,
        class Hash1 = HashFuncBKDR,
        class Hash2 = HashFuncAP,
        class Hash3 = HashFuncDJB
>
class BloomFilter {
public:
    void set(const K &s) {
        int hash1 = Hash1()(s) % M;
        int hash2 = Hash2()(s) % M;
        int hash3 = Hash3()(s) % M;

        // 映射三个位置
        _bs.set(hash1);
        _bs.set(hash2);
        _bs.set(hash3);

//        _bs->set(hash1);
//        _bs->set(hash2);
//        _bs->set(hash3);
    }

    bool test(const K &s) {
        int hash1 = Hash1()(s) % M;
        int hash2 = Hash2()(s) % M;
        int hash3 = Hash3()(s) % M;

        if (_bs.test(hash1) == false)
            return false;
        if (_bs.test(hash2) == false)
            return false;
        if (_bs.test(hash3) == false)
            return false;
//        if (_bs->test(hash1) == false)
//            return false;
//        if (_bs->test(hash2) == false)
//            return false;
//        if (_bs->test(hash3) == false)
//            return false;

        return true;// 也可能误判

    }

private:
    static const size_t M = 8*N;
//    bitset<M> _bs;
    xp::bitset<M> _bs;
//    bitset<M> *_bs = new bitset<M>;
};

void test_BF1() {
    BloomFilter<100000000> bf;
    string s[]{"xp", "zl", "杨", "图书馆", "嗨嗨嗨", "百度", "百毒", "摆渡", "腾讯", "阿里", "自己", "字节"};
    for (auto &e: s) {
        bf.set(e);
    }
    for (auto &e: s) {
        cout << bf.test(e) << endl;
    }
    cout << bf.test("xpp");
}

#define NUM 1000

void test_BF2() {
    BloomFilter<NUM> bf;
//    string s1 = "https://legacy.cplusplus.com/reference/bitset/bitset/?kw=bitset";
    string s1 = "xp";
    srand(time(NULL));
    for (int i = 0; i < NUM; ++i) {
        s1 += to_string(rand() + i);
        bf.set(s1);
    }

    // 生成的字符串一定不一样
//    string s2 = "https://legacy.cplusplus.com/reference/bitset/bitset/?kw=bitset";
    string s2 = "zl";
    size_t num = 0;
    for (int i = 0; i < NUM; ++i) {
        s2 += to_string(rand());
        if (bf.test(s2))
            ++num;
    }
    cout << "误判率：" << (double) num / NUM << endl;
}







