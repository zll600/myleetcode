# [287. Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)

## 题目

Given an array of integers `nums` containing `n + 1` integers where each integer is in the range `[1, n]` inclusive.

There is only **one repeated number** in `nums`, return *this repeated number*.

You must solve the problem **without** modifying the array `nums` and uses only constant extra space.

 

**Example 1:**

```
Input: nums = [1,3,4,2,2]
Output: 2
```

**Example 2:**

```
Input: nums = [3,1,3,4,2]
Output: 3
```

**Example 3:**

```
Input: nums = [1,1]
Output: 1
```

**Example 4:**

```
Input: nums = [1,1,2]
Output: 1
```

 

**Constraints:**

- `1 <= n <= 105`
- `nums.length == n + 1`
- `1 <= nums[i] <= n`
- All the integers in `nums` appear only **once** except for **precisely one integer** which appears **two or more** times.

 

**Follow up:**

- How can we prove that at least one duplicate number must exist in `nums`?
- Can you solve the problem in linear runtime complexity?

## 题目大意

给定一个含有 n + 1 个元素的数组，每个元素的范围是 [1-n] ，存在一个出现来两次的数，返回这个数

## 解题思路

* 最简单直接的是使用”缓存“，用一个 map 来缓存已经遍历过的数，如果已经出现过，则直接返回
* "缓存"使用的桶可以被优化掉，原地做标记，但要求标记必须是可还原的，因为最终要返回数组中的元素。这里采用的是将 数组中元素代表的下一个位置的标记为 “负的“，这样遍历的时候检查当前数组元素的值代表的位置是否已经出现过，如果出现国，则直接返回。
* 先排序，排序后重复的数字相邻，可以直接判断重复

* 这道题可以用 “快慢指针”来解，将这些数字想象成链表中的结点，数组中元素的值代表下一个结点的数字的下表。找重复的数字就是找链表中成环的那个点。题目中保证有重复的数，也就是这个假想的链表一定会成环，所以这道题就变成了一个环形链表求环入口的题目。用快慢指针的办法，快指针一次走2步，慢指针一次走一步，相交以后，快指针从头开始，每次走一步，慢指针依旧保持每次走一步，二者相遇就是所求的结果。

* 也可以使用“二分搜索”来做：

  1. 记录该区间的左边界、右边界和中间值 left、right 和 mid

  2. 遍历整个数组，统计小于等于 mid 的数的个数，
  3. 如果超过 mid 个，就说明重复的数存在于区间 [left, mid] （左闭右闭）中；否则，重复的数存在于区间 （mid, right] （左开右闭）中；
  4. 缩小区间，重复2、3步，直到区间个变成一个整数，即 left == right
  5. left 代表的整数就是重复的数。

* 也可以利用 数组下标 和 元素的值 之间的关系，先将数组进行排序，排序之后，利用数组下标从 0 开始递增的特性，计算数组元素的值 与 数组下标 的差值，若没有出现重复，则差值理应增大或不变，若差值减小，说明找到了重复的数。

````
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int size = nums.size();
        if (size < 2) {
            return -1;
        }
        
        // 解法一：原地做标记
        /*
        for (int i = 0; i < size; ++i) {
            int pos = abs(nums[i]) - 1;
            if (nums[pos] > 0) {
                nums[pos] *= -1;
            } else if (nums[pos] < 0) {
                return pos + 1;
            }
        }
        
        return -1;*/
        
        // 解法二：排序后查重
        /*
        sort(nums.begin(), nums.end());
        for (int i = 0; i < size; ++i) {
            if (i > 0 && nums[i - 1] == nums[i]) {
                return nums[i];
            }
        }
        
        return -1;
        */
        
        // 解法三：快慢指针，类似于成环的链表
        /*
        int slow = nums[0];
        int fast = nums[nums[0]];
        
        while (slow != fast) {
            fast = nums[nums[fast]];
            slow = nums[slow];
        }
        
        fast = 0;
        while (fast != slow) {
            fast = nums[fast];
            slow = nums[slow];
        }
        
        return fast;
        */
        
        
        // 解法四：二分搜索
        /*
        int low = 0;
        int high = size - 1;
        
        while (low < high) {
            int mid = low + (high - low) / 2;
            
            int counter = 0;
            for (int i = 0; i < size; ++i) {
                if (nums[i] <= mid) {
                    ++counter;
                }
            }
            
            if (counter > mid) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        
        return low;
        */
        
        // 解法五：排序之后，算二者间的差值
        /*
        sort(nums.begin(), nums.end());
        int diff = -1;
        for (int i = 0; i < size; ++i) {
            if (nums[i] - i - 1 >= diff) {
                diff = nums[i] - i - 1;
            } else {
                return nums[i];
            }
        }
        
        return -1;
        */
    }
};
````

