# [912. Sort an Array](https://leetcode.com/problems/sort-an-array/)

## 题目

Given an array of integers `nums`, sort the array in ascending order.

 

**Example 1:**

```
Input: nums = [5,2,3,1]
Output: [1,2,3,5]
```

**Example 2:**

```
Input: nums = [5,1,1,2,0,0]
Output: [0,0,1,1,2,5]
```

 

**Constraints:**

- `1 <= nums.length <= 5 * 104`
- `-5 * 104 <= nums[i] <= 5 * 104`

## 题目大意

给定一个整数数组 nums，将这个数组按照升序排序

## 解题思路

这道题目可以用来复习学过的排序算法

这里补上一篇总结的很好的题解：https://leetcode-cn.com/problems/sort-an-array/solution/fu-xi-ji-chu-pai-xu-suan-fa-java-by-liweiwei1419/

## 代码

#### 选择排序

`````c++
	// 选择排序，超时
    // 每次选择未排序中最小的一个交换到前面
    vector<int> sortArray(vector<int>& nums) {
        int len = nums.size();
        
        // 循环不变量 [0, i)，且该区间里的元素都是最终排定的样子
        for (int i = 0; i < len; ++i) {
            int min_idx = i;
            // 选择区间 [i, j] 中最小的一个，然后与 i 位置进行交换
            for (int j = i + 1; j < len; ++i) {
                if (nums[i] > nums[j]) {
                    min_idx = j;
                }
            }
            swap(nums[i], nums[min_idx]);
        }

        return nums;
    }
`````

### 插入排序

`````c++
    // 插入排序：稳定排序，在接近有序的情况下，效率较高
    vector<int> sortArray(vector<int>& nums) {
        int len = nums.size();
        
        // 循环不变量，将 nums[i] 插入到 [0, i) 中，使之有序，
        for (int i = 1; i < len; ++i) {
            // 现暂存这个元素，然后将其他元素后移
            int tmp = nums[i];    
            int j = i;
            // 注意检查边界
            while (j > 0 && nums[j - 1] > tmp) {
                nums[j] = nums[j - 1];
                --j;
            }
            nums[j] = tmp;
        }
        return nums;
    }
`````

### 归并排序

`````c++
class Solution {
public:
    // 归并排序
    vector<int> sortArray(vector<int>& nums) {
        vector<int> aux(nums.size());
        MergeSort(nums, 0, nums.size() - 1, aux);
        return nums;
    }

 private:
    static const int kInsertionThreshold = 7;

    // [lo, mid] 和 [mid + 1, hi] 均是有序
    // 这里利用一个辅助数组，
    void Merge(vector<int>& nums, int lo, int mid, int hi, vector<int>& aux) {
        copy(nums.begin() + lo, nums.begin() + hi + 1, aux.begin() + lo);
        
        int i = lo;
        int j = mid + 1;
        
        for (int k = lo; k <= hi; ++k) {
            if (i == mid + 1) {
                nums[k] = aux[j];
                ++j;
            } else if (j == hi + 1) {
                nums[k] = aux[i];
                ++i;
            } else if (aux[i] <= aux[j]) {  // 这里是为了保证排序的稳定行
                nums[k] = aux[i];
                ++i;
            } else {
                // aux[i] > aux[j]
                nums[k] = nums[j];
                ++j;
            }
        }
    }

    // 对数组 arr 的子区间 [lo, hi] 使用插入排序
    void InsertionSort(vector<int>& arr, int lo, int hi) {
        for (int i = lo + 1; i <= hi; ++i) {
            int tmp = arr[i];
            int j = i;

            while (j > lo && tmp < arr[j - 1]) {
                arr[j] = arr[j - 1];
                --j;
            }
            arr[j] = tmp;
        }
    }

    void MergeSort(vector<int>& nums, int lo, int hi, vector<int>& aux) {
        // 小区间使用插入排序
        if (hi - lo <= kInsertionThreshold) {
            InsertionSort(nums, lo, hi);
            return;
        }

        int mid = lo + (hi - lo) / 2;
        MergeSort(nums, lo, mid, aux);
        MergeSort(nums, mid + 1, hi, aux);

        // 如果数组的这个子区间本身有序，无需合并
        if (nums[mid] <= nums[mid + 1]) {
            return;
        }

        Merge(nums, lo, mid, hi, aux);
    }
};
`````

