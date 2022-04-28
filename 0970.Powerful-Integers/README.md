# [970. Powerful Integers](https://leetcode.com/problems/powerful-integers/)

## 题目

An integer is **powerful** if it can be represented as `xi + yj` for some integers `i >= 0` and `j >= 0`.

You may return the answer in **any order**. In your answer, each value should occur **at most once**.

 

**Example 1:**

```
Input: x = 2, y = 3, bound = 10
Output: [2,3,4,5,7,9,10]
Explanation:
2 = 20 + 30
3 = 21 + 30
4 = 20 + 31
5 = 21 + 31
7 = 22 + 31
9 = 23 + 30
10 = 20 + 32
```

**Example 2:**

```
Input: x = 3, y = 5, bound = 15
Output: [2,4,6,8,10,14]
```

 

**Constraints:**

- `1 <= x, y <= 100`
- `0 <= bound <= 106`

## 题目大意

给定两个正整数 `x` 和 `y`，如果某一整数等于 `x^i + y^j`，其中整数 `i >= 0` 且 `j >= 0`，那么我们认为该整数是一个强整数

返回值小于或等于 `bound` 的所有强整数组成的列表

你可以按任何顺序返回答案, 在你的回答中，每个值最多出现一次

## 解题思路

### Solution 1:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0900~0999/0970.Powerful-Integers/)

这道题就是直接暴力解就可以了，不过要注意 1 的任意次方都是 1，这一点是有可能造成四循环的，必须要进行特殊处理

````c++
class Solution {
public:
    vector<int> powerfulIntegers(int x, int y, int bound) {
        // 如果两个都为 1，需要做特殊处理，否则会造成死循环
        if (x == 1 && y == 1) {
            if (bound < 2) {
                return {};
            }
            return {2};
        }

        // 如果不存在 1，那么后面流程正常，
        // 如果存在一个 1，1 只能放在外层循环之中
        if (x > y) {
            swap(x, y);
        }

        // 做判重处理，防止重复添加
        unordered_set<int> cache;

        vector<int> res;
        // 暴力枚举所有可以产生的值
        int i = 0;
        while (true) {
            bool flag = false;

            for (int j = 0; Pow(x, i) + Pow(y, j) <= bound; ++j) {
                int val = Pow(x, i) + Pow(y, j);

                if (cache.find(val) == cache.end()) {
                    flag = true;
                    cache.insert(val);
                    res.push_back(val);
                }
            }

            if (!flag) {
                break;
            }
            ++i;
        }

        return res;
    }

 private:
    int Pow(int base, int exp) {
        return static_cast<int>(std::pow(base, exp));
    }
};
````
