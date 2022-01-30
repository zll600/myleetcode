# [467. Unique Substrings in Wraparound String](https://leetcode-cn.com/problems/unique-substrings-in-wraparound-string/)

## 题目

We define the string `s` to be the infinite wraparound string of `"abcdefghijklmnopqrstuvwxyz"`, so `s` will look like this:

- `"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd...."`.

Given a string `p`, return *the number of **unique non-empty substrings** of* `p` *are present in* `s`.

 

**Example 1:**

```
Input: p = "a"
Output: 1
Explanation: Only the substring "a" of p is in s.
```

**Example 2:**

```
Input: p = "cac"
Output: 2
Explanation: There are two substrings ("a", "c") of p in s.
```

**Example 3:**

```
Input: p = "zab"
Output: 6
Explanation: There are six substrings ("z", "a", "b", "za", "ab", and "zab") of p in s.
```

 

**Constraints:**

- `1 <= p.length <= 105`
- `p` consists of lowercase English letters.

## 题目大意

把字符串 `s` 看作是`“abcdefghijklmnopqrstuvwxyz”`的无限环绕字符串，所以 s 看起来是这样的：`"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd...."`. 

现在我们有了另一个字符串 `p` 。你需要的是找出 `s` 中有多少个唯一的 `p` 的非空子串，尤其是当你的输入是字符串 ` p`，你需要输出字符串 `s` 中 `p` 的不同的非空子串的数目。 



## 解题思路

这道题读完题目之后，会想想到 kmp 算法，不行直接硬刚，但是复杂度就会比较高了

但是这道题目有个特地拿，`s` 本身有一个特性，要成为 `s` 的子串，那么必须是连续的字母，或者首尾闭合的才可以，所以我们只要判断 `p` 中，有多少个连续的子串，再累加就可以了


### Solution 1:




````c++
class Solution {
public:
    int findSubstringInWraproundString(string p) {
        // 先将所有的字符纪委的
        unordered_map<int, int> memo;
        for (char c : p) {
            memo.emplace(c, 0);
        }
        
        int word_len = 1;
        memo[p[0]] = word_len;    
        const int len = p.size();
        for (int i = 1; i < len; ++i) {
            if (p[i] - p[i - 1] == 1 || p[i] - p[i - 1] == -25) {
                // 如果是连续或者是回环的话，就递增
                word_len += 1;
            } else {
                word_len = 1;
            }
            // 更新以这个字符结尾的最长子串的长度
            memo[p[i]] = max(memo[p[i]], word_len);
        }
        
        int sum = 0;
        for (const auto& item : memo) {
            // 累加所有的和
            sum += item.second;
        }
        
        return sum;
    }
};

````


### Solution 2:

