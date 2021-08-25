# [1052. Grumpy Bookstore Owner](https://leetcode.com/problems/grumpy-bookstore-owner/)

## 题目

There is a bookstore owner that has a store open for `n` minutes. Every minute, some number of customers enter the store. You are given an integer array `customers` of length `n` where `customers[i]` is the number of the customer that enters the store at the start of the `ith` minute and all those customers leave after the end of that minute.

On some minutes, the bookstore owner is grumpy. You are given a binary array grumpy where `grumpy[i]` is `1` if the bookstore owner is grumpy during the `ith` minute, and is `0` otherwise.

When the bookstore owner is grumpy, the customers of that minute are not satisfied, otherwise, they are satisfied.

The bookstore owner knows a secret technique to keep themselves not grumpy for `minutes` consecutive minutes, but can only use it once.

Return *the maximum number of customers that can be satisfied throughout the day*.

 

**Example 1:**

```
Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
Output: 16
Explanation: The bookstore owner keeps themselves not grumpy for the last 3 minutes. 
The maximum number of customers that can be satisfied = 1 + 1 + 1 + 1 + 7 + 5 = 16.
```

**Example 2:**

```
Input: customers = [1], grumpy = [0], minutes = 1
Output: 1
```

 

**Constraints:**

- `n == customers.length == grumpy.length`
- `1 <= minutes <= n <= 2 * 104`
- `0 <= customers[i] <= 1000`
- `grumpy[i]` is either `0` or `1`.

## 题目大意

有一个每天开 n 分钟的书店，有一个长度为 n 的数组 customers，代表每分钟进入书店的人数，这一分钟进店的客人都会在这一分钟结束的时候离开，再某一分钟内，书店主任会生气（grumpy[i]  = 1），其余时间则正常（grumpy[i] = 0），当书店主人生气的时候，客人不会满意，否则客人满意，书店主任有一个办法可以抑制自己连续 minutes 不生气，但是只能用一次，返回一天内最多有多少客人会满意。

## 解题思路

* 给出一个顾客入店时间表和书店老板发脾气的时间表。两个数组的时间是一一对应的，即相同下标对应的相同的时间。书店老板可以控制自己在 X 分钟内不发火，但是只能控制一次。问有多少顾客能在书店老板不发火的时候在书店里看书。抽象一下，给出一个价值数组和一个装着 0 和 1 的数组，当价值数组的下标对应另外一个数组相同下标的值是 0 的时候，那么这个价值可以累加，当对应是 1 的时候，就不能加上这个价值。现在可以让装着 0 和 1 的数组中连续 X 个数都变成 0，问最终价值最大是多少？
* 
* 根据题目，每分钟进入的顾客数量数组和书店老板生气的时间一一对应，如果求满意客人的最多数量，如果对应的书店老板没有生气就可以将对应的客人数量计入，如果老板生气，则不能计入，老板可以可以控制自己连续 minutes 分钟内不生气，意味着可以让 grumpy 数组的连续 minutes 均为 0（即：是可计入总结果的）。
* 可以利用“滑动窗口”，暴力解法是持续扩大窗口直至窗口的大小为 minutes 时，计算此时对应的客人数，当整个宽度为 minutes 的窗口滑过整个整个数组后，输出维护的最大值即可。但这个方法耗时比较长，因为每次计算结果时，都需要遍历整个数组。
* 每次计算数组总结果时，影响最终结果的因素主要是窗口中 grumpy 对应为 1 的客人数量的累加和，因为如果把这个窗口里面的 1 都变成 0 以后，对结果的影响也是最大的。所以可以用一个变量 customers0 专门记录 grumpy 数组中为 0 的对应的值，累加起来。因为这部分值再计算结果时，不会影响最终的结果。唯一影响结果的是 1 变成 0，用 customers1 记录 grumpy 数组中为 1 的对应的值，再窗口滑动过程中，找到 customers 的最大值，就是最终结果的最大值。

## 代码

````c++
class Solution {
public:
    // 滑动窗口 暴力解法
    /*
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int size = customers.size();
        if (size == 0) {
            return 0;
        }
        
        int res = 0;
        int left = 0;
        int right = -1;
        
        while (left < size) {
            if (right < size - 1 && right - left + 1 < minutes) {
                ++right;
            } else {
                if (right - left + 1 == minutes) {
                    res = max(res, SumSatisfied(customers, grumpy, left, right));
                }
                ++left;
            }
        }
        
        return res;
    }
    
 private:
    int SumSatisfied(const vector<int>& customers, const vector<int>& grumpy, int start, int end) {
        int sum = 0;
        int size = customers.size();
        
        for (int i = 0; i < size; ++i) {
            if (i < start || i > end) {
                if (grumpy[i] == 0) {
                    sum += customers[i];
                }
            } else {
                sum += customers[i];
            }
        }
        
        return sum;
    }
    */
    
    // 滑动窗口优化
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int size = customers.size();
        int left = 0;
        int right = 0;
        int customers1 = 0;
        int customers0 = 0;
        int max_customers1 = 0;
        
        for (; right < size; ++right) {
            if (grumpy[right] == 0) {
                customers0 += customers[right];
            } else {
                customers1 += customers[right];
                
                while (right - left + 1 > minutes) {
                    if (grumpy[left] == 1) {
                        customers1 -= customers[left];
                    }
                    ++left;
                }
                
                max_customers1 = max(max_customers1, customers1);
            }
        }
        
        return max_customers1 + customers0;
    }
};
````

