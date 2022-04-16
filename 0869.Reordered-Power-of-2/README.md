# [869. Reordered Power of 2](https://leetcode.com/problems/reordered-power-of-2/)

## 题目

You are given an integer `n`. We reorder the digits in any order (including the original order) such that the leading digit is not zero.

Return `true` *if and only if we can do this so that the resulting number is a power of two*.

 

**Example 1:**

```
Input: n = 1
Output: true
```

**Example 2:**

```
Input: n = 10
Output: false
```

 

**Constraints:**

- `1 <= n <= 109`

## 题目大意

给定正整数 `N` ，我们按任何顺序（包括原始顺序）将数字重新排序，注意其前导数字不能为零。

如果我们可以通过上述方式得到 `2` 的幂，返回 `true`；否则，返回 `false`

## 解题思路



### Solution 1:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0869.Reordered-Power-of-2/)

当然这里也可以用打表的办法来做，最多只要 32 个数就可以了

````c++
class Solution {
public:
    bool reorderedPowerOf2(int n) {
        string target = to_string(n);
        int i = 1;
        string cur = to_string(i);
        while (cur.size() <= target.size()) {
            if (cur.size() == target.size() && IsSame(cur, target)) {
                return true;
            }
            i = i << 1;
            cur = to_string(i);
        }

        return false;
    }

 private:
    // 判断 2 的次方的字符串形式，和 target 是否相同
    // 这里只要字符出现的频数相同即可
    bool IsSame(const string& cur, const string& target) {
        unordered_map<char, int> freq;
        for (char c : cur) {
            ++freq[c];
        }

        for (char c : target) {
            --freq[c];

            if (freq[c] < 0) {
                return false;
            }
        }

        return true;
    }
};
````
