# [801. Minimum Swaps To Make Sequences Increasing](https://leetcode-cn.com/problems/minimum-swaps-to-make-sequences-increasing/)

You are given two integer arrays of the same length `nums1` and `nums2`. In one operation, you are allowed to swap `nums1[i]` with `nums2[i]`.

- For example, if `nums1 = [1,2,3,8]`, and `nums2 = [5,6,7,4]`, you can swap the element at `i = 3` to obtain `nums1 = [1,2,3,4]` and `nums2 = [5,6,7,8]`.

Return *the minimum number of needed operations to make* `nums1` *and* `nums2` ***strictly increasing***. The test cases are generated so that the given input always makes it possible.

An array `arr` is **strictly increasing** if and only if `arr[0] < arr[1] < arr[2] < ... < arr[arr.length - 1]`.

 

**Example 1:**

```
Input: nums1 = [1,3,5,4], nums2 = [1,2,3,7]
Output: 1
Explanation: 
Swap nums1[3] and nums2[3]. Then the sequences are:
nums1 = [1, 3, 5, 7] and nums2 = [1, 2, 3, 4]
which are both strictly increasing.
```

**Example 2:**

```
Input: nums1 = [0,3,5,8,9], nums2 = [2,1,4,6,9]
Output: 1
```

 

**Constraints:**

- `2 <= nums1.length <= 105`
- `nums2.length == nums1.length`
- `0 <= nums1[i], nums2[i] <= 2 * 105`

## 题目大意



## 解题思路

动态规划，可以尝试题目问什么就将什么设置为状态，不一定总是，但是可以试一试，如果可以方便的写出状态转移方程，就可以继续进行，

否则可以先写出 dfs 版本来看出那些变量决定了当前的状态，然后转化为dp

### Solution 1: DP

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/minimum-swaps-to-make-sequences-increasing/solution/dong-tai-gui-hua-de-yi-ban-bu-zou-by-li-zhi-chao-4/)

这道题目的状态转移是基于题目保证输入一定是可以符合条件的，所以就只有这几种情况需要我们去考虑

````c++
class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();

        // dp[i][j] 表示前 i 个位置，交换或者不交换，需要的交换次数
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = 1;

        for (int i = 1; i < n; ++i) {
            if (nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1]) {
                // 如果两个数组本身是有序的
                if (nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1]) {
                    // 如果交换之后还是有序的

                    // 不交换
                    dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]);
                    // 交换
                    dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + 1;
                } else {
                    // 如果交换之后会产生无序

                    // 不交换
                    dp[i][0] = dp[i - 1][0];
                    // 交换
                    dp[i][1] = dp[i - 1][1] + 1;
                }
            } else {
                // 如果两个数组本身无序，

                // 不交换当前位置，那么需要交换前一个位置
                dp[i][0] = dp[i - 1][1];
                // 交换当前位置，那么前一个位置就不需要交换
                dp[i][1] = dp[i - 1][0] + 1;
            }
        }

        return min(dp[n - 1][0], dp[n - 1][1]);
    }
};
````
