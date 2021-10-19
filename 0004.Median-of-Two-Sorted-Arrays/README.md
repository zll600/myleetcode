# [4. Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)

## 题目

Given two sorted arrays `nums1` and `nums2` of size `m` and `n` respectively, return **the median** of the two sorted arrays.

The overall run time complexity should be `O(log (m+n))`.

 

**Example 1:**

```
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
```

**Example 2:**

```
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
```

**Example 3:**

```
Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.00000
```

**Example 4:**

```
Input: nums1 = [], nums2 = [1]
Output: 1.00000
```

**Example 5:**

```
Input: nums1 = [2], nums2 = []
Output: 2.00000
```

 

**Constraints:**

- `nums1.length == m`
- `nums2.length == n`
- `0 <= m <= 1000`
- `0 <= n <= 1000`
- `1 <= m + n <= 2000`
- `-106 <= nums1[i], nums2[i] <= 106`

## 题目大意

给定两个大小分别为 m 和 n 的有序数组 nums1 和 nums2

请你找出这两个有序数组的中位数

## 解题思路

* 这道题下面所有方法的特殊情况处理都是一致的

* 可以利用一个辅助数组，简单的先将两个数组进行合并，因为两个数组均是有序的，所以类似于归并排序的 merge 操作，合并后根据元素个数是偶数还是奇数来求出中位数
* 将上一种方法的辅助数组可以优化掉
* 求中位数可以理解为求第 k 小的数的一种特殊情况，在有序的序列中查找一个数可以使用 “二分搜索”，上一种方法可以看作是每次排除一个数，最终确定答案，采用二分法，每次排除一半答案，可以降低时间复杂度。可以参考链接中的题解，讲的很详细
* 采用对数组进行切分的方法，
* 这里是参考的题解的链接https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-w-2/

## 代码

### Solution1:

这种解法比较容易想到，是空间换时间的策略，具体做法是，将两个有序数组进行合并（类似归并排序中的 merge操作），然后直接结算中位数即可

`````c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        const int m = nums1.size();
        const int n = nums2.size();

        // 如果 nums1 为空
        if (m == 0) {
            if (n % 2 != 0) {
                return nums2[n / 2] * 1.0;
            } else {
                return (nums2[n / 2 - 1] + nums2[n / 2]) / 2.0;
            }
        }

        // 如果 nums2 为空
        if (n == 0) {
            if (m % 2 != 0) {
                return nums1[m / 2] * 1.0;
            } else {
                return (nums1[m / 2 - 1] + nums1[m / 2]) / 2.0;
            }
        }

        const int size = m + n;
        vector<int> arr(size);
        int first = 0;  // 第一个数组的下标
        int second = 0;  // 第二个数组的下标
        // 这里利用了归并排序的知识
        for (int i = 0; i < size; ++i) {
            if (first >= m) {  // 如果 nums1 已经合并完毕
                arr[i] = nums2[second];
                ++second;
            } else if (second >= n) {  // 如果 nums2 已经已经合并完毕
                arr[i] = nums1[first];
                ++first;
            } else if (nums1[first] < nums2[second]) {  // 如果 nums[first] < nums2[second]
                arr[i] = nums1[first];
                ++first;
            } else {  // 如果 nums1[first] >= nums2[second]
                arr[i] = nums2[second];
                ++second;
            }
        }

        if (size % 2 != 0) {
            return arr[size / 2] * 1.0;
        }
        return (arr[size / 2 - 1] + arr[size / 2]) / 2.0;
    }
};c
`````

### Solution 2:

这中解法是对上一种解法的一种优化，因为两个数组本省都是有序的，所以我们并不需要一个数组来将二者真正合并，我们只需在归并的时候得到的需要的数字即可，我们并不需要归并所有的数字，因为计算中位数，只需要遍历到中间即可

这里我们计算一下：

