# [169. Majority Element](https://leetcode.com/problems/majority-element/)

Given an array `nums` of size `n`, return *the majority element*.

The majority element is the element that appears more than `⌊n / 2⌋` times. You may assume that the majority element always exists in the array.

 

**Example 1:**

```
Input: nums = [3,2,3]
Output: 3
```

**Example 2:**

```
Input: nums = [2,2,1,1,1,2,2]
Output: 2
```

 

**Constraints:**

- `n == nums.length`
- `1 <= n <= 5 * 104`
- `-231 <= nums[i] <= 231 - 1`

 

**Follow-up:** Could you solve the problem in linear time and in `O(1)` space?

## 题目大意

给定一个长度为 n 的整数数组，返回其中的众数

众数是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。你可以假设数组是非空的，并且给定的数组总是存在众数。

进阶要求：使用 O(1) 的空间

## 解题思路

这道题目的解题思路可以参考这篇题解：https://leetcode-cn.com/problems/majority-element/solution/3chong-fang-fa-by-gfu-2/

### 解法1（排序）

对于众数来说，出现次数是 n / 2，则排序之后，中间位置一定是

````c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // 排序，取中间值
        sort(nums.begin(), nums.end());
        return nums[(nums.size() - 1) / 2];
    }
};
````

### 解法2（计数）

使用一个 map ，元素的值做 key，元素出现的次数作为 value

`````c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        for (const auto& item : freq) {
            if (item.second > nums.size() / 2) {
                return item.first;
            }
        }
        
        return 0;
    }
};
`````

### 解法3（摩尔投票法思路）

大致思路就是如果 res == num 则 cnt++，否则 cnt--， 如果cnt 减至0，选取新的 res，然后将 cnt 重新置为 1，遍历完数组即可得到答案

这里注意：我在这里为了从下标 0 开始遍历，将 cnt 初始化为0，如果cnt 初值为 1，应该从下标 1 处开始遍历

关于这个算法： https://www.zhihu.com/question/49973163/answer/235921864

````c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int res = nums[0];
        int cnt = 0;  // 注意：这里初始化为 0，还未进入循环
        for (int num : nums) {
            if (num == res) {
                cnt++;
            } else {
                cnt--;
                if (cnt == 0) {  // 如果 cnt 减到0，则使用新的元素
                    res = num;
                    cnt = 1;
                }
            }
        }
        
        return res;
    }
};
````

