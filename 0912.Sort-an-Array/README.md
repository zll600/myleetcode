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

### 快速排序（基本）

`````c++
class Solution {
 public:
    // 基本快速排序
    vector<int> sortArray(vector<int>& nums) {
        QuickSort(nums, 0, nums.size() - 1);
        return nums;
    }
    
 private:
    static const int kInsertionSort = 7;
    
    void InsertionSort(vector<int>& nums, int lo, int hi) {
        for (int i = lo + 1; i <= hi; ++i) {
            int tmp = nums[i];
            int j = i;
            while (j > lo && nums[j - 1] > tmp) {
                nums[j] = nums[j - 1];
            }
            nums[j] = tmp;
        }
    }
    
    int Partition(vector<int>& nums, int lo, int hi) {
        int pivot_idx = rand() % (hi - lo + 1) + lo;
        swap(nums[lo], nums[pivot_idx]);
        
        // 基准值
        int pivot = nums[lo];
        int lt = lo;
        
        // 循环不变量
        // all in [lo + 1, lt] < pivot
        // all in [lt + 1, i) >= pivot
        for (int i = lo + 1; i <= hi; ++i) {
            if (nums[i] < pivot) {
                lt++;
                swap(nums[i], nums[lt]);
            }
        }
        swap(nums[lo], nums[lt]);
        
        return lt;
    }
    
    void QuickSort(vector<int>& nums, int lo, int hi) {
        if (hi - lo <= kInsertionSort) {
            InsertionSort(nums, lo, hi);
            return;
        }
        
        int pivot_idx = Partition(nums, lo, hi);
        QuickSort(nums, lo, pivot_idx - 1);
        QuickSort(nums, pivot_idx + 1, hi);
    }
    
};
`````

### 快速排序（双指针）

``````c++
class Solution {
 public:
    vector<int> sortArray(vector<int>& nums) {
        QuickSort(nums, 0, nums.size() - 1);
        return nums;
    }

 private:
    static const int kInsertionThreshold = 7;

    void InsertionSort(vector<int>& nums, int lo, int hi) {
        for (int i = lo + 1; i <= hi; ++i) {
            int tmp = nums[i];
            int j = i;
            while (j > 0 && nums[j - 1] > tmp) {
                nums[j] = nums[j - 1];
            }
            nums[j] = tmp;
        }
    }

    int Partition(vector<int>& nums, int lo, int hi) {
        int pivot_idx = rand() % (hi - lo + 1) + lo;
        swap(nums[lo], nums[pivot_idx]);

        int pivot = nums[lo];
        int lt = lo + 1;
        int gt = hi;

        // all in [lo + 1, lt) <= pivot
        // all in (gt, hi] >= pivot
        while (true) {
            while (lt < hi && nums[lt] < pivot) {
                ++lt;
            }
            while (gt > lo && nums[gt] > pivot) {
                gt--;
            }

            if (lt >= gt) {
                break;
            }

            // 细节：相等的元素通过交换，等概率分到数组的两边
            swap(nums[lt], nums[gt]);
            gt--;
            lt++;
        }
        swap(nums[lo], nums[gt]);

        return gt;
    }

    void QuickSort(vector<int>& nums, int lo, int hi) {
        if (hi - lo <= kInsertionThreshold) {
            InsertionSort(nums, lo, hi);
            return;
        }

        int p_idx = Partition(nums, lo, hi);
        QuickSort(nums, lo, p_idx - 1);
        QuickSort(nums, p_idx + 1, hi);
    }
};
``````

### 快速排序（三指针）

`````c++
class Solution {
 public:
    vector<int> sortArray(vector<int>& nums) {
        QuickSort(nums, 0, nums.size() - 1);
        return nums;
    }

 private:
    static const int kInsertionThreshold = 7;

    void InsertionSort(vector<int>& nums, int lo, int hi) {
        for (int i = lo + 1; i <= hi; ++i) {
            int tmp = nums[i];
            int j = i;
            while (j > 0 && nums[j - 1] > tmp) {
                nums[j] = nums[j - 1];
            }
            nums[j] = tmp;
        }
    }

    void QuickSort(vector<int>& nums, int lo, int hi) {
        if (hi - lo <= kInsertionThreshold) {
            InsertionSort(nums, lo, hi);
            return;
        }
        
        int pivot_idx = rand() % (hi - lo + 1) + lo;
        swap(nums[lo], nums[pivot_idx]);
        
        // 循环不变量
        // all in [lo + 1, lt] < pivot
        // all in [lt + 1, i) == pivot
        // all in [gt, hi] > pivot
        int pivot = nums[lo];
        int lt = lo;
        int gt = hi + 1;
        int i = lo + 1;
        
        while (i < gt) {
            if (nums[i] < pivot) {
                lt++;
                swap(nums[i], nums[lt]);
                i++;
            } else if (nums[i] == pivot) {
                i++;
            } else {
                gt--;
                swap(nums[i], nums[gt]);
            }
        }
        swap(nums[lo], nums[lt]);
                
        // 注意这里，大大减少了两侧分治的区间
        QuickSort(nums, lo, lt - 1);
        QuickSort(nums, gt, hi);
    }
};
`````

###  堆排

``````c++
class Solution {
 public:
    vector<int> sortArray(vector<int>& nums) {
        // 将数组整理成堆
        Heapify(nums);
        
        // 循环不变量 [0, i] 有序
        int i = nums.size() - 1;
        while (i >= 1) {
            // 将堆顶元素（当前最大）交换到数组末尾
            swap(nums[0], nums[i]);
            --i;    // 逐步减少堆有序的部分
            SiftDown(nums, 0, i);   // 下沉操作，保证 [0, i] 有序
        }
        return nums;
    }

 private:
    // 下沉操作
    void SiftDown(vector<int>& nums, int k, int end) {
        while (2 * k + 1 <= end) {  // 注意这里是等于
            int j = 2 * k + 1;
            if (j + 1 <= end && nums[j] < nums[j + 1]) {
                j++;
            }
            
            if (nums[j] > nums[k]) {
                swap(nums[j], nums[k]);
            } else {
               break;   // 这里已经有序 
            }
            
            k = j;
        }
    }
    
    void Heapify(vector<int>& nums) {
        int len = nums.size();
        // 这里是取中间元素的下标而不是 第几个，所以 len -1
        for (int i = (len - 1) / 2; i >= 0; i--) {
            SiftDown(nums, i, len - 1);
        }
    }

};
``````

