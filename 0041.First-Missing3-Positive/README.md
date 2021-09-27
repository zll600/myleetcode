# [41. First Missing Positive](https://leetcode.com/problems/first-missing-positive/description/)

## 题目

Given an unsorted integer array `nums`, return the smallest missing positive integer.

You must implement an algorithm that runs in `O(n)` time and uses constant extra space.

 

**Example 1:**

```
Input: nums = [1,2,0]
Output: 3
```

**Example 2:**

```
Input: nums = [3,4,-1,1]
Output: 2
```

**Example 3:**

```
Input: nums = [7,8,9,11,12]
Output: 1
```

 

**Constraints:**

- `1 <= nums.length <= 5 * 105`
- `-231 <= nums[i] <= 231 - 1`

## 题目大意

给定一个未排序的整数数组，返回最小的缺失的正整数，

你必须使用 O(n)的算法和常数的额外空间

## 解题思路

这道题的引入 **原地哈希**这个概念，具体可以参考这篇题解：https://leetcode-cn.com/problems/first-missing-positive/solution/tong-pai-xu-python-dai-ma-by-liweiwei1419/

### 解法1：利用哈希表（不符合要求）

先将数组中的所有的数放入一个 set 中，然后从 1开始找，知道找到 set 中没有的第一数，返回，不过显然，空间绝对超了，算法复杂度分析，需要好好学学了（留待以后一定学）

````c++
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        unordered_set<int> bucket;
        for (int num : nums) {
            bucket.insert(num);
        }
        
        int i = 1;
        while (true) {
            if (bucket.find(i) == bucket.end()) {
                return i;
            }
            i++;
        }
        return -1;
    }
};
````

### 解法2（不符合条件）：利用二分查找

先将原数组排序，然后从 1开始查找第一个没有出现过的正整数，如果没有返回排序后数组的长度 + 1

`````c++
class Solution {
public:
    // 排序 + 二分查找
    int firstMissingPositive(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        for (int i = 1; i <= nums.size(); i++) {
            int ret = BinarySearch(nums, i);
            if (ret == -1) {
                return i;
            }
        }
        
        return nums.size() + 1;
    }
    
 private:
    int BinarySearch(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }
};
`````

### 解法3（找突变的点）

先排序，然后找到两个正数相差大于1 的位置，然后返回前一个数 + 1，这种解法，是对上面二分查找的一种优化

`````c++
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        // 排序
        sort(nums.begin(), nums.end());
        
        int pre = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] <= 0 || nums[i] == pre) {
                continue;   // 这里直接跳过，避免更新 pre
            } else if (nums[i] > pre + 1){  // 发生突变，找到缺失的数
                break;
            }
            
            pre++;
        }
        
        return pre + 1;
    }
};
`````

#### 解法3（原地哈希）

根据题目，我们需要找的数的范围在 [1,  len + 1]中，而在长度为 len 的数组中，至多可以查找到所有 [1, len] 的数，此时我们返回 len + 1,

对于其余的数，我们将 nums[i]，放在 nums[i] - 1 的索引处，最后再遍历一遍数组，找到第一个 nums[i] != i + 1 的数即可，

在交换位置的时候我们需要跳过不符合条件的数，

``````c++
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int len = nums.size();
        
        for (int i = 0; i < len; i++) {
            while (nums[i] > 0 && nums[i] <= len && nums[i] != nums[nums[i] - 1]) {
                // 在指定范围内，而且没有放在指定的位置上，则可以交换
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        
        for (int i = 0; i < len; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        
        // 都正确，则返回数组长度 + 1
        return len + 1;
    }
};
``````

