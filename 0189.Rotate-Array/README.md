# [189. Rotate Array](https://leetcode.com/problems/rotate-array/)

Given an array, rotate the array to the right by `k` steps, where `k` is non-negative.

 

**Example 1:**

```
Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
```

**Example 2:**

```
Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `-231 <= nums[i] <= 231 - 1`
- `0 <= k <= 105`

 

**Follow up:**

- Try to come up with as many solutions as you can. There are at least **three** different ways to solve this problem.
- Could you do it in-place with `O(1)` extra space?

## 题目大意

给定一个数组，将数组中的元素右移 k 步，其中k 是非负

**进阶要求**：

* 尽可能的想出更多的解法，这道题目至少有三种不同的解法
* 利用空间复杂度 O(1)的算法

## 解题思路

这道题需要注意的是 k 和 size 的大小关系，这里要取模

### 解法1（使用辅助数组）

这种解法利用了一个辅助数组，原数组从 k % size 开始写入，然后再将其余元素依次写入即可

````c++
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int size = nums.size();
        vector<int> aux(size, 0);
        
        int j = 0;  // 跟踪原数组的下标
        // 从原数组中 k % size 的位置开始，因为 k 可能大于等于 size
        for (int i = k % size; i < size && j < size; i++, j++) {
            aux[i] = nums[j];
        }
        
        // 再写入其余部分
        for (int i = 0; j < size; i++, j++) {
            aux[i] = nums[j];
        }
        
        // 将原数组和辅助数组进行交换
        swap(aux, nums);
        return;
    }
};
````

### 解法2

原地翻转

`````c++
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int size = nums.size();
        k %= size;  // 处理 k >= size  的情况，让下标落在合理的范围之内
        
        // 注意这里，reverse() 要求的是一个左闭右开的区间
        // 整体反转
        reverse(nums.begin(), nums.end());
        // 翻转前面 k 个
        reverse(nums.begin(), nums.begin() + k);  // 不含 k
        // 翻转剩余的
        reverse(nums.begin() + k, nums.end());  // 含 k
    }
};
`````

