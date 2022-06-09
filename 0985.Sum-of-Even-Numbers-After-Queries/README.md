# [985. Sum of Even Numbers After Queries](https://leetcode.cn/problems/sum-of-even-numbers-after-queries/)

## 题目

You are given an integer array `nums` and an array `queries` where `queries[i] = [vali, indexi]`.

For each query `i`, first, apply `nums[indexi] = nums[indexi] + vali`, then print the sum of the even values of `nums`.

Return *an integer array* `answer` *where* `answer[i]` *is the answer to the* `ith` *query*.

 

**Example 1:**

```
Input: nums = [1,2,3,4], queries = [[1,0],[-3,1],[-4,0],[2,3]]
Output: [8,6,2,4]
Explanation: At the beginning, the array is [1,2,3,4].
After adding 1 to nums[0], the array is [2,2,3,4], and the sum of even values is 2 + 2 + 4 = 8.
After adding -3 to nums[1], the array is [2,-1,3,4], and the sum of even values is 2 + 4 = 6.
After adding -4 to nums[0], the array is [-2,-1,3,4], and the sum of even values is -2 + 4 = 2.
After adding 2 to nums[3], the array is [-2,-1,3,6], and the sum of even values is -2 + 6 = 4.
```

**Example 2:**

```
Input: nums = [1], queries = [[4,0]]
Output: [0]
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `-104 <= nums[i] <= 104`
- `1 <= queries.length <= 104`
- `-104 <= vali <= 104`
- `0 <= indexi < nums.length`

## 题目大意

给出一个整数数组 `A` 和一个查询数组 `queries`

对于第 `i` 次查询，有 `val = queries[i][0]`, `index = queries[i][1]`，我们会把 `val` 加到 `A[index]` 上。然后，第 `i` 次查询的答案是 `A` 中偶数值的和

（此处给定的 `index = queries[i][1]` 是从 `0` 开始的索引，每次查询都会永久修改数组 `A`）

返回所有查询的答案。你的答案应当以数组 `answer` 给出，`answer[i]` 为第 `i` 次查询的答案

## 解题思路


### Solution 1:

根据题意简单模拟一下就可以了
`
````c++
class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int even_sum = 0;
        
        const int len = nums.size();
        for (int i = 0; i < len; ++i) {
            if (nums[i] % 2 == 0) {
                even_sum += nums[i];
            }
        }
        
        
        vector<int> ans;
        for (const auto& query : queries) {
            int val = query[0], index = query[1];
            
            // 如果之前有影响结果，撤销
            if (nums[index] % 2 == 0) {
                even_sum -= nums[index];
            }
            // 更新
            nums[index] += val;
            // 如果可以影响结果，累加
            if (nums[index] % 2 == 0) {
                even_sum += nums[index];
            }
            
            ans.push_back(even_sum);
        }
        return ans;
    }
};
````


