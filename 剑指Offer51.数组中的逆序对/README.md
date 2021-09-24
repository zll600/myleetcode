# [剑指 Offer 51. 数组中的逆序对](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/)

## 题目

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

 

示例 1:

输入: [7,5,6,4]
输出: 5

 

限制：

0 <= 数组长度 <= 50000

## 解题思路

这道题目利用了分治的思想（记住归并排序计算逆序对数），借助归并排序，将数组一步步进行拆分，然后在合并的时候统计逆序数

* 关键是在合并的时候，利用了两个数组有序的特征统计逆序对数
* 排序的过程是必要的，只有排序才能在下一轮利用顺序关系加快逆序对数的计算，也能避免重复计算

分治算法，逆序对数的来源：

* 左边区间的逆序对数，
* 右边区间的逆序对数
* 两部分合并的逆序对数

这道题有两种写法：

* 在第 2 个子区间归并回去的时候，计算逆序对数
* 在第1 个子区间归并回去的时候，计算逆序对数

这两种方法二选一，不然会重复计算

## 代码

`````c++
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        if (nums.size() < 2) {
            return 0;
        }
        vector<int> aux(nums.size());
        return ReversePairs(nums, 0, nums.size() - 1, aux);
    }

 private:
    // 计算 [lo, hi] 中的逆序数
    int ReversePairs(vector<int>& nums, int lo, int hi, vector<int>& aux) {
        if (lo >= hi) {
            return 0;
        }

        int mid = lo + (hi - lo) / 2;
        int left_pairs = ReversePairs(nums, lo, mid, aux);
        int right_pairs = ReversePairs(nums, mid + 1, hi, aux);

        // 如果整个数组已经有序，则无需合并，注意这里使用了小于等于
        if (nums[mid] <= nums[mid + 1]) {
            return left_pairs + right_pairs;
        }

        int cross_pairs = MergeCount(nums, lo, mid, hi, aux);
        return left_pairs + cross_pairs + right_pairs;
    }

    int MergeCount(vector<int>& nums, int lo, int mid, int hi, vector<int>& aux) {
        copy(nums.begin() + lo, nums.begin() + hi + 1, aux.begin() + lo);

        int i = lo;
        int j = mid + 1;

        int res = 0;
        for (int k = lo; k <= hi; ++k) {
            // 下标访问需要先判断是否越界
            if (i == mid + 1) {
                nums[k] = aux[j];
                ++j;
            } else if (j == hi + 1) {
                nums[k] = aux[i];
                ++i;
            } else if (aux[i] <= aux[j]) {
                // 注意：这里是 <=，题目要求的严格小于
                nums[k] = aux[i];
                ++i;
            } else {
                nums[k] = aux[j];
                ++j;
                // 计算逆序对数
                res += (mid - i + 1);
            }
        }
        return res;
    }
};
`````