* 对于奇数个数：以 5 为例，中位数下标 5 / 2 = 2（趋零截断），表示数组中的第 3 个数（从 1 开始），遍历次数 5 / 2 +  1 = 3 （idx = 0; idx < 3; ++idx）
* 对于奇数个数：以 6 位例，中位数下标有两位 6 / 2 = 3, 6 / 2 - 1 = 2，表示数组中的第 2 个数和第三个数（从 1 开始），遍历次数 6 / 2  + 2 = 4，将循环展开就是 (idx = 0; i dx < 4; ++idx)，

综上，奇数个数和偶数个数的情况，循环的次数都是一样的，这样我们就可以同意循环的逻辑

不同的是，奇数个数，最终结果只需要当前遍历到的，而偶数个数，除了当前遍历到的，还需要上一次遍历到的，二者相加取平均值

``````c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        const int m = nums1.size();
        const int n = nums2.size();

        // 如果 nums1 为空
        if (m == 0) {
            if (n % 2 != 0) {
                return nums2[n / 2] * 1.0;
            } else {
                return (nums2[n / 2 - 1] + nums2[n / 2]) / 2.0;
            }
        }

        // 如果 nums2 为空
        if (n == 0) {
            if (m % 2 != 0) {
                return nums1[m / 2] * 1.0;
            } else {
                return (nums1[m / 2 - 1] + nums1[m / 2]) / 2.0;
            }
        }

        const int size = m + n;
        int idx = 0;
        int first = 0;
        int second = 0;
        int prev = -1;
        int cur = -1;
        while (idx < size / 2 + 1) {
            prev = cur;
            if (first >= m) {
                cur = nums2[second];
                ++second;
            } else if (second >= n) {
                cur = nums1[first];
                ++first;
            } else if (nums1[first] < nums2[second]) {
                cur = nums1[first];
                ++first;
            } else {
                cur = nums2[second];
                ++second;
            }
            ++idx;
            // cout << prev << "---" << cur << endl;
        }

        if (size % 2 != 0) {
            return cur;
        }
        return (prev + cur) / 2.0;
    }
};
``````



### Solution 3:

将求中位数转换为求第 k 小的数，利用两个数组有序的特点来进行计算

````c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        const int len1 = nums1.size();  // nums1 的长度
        const int len2 = nums2.size();  // nums2 的长度
        int left = (len1 + len2 + 1) / 2;  // 中线左边位置
        int right = (len1 + len2 + 2) / 2;  // 中线右边位置

        // 这里，如果总长度是奇数，会求两次然后除以 2
        return (GetKth(nums1, 0, len1 - 1, nums2, 0, len2 - 1, left)
                + GetKth(nums1, 0, len1 - 1, nums2, 0, len2 - 1, right)) / 2.0;
    }

 private:
    // 递归区间是 [k, 1]，所以上面求left,right 时多了一步偏移
    int GetKth(const vector<int>& nums1, int start1, int end1,
            const vector<int>& nums2, int start2, int end2, int k) {
        int len1 = end1 - start1 + 1;  // 数组1 的有效长度
        int len2 = end2 - start2 + 1;  // 数组2 的有效长度
        // 因为我们后面会判但 len1 == 0，所以我们让 nums1 始终是最短的那个数组，可以简化代码
        if (len1 > len2) {
            return GetKth(nums2, start2, end2, nums1, start1, end1, k);
        }
        
        // 如果 nums1 为空，从nums2 中取，我们保证 nums1 一定先结束，
        // 因此这里的 if 语句的位置不能随意调换
        if (len1 == 0) {
            return nums2[start2 + k - 1];
        }
        // 执行到这里，两个数组肯定都是有效的
        // 取二者中较小的一个，
        if (k == 1) {
            return min(nums1[start1], nums2[start2]);
        }
        
        // 这里注意不能越界
        int i = start1 + min(len1, k / 2) - 1;  // 从nums1 中删除 k/ 2数，
        int j = start2 + min(len2, k / 2) - 1;  // 从nums2 中删除 k / 2个数
        if (nums1[i] > nums2[j]) {  // 如果nums2 中的数更小，就从nums2 中删除
            return GetKth(nums1, start1, end1, nums2, j + 1, end2, k - (j - start2 + 1));
        }
        return GetKth(nums1, i + 1, end1, nums2, start2, end2, k - (i - start1 + 1));
    }
};
````

