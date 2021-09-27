# [75. Sort Colors](https://leetcode.com/problems/sort-colors/)

## 题目

Given an array `nums` with `n` objects colored red, white, or blue, sort them **[in-place](https://en.wikipedia.org/wiki/In-place_algorithm)** so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

We will use the integers `0`, `1`, and `2` to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function.

 

**Example 1:**

```
Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
```

**Example 2:**

```
Input: nums = [2,0,1]
Output: [0,1,2]
```

**Example 3:**

```
Input: nums = [0]
Output: [0]
```

**Example 4:**

```
Input: nums = [1]
Output: [1]
```

 

**Constraints:**

- `n == nums.length`
- `1 <= n <= 300`
- `nums[i]` is `0`, `1`, or `2`.

 

**Follow up:** Could you come up with a one-pass algorithm using only constant extra space?

## 题目大意

给定一个含有 n 个对象的数组，让颜色相同的对象相邻，

使用 0， 1， 2， 分别代表不同颜色的对象，只能原地排序，且不能使用库函数

* 进阶要求，使用一遍算法

## 解题思路

这道题就是三路快排的 partition 过程，这个过程最重要的就是要维护好区间的划分，在遍历数组的过程中，不能改变区间的含义，学术名称称为循环不变量，具体可以参考这篇题解：https://leetcode-cn.com/problems/sort-colors/solution/kuai-su-pai-xu-partition-guo-cheng-she-ji-xun-huan/

不过这道题目我是用三路快排解决的时候维护的循环不变量的含义与这篇题题解中有所不同，但我认为核心在于找到一个合理且正确的循环不变量的定义即可，最重要的是在遍历数组的时候维护好这个定义

## 代码

`````c++
class Solution {
public:
    void sortColors(vector<int>& nums) {
        if (nums.size() < 2) {
            return;
        }
        
        // 循环不变量
        // all in [0, zero] == 0
        // all in (zero, i) == 1
        // all in [two, len - 1] == 2
        
        // 初始化 [0, zero] 为空，所以 zero 为 -1，下面交换时，先自增，再交换
        int zero = -1;
        // 初始时 [two, len - 1] 为空，所以 two 为 len，下面交换时，先自减，再交换
        int two = nums.size();
        
        // i == two时覆盖了整个区间
        int i = 0;
        while (i < two) {
            if (nums[i] == 0) {
                zero++;
                swap(nums[i], nums[zero]);
                i++;
            } else if (nums[i] == 1) {
                i++;
            } else {
                two--;
                swap(nums[i], nums[two]);
            }
        }
    }
};
`````

