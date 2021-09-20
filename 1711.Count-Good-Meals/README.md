# [1711. Count Good Meals](https://leetcode.com/problems/count-good-meals/)

## 题目

A **good meal** is a meal that contains **exactly two different food items** with a sum of deliciousness equal to a power of two.

You can pick **any** two different foods to make a good meal.

Given an array of integers `deliciousness` where `deliciousness[i]` is the deliciousness of the `ith` item of food, return *the number of different **good meals** you can make from this list modulo* `109 + 7`.

Note that items with different indices are considered different even if they have the same deliciousness value.

 

**Example 1:**

```
Input: deliciousness = [1,3,5,7,9]
Output: 4
Explanation: The good meals are (1,3), (1,7), (3,5) and, (7,9).
Their respective sums are 4, 8, 8, and 16, all of which are powers of 2.
```

**Example 2:**

```
Input: deliciousness = [1,1,1,3,3,3,7]
Output: 15
Explanation: The good meals are (1,1) with 3 ways, (1,3) with 9 ways, and (1,7) with 3 ways.
```

 

**Constraints:**

- `1 <= deliciousness.length <= 105`
- `0 <= deliciousness[i] <= 220`

## 题目大意

大餐是恰好包含两种不同的食物，且美味程度的总和是 2 的幂，

你可以选择任意两种不同的食物做一顿大餐，给定一个整数数组 deliciousness 其中 deliciousness[i] 是第 i 种事务的美味程度，返回你做出的不同大餐的数目

注意：不同的下标代表不同的食物，即使他们有相同的美味程度，

## 解题思路

* 这道题直接的想法，就是枚举出所有的组合，然后判断是否符合条件，不过这种做法超时了，所以这道题的核心在于如何选出两个数来凑成2 的幂，
* 进阶一点的想法是利用 “两数和”的思想，可以参考这篇题解：https://leetcode-cn.com/problems/count-good-meals/solution/gong-shui-san-xie-xiang-jie-san-chong-gu-nn4f/

## 代码

`````c++
class Solution {
public:
    // 枚举之前出现过的所有值，
    int countPairs1(vector<int>& deliciousness) {
        // 保存出现过的值和次数
        unordered_map<int, int> freq;
        
        int res = 0;
        int len = deliciousness.size();
        for (int i = 0; i < len; ++i) {
            int tmp = deliciousness[i];
            for (const auto& it : freq) {
                if (Check(tmp + it.first)) {
                    res += it.second;
                    res %= mod;
                }
            }
            ++freq[tmp];
        }
        
        return res;
    }
    
    // 利用容斥原理
    int countPairs2(vector<int>& deliciousness) {
        unordered_map<int, int> freq;
        for (int it : deliciousness) {
            ++freq[it];
        }
        
        long res = 0;
        for (const auto& it : freq) {
            for (int i = 1; i < limit; i <<= 1) {
                int val = i - it.first;
                if (freq.find(val) != freq.end()) {
                    if (val == it.first) {	// 如果两个数相等，这是求组合数，需要特殊处理一下
                        res += 1L * freq.at(val) * (freq.at(val) - 1);
                    } else {
                        res += 1L * freq.at(it.first) * freq.at(val);
                    }
                }
            }
        }
        res >>= 1;
        
        return static_cast<int>(res %= mod);
    }
    
    // 边遍历边计算
    int countPairs(vector<int>& deliciousness) {
        unordered_map<int, int> freq;
        int res = 0;
        
        for (int item : deliciousness) {
            for (int i = 1; i < limit; i <<= 1) {
                int key = i - item;
                if (freq.find(key) != freq.end()) {
                    res += freq.at(key);
                    res %= mod;
                }
            }
            ++freq[item];
        }
        
        return res;
    }
    
 private:
    static const int mod = 1000000007;
    static const int limit = 1 << 22;
    bool Check(int n) {
        return (n > 0 && (n & (n - 1)) == 0);
    }
};
`````