### Solution 4:

这种解法，分别在两个数组上进行切割，这道题并不好讲解，最好自己照着题解，去画一画，将每一步的原因搞清楚

`````c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        const int len1 = nums1.size();
        const int len2 = nums2.size();
        // 保证 len1 <= len2
        if (len1 > len2) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int i_min = 0;
        int i_max = len1;
        while (i_min <= i_max) {
            int i = (i_min + i_max) / 2;  // nums1 的 mid
            int j = (len1 + len2 + 1) / 2 - i;  // nums2 的 mid 

            if (j != 0 && i != len1 && nums2[j - 1] > nums1[i]) {
                // 将 i 向右移，j 会自动左移
                i_min = i + 1;
            } else if (i != 0 && j != len2 && nums1[i - 1] > nums2[j]) {
                // 将 i 向左移，j 会自动右移
                i_max = i - 1;
            } else {
                // 达到要求开始考虑边界
                // 求左侧最大的数
                int max_left = 0;
                if (i == 0) {  // nums1 的左侧已经没有
                    max_left = nums2[j - 1];
                } else if (j == 0) {  // nums2 的左侧已经没有
                    max_left = nums1[i - 1];
                } else {
                    max_left = max(nums1[i - 1], nums2[j - 1]);
                }

                // 如果len1 + len2 是奇数
                if ((len1 + len2) % 2 != 0) {
                    return max_left;
                }

                // 求右侧最小的数
                int min_right = 0;
                if (i == len1) {  // nums1 的右侧已经没有
                    min_right = nums2[j];
                } else if (j == len2) {  // nums2的右侧已经没有
                    min_right = nums1[i];
                } else {
                    min_right = min(nums1[i], nums2[j]);
                }

                return (max_left + min_right) / 2.0;
            }
        }
        return 0.0;
    }
};
`````







````c++
class Solution {
public:
    // 解法一：先合并为一个大的数组，类似归并排序再计算中位数
    /*
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        
        if (m == 0) {
            if (n % 2 != 0) { // 避免 n 为负数
                return nums2[n / 2];
            } else {
                return (nums2[n / 2 - 1] / 2.0 + nums2[n / 2] / 2.0);
            }
        }
        
        if (n == 0) {
            if (m % 2 != 0) {
                return nums1[m / 2];
            } else {
                return (nums1[m / 2 - 1] / 2.0 + nums1[m / 2] / 2.0);
            }
        }
        
        vector<int> arr(m + n);
        int idx = 0;
        int i = 0;
        int j = 0;
        while (idx < (m + n)) {
            if (i == m) {
                while (j < n) {
                    arr[idx++] = nums2[j++];
                }
                break;
            }
            
            if (j == n) {
                while (i < m) {
                    arr[idx++]  = nums1[i++];
                }
                break;
            }
            
            if (nums1[i] < nums2[j]) {
                arr[idx++] = nums1[i++];
            } else {
                arr[idx++] = nums2[j++];
            }
        }
        
        if ((m + n) % 2 != 0) {
            return arr[idx / 2];
        } else {
            return (arr[idx / 2 - 1] / 2.0 + arr[idx / 2] / 2.0);
        }
        
        return -1;
    }
    */
    
    // 解法二：因为两个数组均是有序的，所以辅助数组是可以省略的。
    /*
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        
        int a_idx = 0;
        int b_idx = 0;
        int left = -1;
        int right = -1;
        
        for (int i = 0; i <= (m + n) / 2; ++i) {
            left = right;
            
            if (a_idx < m && (b_idx >= n || nums1[a_idx] < nums2[b_idx])) {
                right = nums1[a_idx++];
            } else {
                right = nums2[b_idx++];
            }
        }
        
        if ((m + n) % 2 != 0) {
            return right;
        } else {
            return (left / 2.0 + right / 2.0);
        }
        
        return -1;
    }
    */
    
    
    // 解法三：将查找中位数，转化为查找第 k 小的数的问题 （这个方法暂时没有通过，下面给出一个通过的java 版本）
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        
        int left = (n + m + 1) / 2; // 由对应的下表变化而来
        int right = (n + m + 2) / 2;
        
