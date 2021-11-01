# [395. Longest Substring with At Least K Repeating Characters](https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/)

## 题目

Given a string `s` and an integer `k`, return *the length of the longest substring of* `s` *such that the frequency of each character in this substring is greater than or equal to* `k`.

 

**Example 1:**

```
Input: s = "aaabb", k = 3
Output: 3
Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
```

**Example 2:**

```
Input: s = "ababbc", k = 2
Output: 5
Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
```

 

**Constraints:**

- `1 <= s.length <= 104`
- `s` consists of only lowercase English letters.
- `1 <= k <= 105`

## 题目大意

给定一个字符串和一个整数 k，返回每个字母出现的次数均大于等于 K 的最长子串

## 解题思路

这道题目的关键在于，使用子串中不符合条件的字符去分割字符串，直至得到结果为止，这正好符合递归的思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/longest-substring-with-at-least-k-repeating-characters/solution/jie-ben-ti-bang-zhu-da-jia-li-jie-di-gui-obla/

我觉得这道题的霜神的题解，也可以参考以下

### Solution 1:

使用不满足条件的字符分割字符串，知道符合条件，或者无法继续分割

`````c++
class Solution {
public:
    int longestSubstring(string s, int k) {
        return Recur(s, k);
    }
    
 private:
    // 分割字符串
    static vector<string> Split(const string& str, const char delim = ' ') {
        istringstream ss(str);  // 利用 istringstream
        string tmp = "";
        
        vector<string> strs;
        while (getline(ss, tmp, delim)) {
            strs.push_back(tmp);
        }
        
        return strs;
    }
    
    int Recur(const string& str, int k) {
        // 如果分割出来的字符串长度已经小于k，则一定不满足
        if (str.size() < k) {
            return 0;
        }
        
        unordered_map<char, int> freq;  // 统计字符串中每个字符出现的次数
        for (char c : str) {
            ++freq[c];
        }
        
        for (const auto& item : freq) {
            // 如果有多个不满足条件的，这里随便用一个进行分割
            // unordered_map 遍历是无序的
            if (item.second < k) {  // 如果在当前字符串中该字符出现的次数小于k，
                int res = 0;
                // 用该字符分割字符串
                // 状态转移
                vector<string> strs = Split(str, item.first);
                for (const string& s : strs) {
                    res = max(res, Recur(s, k));
                }
                
                return res;
            }
        }
        
        return str.size();
    }
};
`````

