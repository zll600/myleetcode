# [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)

## 题目

Given an array of integers `temperatures` represents the daily temperatures, return *an array* `answer` *such that* `answer[i]` *is the number of days you have to wait after the* `ith` *day to get a warmer temperature*. If there is no future day for which this is possible, keep `answer[i] == 0` instead.

 

**Example 1:**

```
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]
```

**Example 2:**

```
Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]
```

**Example 3:**

```
Input: temperatures = [30,60,90]
Output: [1,1,0]
```

 

**Constraints:**

- `1 <= temperatures.length <= 105`
- `30 <= temperatures[i] <= 100`

## 题目大意

给定一个整数数组表示 temperatures 表示每日温度，要求输出比当天温度高的在未来的哪一天，输出未来第几天的天数，如果没有结果为0

## 解题思路

* 可以使用暴力解法，即两层循环

* 使用单调栈来进行模拟，维护一个单调递减的栈。

## 代码

````c++
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        int size = T.size();
        vector<int> res(size);
        stack<int> sta; 
        
        for (int i = 0; i < size; ++i) {
            while (!sta.empty() && T[sta.top()] < T[i]) {
                res[sta.top()] = i - sta.top();
                sta.pop();
            }
            sta.push(i);
        }
        return res;
    }
    
    // 解法一：暴力解，会超时
    /*
    vector<int> dailyTemperatures(vector<int>& arr) {
        int size = arr.size();
        vector<int> res(size);
        
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                if (arr[j] > arr[i]) {
                    res[i] = j - i;
                    break;
                }
            }
        }
        
        return res;
    }*/
};
````

