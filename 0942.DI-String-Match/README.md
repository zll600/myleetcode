# [942. DI String Match](https://leetcode-cn.com/problems/di-string-match/)

## 题目

A permutation `perm` of `n + 1` integers of all the integers in the range `[0, n]` can be represented as a string `s` of length `n` where:

- `s[i] == 'I'` if `perm[i] < perm[i + 1]`, and
- `s[i] == 'D'` if `perm[i] > perm[i + 1]`.

Given a string `s`, reconstruct the permutation `perm` and return it. If there are multiple valid permutations perm, return **any of them**.

 

**Example 1:**

```
Input: s = "IDID"
Output: [0,4,1,3,2]
```

**Example 2:**

```
Input: s = "III"
Output: [0,1,2,3]
```

**Example 3:**

```
Input: s = "DDI"
Output: [3,2,0,1]
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s[i]` is either `'I'` or `'D'`.

## 题目大意

由范围 `[0,n]` 内所有整数组成的 `n + 1` 个整数的排列序列可以表示为长度为 `n` 的字符串 `s` ，其中:

如果 `perm[i] < perm[i + 1]` ，那么 `s[i] == 'I'` 
如果 `perm[i] > perm[i + 1]` ，那么 `s[i] == 'D'` 
给定一个字符串 `s` ，重构排列 `perm` 并返回它。如果有多个有效排列 `perm` ，则返回其中 任何一个 。


## 解题思路

同时维护当前可以取到的最大值和最小值，遇到 `I` 取当前的最小值，遇到 `D` 取当前的最大值、

### Solution 1:


````c++
class Solution {
public:
    vector<int> diStringMatch(string s) {
        const int len = s.size();
        int low = 0, high = len;
        
        vector<int> res;
        for (char c : s) {
            if (c == 'I') {
                // 优先取小的
                res.push_back(low);
                ++low;
            } else {
                // 优先取大的
                res.push_back(high);
                --high;
            }
        }
        // 多补一个
        res.push_back(low);
        return res;
    }
};
````
