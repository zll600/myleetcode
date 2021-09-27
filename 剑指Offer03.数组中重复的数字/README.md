# [剑指 Offer 03. 数组中重复的数字](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)

## 题目

找出数组中重复的数字。


在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

示例 1：

输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2 或 3 


限制：

2 <= n <= 100000

### 解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/solution/mian-shi-ti-03-shu-zu-zhong-zhong-fu-de-shu-zi-yua/

#### 解法1

利用map 作缓存一旦一个数字出现的数目大于 1，就立刻返回

````c++
class Solution {
 public:
    int findRepeatNumber1(vector<int>& nums) {
        unordered_map<int, int> freq;

        for (int num : nums) {
            freq[num]++;
            if (freq[num] > 1) {
                return num;
            }
        }

        return -1;
    }
};
````

### 解法2

如果用方法1，题目中还有一个条件没有用到 所有的数字都在`0~n-1`中，这说明可以利用索引和值的对应关心来解决这个问题

* nums[i] == i，可以直接跳过，索引右移
* nums[i] = nums[nums[i]] ，出现多个值对应一个索引的情况，可以直接返回
* 不满足上面的条件的话，将值防到对应的索引上，

````c++
class Solution {
public:
    // 利用了了原地排序的思想
    int findRepeatNumber(vector<int>& nums) {
        for (int i = 0; i < nums.size();) {
            if (nums[i] == i) { // 说明已经对应
                i++; // 只有已经有序才可以继续前进
                continue;
            } else if (nums[nums[i]] == nums[i]) {  // 出现多个值对应同一个索引
                return nums[i];
            }
            // 索引上的值 != 索引，将值调整的属于的索引中
            //int idx = nums[i];  // 这里最好借助一个临时变量，可以使代码更加清晰
            swap(nums[i], nums[idx]]);
        }

        return -1;
    }
};
````

