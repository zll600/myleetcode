# [1818. Minimum Absolute Sum Difference](https://leetcode.com/problems/minimum-absolute-sum-difference/)

## 题目

You are given two positive integer arrays `nums1` and `nums2`, both of length `n`.

The **absolute sum difference** of arrays `nums1` and `nums2` is defined as the **sum** of `|nums1[i] - nums2[i]|` for each `0 <= i < n` (**0-indexed**).

You can replace **at most one** element of `nums1` with **any** other element in `nums1` to **minimize** the absolute sum difference.

Return the *minimum absolute sum difference **after** replacing at most one element in the array `nums1`.* Since the answer may be large, return it **modulo** `109 + 7`.

`|x|` is defined as:

- `x` if `x >= 0`, or
- `-x` if `x < 0`.

 

**Example 1:**

```
Input: nums1 = [1,7,5], nums2 = [2,3,5]
Output: 3
Explanation: There are two possible optimal solutions:
- Replace the second element with the first: [1,7,5] => [1,1,5], or
- Replace the second element with the third: [1,7,5] => [1,5,5].
Both will yield an absolute sum difference of |1-2| + (|1-3| or |5-3|) + |5-5| = 3.
```

**Example 2:**

```
Input: nums1 = [2,4,6,8,10], nums2 = [2,4,6,8,10]
Output: 0
Explanation: nums1 is equal to nums2 so no replacement is needed. This will result in an 
absolute sum difference of 0.
```

**Example 3:**

```
Input: nums1 = [1,10,4,4,2,7], nums2 = [9,3,5,1,7,4]
Output: 20
Explanation: Replace the first element with the second: [1,10,4,4,2,7] => [10,10,4,4,2,7].
This yields an absolute sum difference of |10-9| + |10-3| + |4-5| + |4-1| + |2-7| + |7-4| = 20
```

 

**Constraints:**

- `n == nums1.length`
- `n == nums2.length`
- `1 <= n <= 105`
- `1 <= nums1[i], nums2[i] <= 105`

## 题目大意

给你两个正整数数组 `nums1` 和 `nums2` ，数组的长度都是 `n` 。数组 `nums1` 和 `nums2` 的 绝对差值和 定义为所有  `|nums1[i] - nums2[i]|（0 <= i < n）` 的 总和（下标从 `0` 开始）

你可以选用 `nums1` 中的  *任意一个* 元素来替换 `nums1` 中的 *至多* 一个元素，以 *最小化* 绝对差值和。在替换数组 `nums1` 中最多一个元素 *之后*  ，返回最小绝对差值和

因为答案可能很大，所以需要对 `10^9 + 7` 取余 后返回。

## 解题思路

这道题目其实不难想到，要让整体的差值最小，且只能操作一次，那么就必须减小最大的那对差值，如果最大的差值有多对，还需要判断，修改那一对可以使得整体最小（这个跟 nums1 中的元素有关）

上面是想说明仅仅找到差值最大的一对数是不够的，另外，确定了需要修改的那对，那么怎样找到替换的值，这里其实不难想到排序 + 二分的思路

### Solution 1: Binary Search

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/minimum-absolute-sum-difference/solution/5724-jue-dui-chai-zhi-he-er-fen-cha-zhao-4glp/)

这里使用 set，一方面可以利用 set 的有序性，使用二分查找，一方面可以使用 set 来去重

对比去找产生最大差值的那一对，这里使用的思路是可以查找最大优化的那一对，这种思路和解法其实更优

````c++
class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        const int len = nums1.size();
        // 这里是为了利用 set 的有序性，方便后面进行二分查找
        set<long long> diff;
        long long all = 0, ans = 0;
        // 遍历两个数组的同时，计算出总的差值的和
        for (int i = 0; i < len; ++i) {
            diff.insert(nums1[i]);
            all += abs(nums1[i] - nums2[i]);
        }
        
        // 维护替换后可以产生的最大差值，这个值需要最大化
        long long max_diff = 0;
        for (int i = 0; i < len; ++i) {
            // 在 nums1 的所有元素中，查找第一个大于等于 nums2[i] 的，
            auto it = diff.lower_bound(nums2[i]);
            long long cur = abs(nums1[i] - nums2[i]);
            
            if (it != diff.end()) {
                max_diff = max(max_diff, cur - abs(*it - nums2[i]));
            }
            // 还需要考虑第一个小于 nums2[i] 的元素
            if (it != diff.begin()) {
                max_diff = max(max_diff, cur - abs(*(--it) - nums2[i]));
            }
        }
        return (all - max_diff) % mod_;
    }
 
 private:
    static const int mod_ = 1e9 + 7;
};
````

