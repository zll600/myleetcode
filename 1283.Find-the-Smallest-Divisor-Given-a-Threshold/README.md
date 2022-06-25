#### [1283. Find the Smallest Divisor Given a Threshold](https://leetcode.cn/problems/find-the-smallest-divisor-given-a-threshold/)

Given an array of integers `nums` and an integer `threshold`, we will choose a positive integer `divisor`, divide all the array by it, and sum the division's result. Find the **smallest** `divisor` such that the result mentioned above is less than or equal to `threshold`.

Each result of the division is rounded to the nearest integer greater than or equal to that element. (For example: `7/3 = 3` and `10/2 = 5`).

The test cases are generated so that there will be an answer.

 

**Example 1:**

```
Input: nums = [1,2,5,9], threshold = 6
Output: 5
Explanation: We can get a sum to 17 (1+2+5+9) if the divisor is 1. 
If the divisor is 4 we can get a sum of 7 (1+1+2+3) and if the divisor is 5 the sum will be 5 (1+1+1+2). 
```

**Example 2:**

```
Input: nums = [44,22,33,11,1], threshold = 5
Output: 44
```

 

**Constraints:**

- `1 <= nums.length <= 5 * 104`
- `1 <= nums[i] <= 106`
- `nums.length <= threshold <= 106`

### 题目大意

给你一个整数数组 `nums` 和一个正整数 `threshold`  ，你需要选择一个正整数作为除数，然后将数组里每个数都除以它，并对除法结果求和。

请你找出能够使上述结果小于等于阈值 `threshold` 的除数中 *最小* 的那个。

每个数除以除数后都向上取整，比方说 7/3 = 3 ， 10/2 = 5 。

题目保证一定有解

## 解题思路

这道题目还是比较明显可以看出来应该属于二分答案的题目，即最小化最大值，然后再根据数据规模再次判断，应该就可以确定了

### Solution 1: Binary Search

这里的 Check 函数也不难确定，难点就是二分的范围的确定，

不难想到最大值肯定就是 `nums` 中的最大值，但是最小值可能是 `nums`

中的最小值，也可能是 1，这里最终选择的是 1



````c++
class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int low = 1, high = *max_element(nums.begin(), nums.end());
        
        while (low < high) {
            const int mid = low + (high - low) / 2;
            if (Check(nums, mid, threshold)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
    
 private:
    bool Check(const vector<int>& nums, int divisor, int threshold) {
        int sum = 0;
        for (int num : nums) {
            sum += num / divisor;
            if (num % divisor != 0) {
                ++sum;
            }
        }
        return sum <= threshold;
    }
};
````

