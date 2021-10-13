# [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)

## 题目

Given an array of integers `nums` and an integer `k`, return *the total number of continuous subarrays whose sum equals to `k`*.

 

**Example 1:**

```
Input: nums = [1,1,1], k = 2
Output: 2
```

**Example 2:**

```
Input: nums = [1,2,3], k = 3
Output: 2
```

 

**Constraints:**

- `1 <= nums.length <= 2 * 104`
- `-1000 <= nums[i] <= 1000`
- `-107 <= k <= 107`

## 解题思路

给定一个整数数组 nums，和一个整数 k，返回 和等于 k 的连续子数组的数目

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/subarray-sum-equals-k/solution/bao-li-jie-fa-qian-zhui-he-qian-zhui-he-you-hua-ja/

### 解法1（TLE）

一个连续子数组，可以由两个指针来定位，所以采用两层循环，固定左边界，移动右边界，

注意这道题目的数据范围，因为有负数，所以每次内层遍历，都需要循环直到结尾，否则可能漏掉某些选项

`````c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {     
        int res = 0;
        const int size = nums.size();
        
        for (int i = 0; i < size; ++i) {
            int sum = 0;
            for (int j = i; j < size; ++j) {
                sum += nums[j];
                if (sum == k) {  // 这里不终止内层循环，因为元素有正有负，应该继续向后面加
                    ++res;
                }
            }
        }
        
        return res;
    }
};
`````

### 解法2（前缀和）

先简单介绍一下前缀和：

前缀和：即 `nums` 的第 0 项到 当前项 的和。
定义 `prefixSum` 数组，`prefixSum[x]`：第 0 项到 第 x 项 的和。
`prefixSum[x] = nums[0] + nums[1] +…+nums[x]`

`nums` 的某项 = 两个相邻前缀和的差：
`nums[x] = prefixSum[x] - prefixSum[x - 1]`

`nums` 的 第 i 到 j 项 的和，有：
`nums[i] +…+nums[j]=prefixSum[j] - prefixSum[i - 1]`

当 i 为 0，此时 i-1 为 -1，我们故意让 `prefixSum[-1]` 为 0，使得通式在i=0时也成立：
`nums[0] +…+nums[j]=prefixSum[j]`

这里在计算前缀和数组的时候，整体向后偏移一位，



注意这个解法，对比第一种解法其实时间复杂度并没有明显的优化，而且空间复杂度有所提高

`````c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {     
        const int size = nums.size();
        vector<int> pre_sum(size + 1);  // 前缀和数组
        pre_sum[0] = 0;
        for (int i = 0; i < size; ++i) {  // 注意，这里有一位偏移
            pre_sum[i + 1] = pre_sum[i] + nums[i]; 
        }
        
        int res = 0;
        for (int left = 0; left < size; ++left) {
            for (int right = left; right < size; ++right) {
                if (pre_sum[right + 1] - pre_sum[left] == k) {  // pre_sum[i] - pre_sum[j - 1] == k，这里将下标右移了
                    ++res;
                }
            }
        }
        
        return res;
    }
};
`````

### 解法3（前缀和 + 哈希）

如果注释中为什么插入 (0, 1) 是必要的不理解的话，可以参考上面的题解

`````c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {     
        unordered_map<int, int> freq;
        freq.emplace(0, 1);  // 前缀和 0 出现的次数为 1
        // 注意这里的 0 是必须的，举个例子 [1, 1, 1] 和 1，如果没有这个提前放置的 0，那么第一个 1 是不能计入的
        
        
        int pre_sum = 0;
        int res = 0;
        for (int num : nums) {
            pre_sum += num;  // 计算前缀和
            
            if (freq.find(pre_sum - k) != freq.end()) {
                res += freq.at(pre_sum - k);
            }
            
            ++freq[pre_sum];
        }
        
        return res;
    }
};
`````

