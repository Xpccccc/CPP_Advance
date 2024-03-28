#include <iostream>
#include <map>
#include <vector>
#include <cstdio>
#include <string.h>

using namespace std;

// KY264 单词识别
int main() {
    map<string, int> mp;

    vector<string> v;

    string str;
    getline(cin, str);
    string pstr = ""; // 用来记录每个单词然后push给v
    int pos = 0;
    // 把最后一个单词的.去掉
    str[str.size() - 1] = ' ';
    for (int i = 0; i < str.size(); ++i) {

        if (str[i] != ' ') {
            // 大字母转换为小字母
            if (str[i] >= 'A' && str[i] <= 'Z')
                str[i] += 32;
            pstr += str[i];
        } else {
            v.push_back(pstr);
            pstr = "";
        }
    }


    for (auto &e: v) {
        mp[e]++;
    }

    for (auto &e: mp) {
        cout << e.first << ":" << e.second << endl;
    }

}
// 64 位输出请用 printf("%lld")