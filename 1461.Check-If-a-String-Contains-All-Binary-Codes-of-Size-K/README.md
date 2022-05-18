# [1461. Check If a String Contains All Binary Codes of Size K](https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/)

## 题目

Given a binary string `s` and an integer `k`, return `true` *if every binary code of length* `k` *is a substring of* `s`. Otherwise, return `false`.

 

**Example 1:**

```
Input: s = "00110110", k = 2
Output: true
Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indices 0, 1, 3 and 2 respectively.
```

**Example 2:**

```
Input: s = "0110", k = 1
Output: true
Explanation: The binary codes of length 1 are "0" and "1", it is clear that both exist as a substring. 
```

**Example 3:**

```
Input: s = "0110", k = 2
Output: false
Explanation: The binary code "00" is of length 2 and does not exist in the array.
```

 

**Constraints:**

- `1 <= s.length <= 5 * 105`
- `s[i]` is either `'0'` or `'1'`.
- `1 <= k <= 20`

## 题目大意

给你一个二进制字符串 s 和一个整数 k 。如果所有长度为 k 的二进制字符串都是 s 的子串，请返回 True ，否则请返回 False 

## 解题思路

可以枚举出 s 中所有长度为 k 的字符串，看其数量能否达到 2^k，

或者预处理得到 2^k 中长度为 k 的二进制字符串，然后进行字符串匹配

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/check-if-a-string-contains-all-binary-codes-of-size-k/solution/ha-xi-biao-zhong-cun-zi-fu-chuan-shi-jian-fu-za-du/)

### Solution 1:

这种解法枚举 s 中所有长度为 k 的子串，然后查看其数量能否达到 2^k 个

````c++
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        unordered_set<string> cache;
        for (int i = 0; i + k <= s.size(); ++i) {
            cache.insert(std::move(s.substr(i, k)));
        }
        return cache.size() == (1 << k);
    }
};
````

### Solution 2: Sliding Window

这里使用子串等价的整数来做 key，避免了计算哈希值的开销

并使用 size 为 k 的滑动窗口来更新子串所表示的 key

````c++
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        if (k > s.size()) {
            return 0;
        }

        int cur = 0;
        for (int i = 0; i < k - 1; ++i) {
            cur = 2 * cur + (s[i] == '1');
        }

        unordered_set<int> cache;
        for (int i = k - 1; i < s.size(); ++i) {
            cur = 2 * cur + (s[i] == '1');
            cache.insert(cur);
            cur &= ~(1 << (k - 1));
        }
        return cache.size() == (1 << k);
    }
};
````
