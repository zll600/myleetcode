# [907. Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/)

## 题目

Given an array of integers arr, find the sum of `min(b)`, where `b` ranges over every (contiguous) subarray of `arr`. Since the answer may be large, return the answer **modulo** `109 + 7`.

 

**Example 1:**

```
Input: arr = [3,1,2,4]
Output: 17
Explanation: 
Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
Sum is 17.
```

**Example 2:**

```
Input: arr = [11,81,94,43,3]
Output: 444
```

 

**Constraints:**

- `1 <= arr.length <= 3 * 104`
- `1 <= arr[i] <= 3 * 104`

## 题目大意

给定一个整数数组 arr，找到找到 min(b) 的总和，其中 b 的范围为 arr 的每个（连续）子数组。

## 解题思路

* 最容易想到的就暴力搜索，结果超时，
  * 分析原因是，某个区间的最小值可能是很多区间的最小值，但是暴力枚举所有区间，导致每个区间都要被遍历一遍，所以关键就在于如果减少遍历的次数，
* 使用一个单调栈，进行计算，可以减少遍历区间的次数，可以类比第 84 题，分别向左和向右扩，

````c++
class Solution {
public:
    // 解法一：暴力解。
    /*
    int sumSubarrayMins(vector<int>& arr) {
        int mod = 1000000007;
        int res = 0;
        
        int size = arr.size();
        for (int i = 0; i < size; ++i) {
            stack<int> sta;
            sta.push(arr[i]);
            
            for (int j = i; j < size; ++j) {
                if (sta.top() >= arr[j]) {
                    sta.pop();
                    sta.push(arr[j]);
                }
                res += sta.top();
                res %= mod;
            }
        }
        
        return res;
    }*/
    
    // 解法二：暴力解，用一个变量代替单元素栈.
    /*
    int sumSubarrayMins(vector<int>& arr) {
        int mod = 1000000007;
        int res = 0;
        
        int size = arr.size();
        for (int i = 0; i < size; ++i) {
            int smallest = arr[i];
            for (int j = i; j < size; ++j) {
                if (smallest >= arr[j]) {
                    smallest = arr[j];
                }
                res += smallest;
                res %= mod;
            }
        }
        return res;
    }*/
    
    // 解法二：使用一个单调栈
    /* https://leetcode-cn.com/problems/sum-of-subarray-minimums/solution/dan-diao-zhan-zuo-you-liang-bian-di-yi-g-ww3n/
    */
    /*
    int sumSubarrayMins(vector<int>& arr) {
        int mod = 1000000007;
        stack<int> sta;
        arr.push_back(0);
        
        int size = arr.size();
        int res = 0;
        for (int i = 0; i < arr.size(); ++i) {
            while (!sta.empty() && arr[i] < arr[sta.top()]) {
                int idx = sta.top();
                sta.pop();
                
                int prev = sta.empty() ? -1 : sta.top();
                int prev_len = idx - prev - 1;
                int last_len = i - idx - 1;
                res += (1L * arr[idx] * (prev_len + 1) * (last_len + 1)) % mod;
                res %= mod;
            }
            sta.push(i);
        }
        
        return res;
    }*/
    
    // 这个解法，目前还有问题
    int sumSubarrayMins(vector<int>& arr) {
        int mod = 1000000007;
        int res = 0;
        int size = arr.size();
        
        stack<int> left;
        vector<int> lefts;
        for (int i = 0; i < size; ++i) {
            int count = 1;
            while (!left.empty() && arr[i] < arr[left.top()]) {
                count += left.top();
                left.pop();
            }
            left.push(i);
            lefts[i] = count;
        }
        
        stack<int> right;
        vector<int> rights;
        for (int i = size - 1; i >= 0; --i) {
            int count = 1;
            while (!right.empty() && arr[i] >= arr[right.top()]) {
                count += right.top();
                right.pop();
            }
            right.push(i);
            rights[i] = count;
        }
        
        for (int i = 0; i < size; ++i) {
            res += (1L * arr[i] * lefts[i] * rights[i]) % mod;
            res %= mod;
        }
        
        return res;
    }
};
````

