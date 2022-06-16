# [1186. Maximum Subarray Sum with One Deletion](https://leetcode.cn/problems/maximum-subarray-sum-with-one-deletion/)

Given an array of integers, return the maximum sum for a **non-empty** subarray (contiguous elements) with at most one element deletion. In other  words, you want to choose a subarray and optionally delete one element  from it so that there is still at least one element left and the sum of  the remaining elements is maximum possible.

Note that the subarray needs to be **non-empty** after deleting one element.

 

**Example 1:**

```
Input: arr = [1,-2,0,3]
Output: 4
Explanation: Because we can choose [1, -2, 0, 3] and drop -2, thus the subarray [1, 0, 3] becomes the maximum value.
```

**Example 2:**

```
Input: arr = [1,-2,-2,3]
Output: 3
Explanation: We just choose [3] and it's the maximum sum.
```

**Example 3:**

```
Input: arr = [-1,-1,-1,-1]
Output: -1
Explanation: The final subarray needs to be non-empty. You can't choose [-1] and delete -1 from it, then get an empty subarray to make the sum equals to 0.
```

 

**Constraints:**

- `1 <= arr.length <= 105`
- `-104 <= arr[i] <= 104`

## 题目大意

给你一个整数数组，返回它的某个 非空 子数组（连续元素）在执行一次可选的删除操作后，所能得到的最大元素总和。换句话说，你可以从原数组中选出一个子数组，并可以决定要不要从中删除一个元素（只能删一次哦），（删除后）子数组中至少应当有一个元素，然后该子数组（剩下）的元素总和是所有子数组之中最大的

注意，删除一个元素后，子数组 不能为空

## 解题思路

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/maximum-subarray-sum-with-one-deletion/solution/dian-xing-de-zhuang-tai-ji-dpwen-ti-by-y-q6mq/)

定义状态 dp0 表示当前位置未删除，dp1 表示当前位置已删除

遇到每一个值：

- if num >= 0，那么不删除的最大值可以是累加过来的，也可以只包含自身（如果之前的累加和为负数或0），删除的最大值可以
- if num < 0，

````c++
class Solution {
public:
    int maximumSum(vector<int>& arr) {
        // dp0 -- keep dp1 -- delete
        int dp0 = arr[0], dp1 = 0, res = dp0;
        for (int i = 1; i < arr.size(); ++i) {
            if (arr[i] >= 0) {
                // maximum sum
                dp0 = max(0, dp0) + arr[i];
                // subarry will be empty if delete arr[i]
                dp1 = dp1 + arr[i];
            } else {
                // delete arr[i] or before
                dp1 = max(dp0, dp1 + arr[i]);
                // don't delete
                dp0 = max(0, dp0) + arr[i];
            }
            res = max(res, dp0);
            res = max(res, dp1);
        }
        return res;
    }
};
````