        return (GetKth(nums1, 0, m - 1, nums2, 0, n - 1, left) / 2.0
              + GetKth(nums1, 0, m - 1, nums2, 0, n - 1, right) / 2.0);
    }
    
    // 解法四：对数组进行切分
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        
        if (m > n) {
            return findMedianSortedArrays(nums2, nums1); // 保证 m <= n
        }
        
        int i_left = 0;
        int i_right = m;
        while (i_left <= i_right) {
            int i = i_left + (i_right - i_left) / 2;
            int j = (m + n + 1) / 2 - i;
            
            if (j > 0 && i < m && nums2[j - 1] > nums1[i]) { // 需要右移
                i_left = i + 1;
            } else if (i > 0 && j < n && nums1[i - 1] > nums2[j]) { // 需要左移
                i_right = i - 1;
            } else {        // 切分完成
                int left_bound = 0;     // 先考虑边界情况
                if (i == 0) {
                    left_bound = nums2[j - 1];
                } else if (j == 0) {
                    left_bound = nums1[i - 1];
                } else {
                    left_bound = max(nums1[i - 1], nums2[j - 1]);
                }
            
                if ((m + n) % 2 != 0) {     // 如果元素总数是奇数个，则不用再考虑右边
                    return left_bound;
                }
                
                int right_bound = 0;
                if (i == m) {
                    right_bound = nums2[j];
                } else if (j == n) {
                    right_bound = nums1[i];
                } else {
                    right_bound = min(nums1[i], nums2[j]);
                }
                
                return (left_bound / 2.0 + right_bound / 2.0); // 如果元素总数是偶数个
            }
        }
        
        return 0.0;
    }
    
 private:
    int GetKth(const vector<int>& nums1, int start1, int end1,
              const vector<int>& nums2, int start2, int end2, int k) {
        int len1 = start1 - end1 + 1;
        int len2 = start2 - end2 + 1;
        
        if (len1 > len2) {
            return GetKth(nums2, start2, end2, nums1, start1, end1, k);
        }
        if (len1 == 0) {
            return nums2[start2 + k - 1];
        }
        if (k == 1) {
            return min(nums1[start1], nums2[start2]);
        }
        
        int i = start1 + min(len1, k / 2) - 1;
        int j = start2 + min(len2, k / 2) - 1;
        if (nums1[i] > nums2[j]) {
            return GetKth(nums1, start1, end1, nums2, j + 1, end2, k - (j - start2 + 1));
        } else {
            return GetKth(nums1, i + 1, end1, nums2, start2, end2, k - (i - start1 + 1));
        } 
    }
};
````

* 解法三：java 版

```java
class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int n = nums1.length;
        int m = nums2.length;
        int left = (n + m + 1) / 2;
        int right = (n + m + 2) / 2;
        //将偶数和奇数的情况合并，如果是奇数，会求两次同样的 k 。
        return (getKth(nums1, 0, n - 1, nums2, 0, m - 1, left)
            + getKth(nums1, 0, n - 1, nums2, 0, m - 1, right)) * 0.5;  
    }
    
    
    private int getKth(int[] nums1, int start1, int end1, int[] nums2, int start2, int end2, int k) {
        int len1 = end1 - start1 + 1;
        int len2 = end2 - start2 + 1;
        //让 len1 的长度小于 len2，这样就能保证如果有数组空了，一定是 len1 
        if (len1 > len2) return getKth(nums2, start2, end2, nums1, start1, end1, k);
        if (len1 == 0) return nums2[start2 + k - 1];

        if (k == 1) return Math.min(nums1[start1], nums2[start2]);

        int i = start1 + Math.min(len1, k / 2) - 1;
        int j = start2 + Math.min(len2, k / 2) - 1;

        if (nums1[i] > nums2[j]) {
            return getKth(nums1, start1, end1, nums2, j + 1, end2, k - (j - start2 + 1));
        }
        else {
            return getKth(nums1, i + 1, end1, nums2, start2, end2, k - (i - start1 + 1));
        }
    }
}
```



