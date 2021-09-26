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

### 冒泡排序

`````c++
class Solution {
 public:
    vector<int> sortArray(vector<int>& nums) {
        for (int i = nums.size() - 1; i >= 1; i--) {
            // 这里先默认数组是有序的，只要发生一次交换，就说明还需要至少再来一轮
            // 如果内层循环没有发生一次交换，就说明数组已经有序，可以直接退出
            bool sorted = true;
            for (int j = 0; j < i; j++) {
                if (nums[j] > nums[j + 1]) {
                    swap(nums[j], nums[j + 1]);
                    sorted = false;
                }
            }
            if (sorted) {
                break;
            }
        }
        
        return nums;
    }
};
`````

### 计数排序（了解）

`````c++
class Solution {
 public:
    vector<int> sortArray(vector<int>& nums) {
        // 这里加上一个偏移使得输入的值可以作为数组下标
        int offset = 50000;
        int size = 100000;
        
        vector<int> count(size + 1, 0); // 计数数组
        for (int num : nums) {  // 计算计数数组
            count[num + offset]++;
        }
        
        for (int i = 1; i < size; i++) {  // 将 count 变为前缀和数组，
            count[i] += count[i - 1];
        }
        
        vector<int> tmp(nums.begin(), nums.end());
        
        // 这里是为了保证稳定性，从后往前赋值，
        for (int i = nums.size() - 1; i >= 0; i--) {
            int idx = count[tmp[i] + offset] - 1;
            nums[idx] = tmp[i];
            count[tmp[i] + offset]--;
        }
        
        return nums;
    }
};
`````

### 基数排序 (了解)

`````c++
class Solution {
public:
    // 基数排序：低位优先
    vector<int> sortArray(vector<int>& nums) {
        int len = nums.size();
        
        // 预处理，让所有的数都大于等于 0，这样才可以使用基数排序
        for (int i = 0; i < len; i++) {
            nums[i] += kOffset;
        }
        
        // 1、找出最大的数字
        int max_val = nums[0];
        for (int num : nums) {
            max_val = max(max_val, num);
        }
        
        // 2、计算出最大的数字有几位
        int max_len = GetMaxLen(max_val);
        
        // 计数排序需要使用的计数数组和临时数组
        vector<int> count(10);
        vector<int> tmp(len);
        
        // 表征关键字的量：除数
        // 1 表示按照个位关键字排序
        // 10 表示按照十位关键字排序
        // 1000 表示按照百位关键字排序
        // 10000 表示按照千位关键字排序
        int divisor = 1;
        // 有几位数，外层就需要进行几次排序
        for (int i = 0; i < max_len; i++) {
            // 每一步都使用计数排序，保证排序结果是稳定的
            // 这一步需要额外空间保存结果集，因把结果 tmp zhong
            CountingSort(nums, tmp, divisor, len, count);
            
            // 交换 nums 和 tmp 的引用，下一轮还是按照 nums 进行排序
            swap(nums, tmp);
            
            // divisor 自增，表示采用低位优先的基数排序
            divisor *= 10;
        }
        
        vector<int> res(len);
        for (int i = 0; i < len; i++) {
            res[i] = nums[i] - kOffset;
        }
        return res;
    }
    
 private:
    static const int kOffset = 50000;
    
    // 求数的位数
    int GetMaxLen(int num) {
        int len = 0;
        while (num > 0) {
            num /= 10;
            len++;
        }
        return len;
    }
    
    void CountingSort(vector<int>& nums, vector<int>& res,
                      int divisor, int len, vector<int>& count) {
        // 1、计算计数数组
        for (int i = 0; i < len; i++) {
            int remainder = (nums[i] / divisor) % 10;
            count[remainder]++;
        }
        
        // 2、变成前缀和数组
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        
        // 3、从后向前赋值
        for (int i = len - 1; i >= 0; i--) {
            int remainder = (nums[i] / divisor) % 10;
            int idx = count[remainder] - 1;
            res[idx] = nums[i];
            count[remainder]--;
        }
        
        // fill(count.begin(), count.end(), 0);
        count.assign(10, 0);
    }
};
`````

### 桶排序（了解）

````c++
class Solution {
public:
    
    vector<int> sortArray(vector<int>& nums) {
        int len = nums.size();
        
        // 1、将数据转化为 [0, 100000] 区间里的数
        for (int i = 0; i < len; i++) {
            nums[i] += kOffset;
        }
        
        // 2、观察数据，设置桶的个数
        // 步长
        int step = 10000;
        // 桶的个数
        int bucket_num = 100000 / step;
        
        // 桶
        vector<vector<int>> buckets(bucket_num + 1, vector<int>(len));
        // 每个桶中元素的个数
        vector<int> next(bucket_num + 1);
        
        // 分桶
        for (int num : nums) {
            int bucket_idx = num / step;
            buckets[bucket_idx][next[bucket_idx]] = num;
            next[bucket_idx]++;
        }
        
        for (int i = 0; i < bucket_num + 1; i++) {
            InsertionSort(buckets[i], next[i] - 1); // 这里减一不要忘记
        }
        
        vector<int> res(len);
        int idx = 0;
        for (int i = 0; i < bucket_num + 1; i++) {
            int cur_len = next[i];
            for (int j = 0; j < cur_len; j++) {
                res[idx] = buckets[i][j] - kOffset;
                idx++;
            }
        }
        
        return res;
    }
    
 private:
    static const int kOffset = 50000;
    
    // 注意这里要求提供一个左闭右闭的输入
    void InsertionSort(vector<int>& arr, int end) {
        for (int i = 1; i <= end; i++) {
            int tmp = arr[i];
            int j = i;
            while (j > 0 && arr[j - 1] > tmp) {
                arr[j] = arr[j - 1];
            }
            arr[j] = tmp;
        }
    }
};
````

 