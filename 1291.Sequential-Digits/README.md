#### [1291. Sequential Digits](https://leetcode.cn/problems/sequential-digits/)

An integer has *sequential digits* if and only if each digit in the number is one more than the previous digit.

Return a **sorted** list of all the integers in the range `[low, high]` inclusive that have sequential digits.

 

**Example 1:**

```
Input: low = 100, high = 300
Output: [123,234]
```

**Example 2:**

```
Input: low = 1000, high = 13000
Output: [1234,2345,3456,4567,5678,6789,12345]
```

 

**Constraints:**

- `10 <= low <= high <= 10^9`



## 题目大意

我们定义「顺次数」为：每一位上的数字都比前一位上的数字大 1 的整数。

请你返回由 [low, high] 范围内所有顺次数组成的 有序 列表（从小到大排序）。

## 解题思路



### Solution 1: 

这道题目的结果集是常数，而且并不大，所以第一个想到的肯定就是打表了



`````c++
class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        auto left = data_.begin();
        while (left != data_.end() && *left < low) {
            ++left;
        }
        auto right = left;
        while (right != data_.end() && *right <= high) {
            ++right;
        }
        return vector<int>(left, right);
    }
    
 private:
    vector<int> data_ = {
            12, 23, 34, 45, 56, 67, 78, 89,
            123, 234, 345, 456, 567, 678, 789,
            1234, 2345, 3456, 4567, 5678, 6789,
            12345, 23456, 34567, 45678, 56789,
            123456, 234567, 345678, 456789,
            1234567, 2345678, 3456789,
            12345678, 23456789,
            123456789
        };
};
`````

