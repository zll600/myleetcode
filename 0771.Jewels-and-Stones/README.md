# [771. Jewels and Stones](https://leetcode.com/problems/jewels-and-stones/)

## 题目

You're given strings `jewels` representing the types of stones that are jewels, and `stones` representing the stones you have. Each character in `stones` is a type of stone you have. You want to know how many of the stones you have are also jewels.

Letters are case sensitive, so `"a"` is considered a different type of stone from `"A"`.

 

**Example 1:**

```
Input: jewels = "aA", stones = "aAAbbbb"
Output: 3
```

**Example 2:**

```
Input: jewels = "z", stones = "ZZ"
Output: 0
```

 

**Constraints:**

- `1 <= jewels.length, stones.length <= 50`
- `jewels` and `stones` consist of only English letters.
- All the characters of `jewels` are **unique**.

## 题目大意

给定字符串 `jewels` 代表石头中宝石的类型，和字符串 `stones` 代表你拥有的石头。`stones` 中每个字符代表了一种你拥有的石头的类型，你想知道你拥有的石头中有多少是宝石。

字母区分大小写，因此 “a” 和 “A” 是不同类型的石头。

## 解题思路

有点像找两个集合的交集，不过 石头中是可以重复的

### Solution 1: hash

这里利用一个 `unordered_set` 来判重


````c++
class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        // 生成一个 哈希，方便查找
        unordered_set<char> kinds(jewels.begin(), jewels.end());

        // 统计结果
        int res = 0;
        for (char c : stones) {
            if (kinds.find(c) != kinds.end()) {
                ++res;
            }
        }

        return res;
    }
};
````
