# [791. Custom Sort String](https://leetcode.com/problems/custom-sort-string/)

## 题目

You are given two strings order and s. All the words of `order` are **unique** and were sorted in some custom order previously.

Permute the characters of `s` so that they match the order that `order` was sorted. More specifically, if a character `x` occurs before a character `y` in `order`, then `x` should occur before `y` in the permuted string.

Return *any permutation of* `s` *that satisfies this property*.

 

**Example 1:**

```
Input: order = "cba", s = "abcd"
Output: "cbad"
Explanation: 
"a", "b", "c" appear in order, so the order of "a", "b", "c" should be "c", "b", and "a". 
Since "d" does not appear in order, it can be at any position in the returned string. "dcba", "cdba", "cbda" are also valid outputs.
```

**Example 2:**

```
Input: order = "cbafg", s = "abcd"
Output: "cbad"
```

 

**Constraints:**

- `1 <= order.length <= 26`
- `1 <= s.length <= 200`
- `order` and `s` consist of lowercase English letters.
- All the characters of `order` are **unique**.

## 题目大意

给定两个字符串 `order` 和 `s`，`order` 中的单词都是唯一的，并且按照自定义排序来排序，

我们要根据 `order` 中的字符顺序对 `s` 进行排序。更具体地说，如果 `order` 中 `x` 在 `y` 之前出现，那么返回的字符串中 `x` 也应出现在 `y` 之前。返回任意一种符合条件的字符串 `s`

## 解题思路

### Solution 1:


````c++
class Solution {
public:
    string customSortString(string order, string s) {
        // 这里给每个 order 中的字符分配一个权重
        unordered_map<char, int> weight;
        const int len = order.size();
        for (int i = 0; i < len; ++i) {
            weight[order[i]] = i;
        }

        // 排序
        sort(s.begin(), s.end(), [&](char lhs, char rhs) {
            auto it1 = weight.find(lhs);
            auto it2 = weight.find(rhs);

            if (it1 != weight.end() && it2 != weight.end()) {
                // 如果两者都存在在 order 中，按照权重排序
                return it1->second < it2->second;
            } else if (it1 == weight.end()) {
                // 如果 it1 在order 中，直接返回 false，
                return false;
            } else if (it2 == weight.end()) {
                // 如果 it2 在order 中，直接返回 true
                return true;
            }
            return false;
        });

        return s;
    }
};
````
