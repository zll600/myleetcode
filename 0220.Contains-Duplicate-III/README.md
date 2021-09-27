# [220. Contains Duplicate III](https://leetcode.com/problems/contains-duplicate-iii/)

Given an integer array `nums` and two integers `k` and `t`, return `true` if there are **two distinct indices** `i` and `j` in the array such that `abs(nums[i] - nums[j]) <= t` and `abs(i - j) <= k`.

 

**Example 1:**

```
Input: nums = [1,2,3,1], k = 3, t = 0
Output: true
```

**Example 2:**

```
Input: nums = [1,0,1,1], k = 1, t = 2
Output: true
```

**Example 3:**

```
Input: nums = [1,5,9,1,5,9], k = 2, t = 3
Output: false
```

 

**Constraints:**

- `0 <= nums.length <= 2 * 104`
- `-231 <= nums[i] <= 231 - 1`
- `0 <= k <= 104`
- `0 <= t <= 231 - 1`

## 题目大意

给定一个证书数组 nums 和两个整数 k，和 t，如果存在两个不同的索引 i, j 满足 `abs(nums[i], nums[j]) <= t` 且`abs(i - j) <= k`

## 解题思路

### 解法1

暴力解法，会超时，

这里需要注意两个问题：

* 边界处理，数组元素数目少于两个
* 整数减法出现溢出

`````c++
class Solution {
public:
    // 暴力解法（超时）
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (nums.size() < 2) {
            return false;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size() && j - i <= k; j++) {
                if (abs(1L * nums[j] - nums[i]) <= 1L * t) {    // 这里是为了防止出现溢出的情况
                    return true;
                }
            }
        }
        
        return false;
    }
};
`````

### 解法2（利用桶排序的思想）

这种解法利用的是桶排序的思想，这里放上这篇题解：https://leetcode-cn.com/problems/contains-duplicate-iii/solution/c-li-yong-tong-fen-zu-xiang-xi-jie-shi-b-ofj6/

每个桶内的数一定满足 abs(nums[i] - nums[j]) <= t，相邻的桶可能满足，但需要作判断

``````c++
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (nums.size() < 2) {  // 处理边界情况
            return false;
        }
        
        unordered_map<int, int> buckets;  // 这里利用哈希表来做桶
        for (int i = 0; i < nums.size(); i++) {
            long cur = nums[i]; // 这里做整型提升，避免下面的减法运算溢出
            int id = GetId(cur, t); // 得到桶 id
            
            if (i - (k + 1) >= 0) { // 前面 i - (k + 1) 的桶超出范围，将其删除
                buckets.erase(GetId(nums[i - (k + 1)], t));
            }
            
            if (buckets.find(id) != buckets.end()) {    // 如果当前 id 的桶内有已经有数，可以直接返回
                return true;
            }
            // 查找前一个桶中有没有元素可以满足条件
            if (buckets.find(id - 1) != buckets.end() && abs(buckets[id - 1] - cur) <= t) {
                return true;
            }
            // 查找后一个桶中有没有元素可以满足条件
            if (buckets.find(id + 1) != buckets.end() && abs(buckets[id + 1] - cur) <= t) {
                return true;
            }
            
            // 没有找到符合条件的，存在这个桶，每个桶中最多存储一个元素
            buckets[id] = cur;
        }
        
        return false;
    }
 private:
    long GetId(long x, long t) {
        if (x >= 0) {   // x >= 0 直接分桶
            return x / (t + 1);
        } else {    // x < 0 先偏移再分组
            return (x + 1) / (t + 1) - 1;
        }
    }
};
``````

