#include <iostream>
#include <vector>

/*
 * 有2个字符串，需要判断他们是不是类似
如果 a中的字符可以按某种映射关系替换得到 b ，那么这两个字符串结构是相同的。
每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。不同字符不能映射到同一个字符上，相同字符只能映射到同一个字符上，字符可以映射到自己本身。
 示例 1:
输入：a= "app", b = "ugg"
输出：true
示例 2：
输入：a = "app", b = "pig"
输出：false
示例 3：
输入：a = "paper", b = "title"
输出：true

paper
title

abc
dcf

1. 递推累计映射关系
2. 新的一组存在对应关系则继续，不存在则保存，矛盾则返回false,直到结束

提示：
可以假设 a 和 b 长度相同。
C++
class Solution {
public:
    bool isIsomorphic(string s, string t) {
    }
};
 */

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        std::map<char, char> c2c;
        std::map<char, char> c2cReverse;
        for(int i = 0; i < s.size(); ++i) {
            if (c2c.end() != c2c.find(s[i])) {
                if (c2c[s[i]] != t[i]) {
                    return false;
                }
            }
            if (c2cReverse.end() != c2cReverse.find(t[i])) {
                if (c2cReverse[t[i]] != s[i]) {
                    return false;
                }
                continue;
            }
            c2c[s[i]] = t[i];
            c2cReverse[t[i]] = s[i];
        }
        return true;
    }
};


int main() {
    string s("aap");
    string t("uug");
    Solution solution;
    cout << solution.isIsomorphic(s,t) << endl;
}